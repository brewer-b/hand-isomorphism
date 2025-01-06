#include "../src/hand_isomorphism.h"
#include <gtest/gtest.h>

TEST(RoundSize, PerfectRecall) {
  HandIsomorphism isomorphism(2, HandIsomorphism::Recall::Perfect);
  EXPECT_EQ(isomorphism.size(0), 169);
  EXPECT_EQ(isomorphism.size(1), 1286792);
  EXPECT_EQ(isomorphism.size(2), 55190538);
  EXPECT_EQ(isomorphism.size(3), 2428287420);
}

TEST(RoundSize, ImperfectRecall) {
  HandIsomorphism isomorphism(2, HandIsomorphism::Recall::Imperfect);
  EXPECT_EQ(isomorphism.size(0), 169);
  EXPECT_EQ(isomorphism.size(1), 1286792);
  EXPECT_EQ(isomorphism.size(2), 13960050);
  EXPECT_EQ(isomorphism.size(3), 123156254);
}

TEST(RoundSize, FlopRecall) {
  HandIsomorphism isomorphism(2, HandIsomorphism::Recall::Flop);
  EXPECT_EQ(isomorphism.size(0), 169);
  EXPECT_EQ(isomorphism.size(1), 1286792);
  EXPECT_EQ(isomorphism.size(2), 55190538);
  EXPECT_EQ(isomorphism.size(3), 1216698314);
}

TEST(RoundSize, PublicBoard) {
  HandIsomorphism isomorphism(2, HandIsomorphism::Recall::PublicBoard);
  EXPECT_EQ(isomorphism.size(0), 1755);
  EXPECT_EQ(isomorphism.size(1), 1755);
  EXPECT_EQ(isomorphism.size(2), 16432);
  EXPECT_EQ(isomorphism.size(3), 134459);
}