#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(edit_distance_within, full_test)
{
  EXPECT_TRUE(edit_distance_within("a", "ab", 1));
  EXPECT_TRUE(edit_distance_within("aa", "ab", 1));
  EXPECT_FALSE(edit_distance_within("sa", "ab", 1));
  EXPECT_FALSE(edit_distance_within("nn", "ab", 1));
  EXPECT_FALSE(edit_distance_within("aaa", "ab", 1));
  EXPECT_TRUE(edit_distance_within("aaa", "ab", 2));
  EXPECT_TRUE(edit_distance_within("car", "hats", 3));
  EXPECT_FALSE(edit_distance_within("car", "hats", 2));
}
