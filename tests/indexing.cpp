#include "../src/hand_isomorphism.h"
#include <gtest/gtest.h>

TEST(Indexing, index) {
  HandIsomorphism isomorphism(HandIsomorphism::Recall::Perfect);
  uint8_t cards[2] = {0, 1};
  EXPECT_EQ(isomorphism.index(0, cards), 0);
  cards[0] = 1;
  cards[1] = 48;
  EXPECT_EQ(isomorphism.index(0, cards), 78);
}

TEST(Indexing, unindex) {
  HandIsomorphism isomorphism(HandIsomorphism::Recall::Perfect);
  uint8_t cards[2];
  isomorphism.unindex(0, 78, cards);
  EXPECT_EQ((int)cards[0], 48);
  EXPECT_EQ((int)cards[1], 1);
}