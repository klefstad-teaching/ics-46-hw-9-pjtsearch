#include "ladder.h"

bool edit_distance_within(const string &str1, const string &str2, int d)
{
    // subtract from d each time, and then follow Levenshtein
    if (str1.size() == 0)
        return int(str2.size()) <= d;
    if (str2.size() == 0)
        return int(str1.size()) <= d;
    if (str1[0] == str2[0])
        return edit_distance_within(str1.substr(1), str2.substr(1), d);
    return edit_distance_within(str1.substr(1), str2, d - 1) ||
           edit_distance_within(str1, str2.substr(1), d - 1) ||
           edit_distance_within(str1.substr(1), str2.substr(1), d - 1);
}

bool is_adjacent(const string &word1, const string &word2)
{
    return edit_distance_within(word1, word2, 1);
}