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