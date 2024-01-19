#include "deck/deck.h"
#include <string>

#include <gtest/gtest.h>

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