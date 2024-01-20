#include "deck/deck.h"

#include <gtest/gtest.h>

#include <cstddef>
#include <list>
#include <string>
#include <type_traits>
#include <vector>

TEST(DeckTest, Static_TestTypes)
{
    static_assert(std::is_same<Deck<int>::value_type, int>::value == true,
                  "Compile time check failed: value_type doesn't match");
    static_assert(std::is_same<Deck<int>::reference, int&>::value == true,
                  "Compile time check failed: reference doesn't match");
    static_assert(std::is_same<Deck<std::string>::const_reference, const std::string&>::value == true,
                  "Compile time check failed: const_reference doesn't match");
    static_assert(std::is_same<Deck<short>::iterator, std::vector<short>::iterator>::value == true,
                  "Compile time check failed: iterator doesn't match");
    static_assert(
        std::is_same<Deck<int, std::list<int>>::const_iterator, std::list<int>::const_iterator>::value == true,
        "Compile time check failed: const_iterator doesn't match");
    static_assert(std::is_same<Deck<long>::difference_type, std::vector<long>::difference_type>::value == true,
                  "Compile time check failed: difference_type doesn't match");
    static_assert(std::is_same<Deck<int>::size_type, std::size_t>::value == true,
                  "Compile time check failed: size_type doesn't match");
}

TEST(DeckTest, TestAdd)
{
    Deck<int> deck;
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
    Deck<std::string> deck;
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
    EXPECT_EQ(deck, deck2);
    deck.add(4);
    EXPECT_NE(deck, deck2);
}

TEST(DeckTest, TestEmpty)
{
    Deck<int> deck;
    EXPECT_TRUE(deck.empty());
    deck.add(1);
    EXPECT_FALSE(deck.empty());
}
