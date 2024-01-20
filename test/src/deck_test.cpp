#include "deck/deck.h"

#include <gtest/gtest.h>

#include <cstddef>
#include <deque>
#include <list>
#include <memory>
#include <string>
#include <type_traits>

TEST(DeckTest, Static_TestTypes)
{
    static_assert(std::is_same<Deck<int>::value_type, int>::value == true,
                  "Compile time check failed: value_type doesn't match");
    static_assert(std::is_same<Deck<int>::reference, int&>::value == true,
                  "Compile time check failed: reference doesn't match");
    static_assert(std::is_same<Deck<std::string>::const_reference, const std::string&>::value == true,
                  "Compile time check failed: const_reference doesn't match");
    static_assert(std::is_same<Deck<short>::iterator, std::deque<short>::iterator>::value == true,
                  "Compile time check failed: iterator doesn't match");
    static_assert(
        std::is_same<Deck<int, std::list<int>>::const_iterator, std::list<int>::const_iterator>::value == true,
        "Compile time check failed: const_iterator doesn't match");
    static_assert(std::is_same<Deck<long>::difference_type, std::deque<long>::difference_type>::value == true,
                  "Compile time check failed: difference_type doesn't match");
    static_assert(std::is_same<Deck<int>::size_type, std::size_t>::value == true,
                  "Compile time check failed: size_type doesn't match");
}

TEST(DeckTest, TestAdd)
{
    Deck<int, std::vector<int>> deck;
    deck.add(1);
    EXPECT_EQ(1, deck.bottom());
    EXPECT_EQ(1, deck.top());

    deck.add(-1);
    EXPECT_EQ(1, deck.bottom());
    EXPECT_EQ(-1, deck.top());

    deck.add(100);
    EXPECT_EQ(1, deck.bottom());
    EXPECT_EQ(100, deck.top());
}

TEST(DeckTest, TestBottom)
{
    Deck<std::string, std::list<std::string>> deck;
    deck.add("Buu");
    deck.add("u");
    deck.add("uts");

    const auto& cbottom = deck.bottom();
    auto& bottom = deck.bottom();
    EXPECT_EQ("Buu", bottom);
    EXPECT_EQ("Buu", cbottom);

    bottom = "switcharoo";
    EXPECT_EQ("switcharoo", bottom);
    EXPECT_EQ("switcharoo", cbottom);
}

TEST(DeckTest, TestTop)
{
    Deck<std::string> deck;
    deck.add("Buu");
    deck.add("u");
    deck.add("uts");

    const auto& ctop = deck.top();
    auto& top = deck.top();
    EXPECT_EQ("uts", top);
    EXPECT_EQ("uts", ctop);

    top = "switcharoo";
    EXPECT_EQ("switcharoo", top);
    EXPECT_EQ("switcharoo", ctop);
}

TEST(DeckTest, TestSize)
{
    Deck<int> deck;
    EXPECT_EQ(0, deck.size());
    deck.add(1);
    EXPECT_EQ(1, deck.size());
    deck.add(1);
    deck.add(1);
    deck.add(1);
    EXPECT_EQ(4, deck.size());
}

TEST(DeckTest, TestCopy)
{
    Deck<int> deck;
    deck.add(1);
    deck.add(2);
    deck.add(3);

    auto deck2 = deck;
    auto deck3(deck);
    EXPECT_EQ(deck, deck2);
    EXPECT_EQ(deck, deck3);

    deck.add(4);
    EXPECT_NE(deck, deck2);
    EXPECT_NE(deck, deck3);
}

TEST(DeckTest, TestEmpty)
{
    Deck<int> deck;
    EXPECT_TRUE(deck.empty());
    EXPECT_EQ(0, deck.size());
    deck.add(1);
    EXPECT_FALSE(deck.empty());
    EXPECT_EQ(1, deck.size());
}

TEST(DeckTest, TestDraw)
{
    Deck<char> deck;
    deck.add('a');
    deck.add('b');
    deck.add('c');

    EXPECT_EQ(3, deck.size());
    EXPECT_EQ('c', deck.draw());

    EXPECT_EQ(2, deck.size());
    EXPECT_EQ('b', deck.draw());

    EXPECT_EQ(1, deck.size());
    EXPECT_EQ('a', deck.draw());

    EXPECT_TRUE(deck.empty());
}

TEST(DeckTest, TestMove)
{
    Deck<int> deck;
    deck.add(1);
    deck.add(10);
    deck.add(100);

    ASSERT_EQ(3, deck.size());

    auto&& moved_deck = std::move(deck);
    ASSERT_EQ(3, moved_deck.size());
    EXPECT_EQ(100, deck.draw());
    EXPECT_EQ(10, deck.draw());
    EXPECT_EQ(1, deck.draw());

    // Container semantics: "destroys or move-assigns all elements of a from elements of rv"
    // -> expect source container to be empty now
    EXPECT_TRUE(deck.empty());
}

TEST(DeckTest, TestMovable)
{
    Deck<std::unique_ptr<std::string>> deck;
    auto str = std::make_unique<std::string>("rofl");
    deck.add(std::move(str));
    deck.add(std::make_unique<std::string>("mao"));

    EXPECT_EQ("rofl", *deck.bottom());
    EXPECT_EQ("mao", *deck.top());

    auto ptr = deck.draw();
    EXPECT_EQ("mao", *ptr);

    ptr = deck.draw();
    EXPECT_EQ("rofl", *ptr);
}

TEST(DeckTest, TestIterators)
{
    Deck<int> deck;
    deck.add(1);
    deck.add(2);
    deck.add(3);

    auto it = deck.begin();
    EXPECT_EQ(1, *it++);
    EXPECT_EQ(2, *it);
    EXPECT_EQ(3, *(++it));
    EXPECT_EQ(deck.end(), ++it);
    EXPECT_EQ(deck.end(), deck.cend());

    int expected = 1;
    for (const auto& value : deck)
    {
        EXPECT_EQ(expected, value);
        expected++;
    }
}

TEST(DeckTest, TestSwap)
{
    Deck<int> deck;
    deck.add(5);
    deck.add(6);
    deck.add(7);

    Deck<int> deck2;
    deck2.add(100);
    deck2.add(200);

    std::swap(deck, deck2);
    ASSERT_EQ(2, deck.size());
    EXPECT_EQ(100, deck.bottom());
    EXPECT_EQ(200, deck.top());

    ASSERT_EQ(3, deck2.size());
    EXPECT_EQ(7, deck2.draw());
    EXPECT_EQ(6, deck2.draw());
    EXPECT_EQ(5, deck2.draw());
}

TEST(DeckTest, TestMaxSize)
{
    Deck<int> deck;
    std::deque<int> deque;
    EXPECT_EQ(deque.max_size(), deck.max_size());

    Deck<int, std::vector<int>> deck2;
    std::vector<int> vector;
    EXPECT_EQ(vector.max_size(), deck2.max_size());
}