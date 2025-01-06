#include <gtest/gtest.h>

extern "C" {
#include "../src/hand_isomorphism_c.h"
}

TEST(CWrapper, size) {
  HandIsomorphism *isomorphism = hand_isomorphism_create(2, RECALL_PERFECT);
  EXPECT_EQ(hand_isomorphism_size(isomorphism, 0), 169);
  EXPECT_EQ(hand_isomorphism_size(isomorphism, 1), 1286792);
  EXPECT_EQ(hand_isomorphism_size(isomorphism, 2), 55190538);
  EXPECT_EQ(hand_isomorphism_size(isomorphism, 3), 2428287420);
}
