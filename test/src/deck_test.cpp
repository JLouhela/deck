#include "deck/deck.h"

#include <gtest/gtest.h>

TEST(DeckTest, FirstTest)
{
    Deck<int> deck;
    EXPECT_EQ(0, deck.test());
}