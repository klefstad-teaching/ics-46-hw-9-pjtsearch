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

TEST(is_adjacent, full_test)
{
  EXPECT_TRUE(is_adjacent("a", "ab"));
  EXPECT_TRUE(is_adjacent("aa", "ab"));
  EXPECT_FALSE(is_adjacent("sa", "ab"));
  EXPECT_FALSE(is_adjacent("nn", "ab"));
  EXPECT_FALSE(is_adjacent("aaa", "ab"));
  EXPECT_TRUE(is_adjacent("appl", "apple"));
  EXPECT_TRUE(is_adjacent("apple", "bapple"));
  EXPECT_TRUE(is_adjacent("apple", "apple"));
}

TEST(generate_word_ladder, full_test)
{
  set<string> word_list = {"cats", "car", "end", "cade", "cate", "date", "data"};
  vector<string> expected = {"code", "cade", "cate", "date", "data"};
  ASSERT_EQ(generate_word_ladder("code", "data", word_list), expected);
  set<string> word_list2 = {"cats", "car", "end", "cade", "cate", "data"};
  vector<string> expected2 = {};
  ASSERT_EQ(generate_word_ladder("code", "data", word_list), expected);
}