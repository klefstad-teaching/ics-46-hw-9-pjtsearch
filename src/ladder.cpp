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

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list)
{
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size() - 1];
        for (string word : word_list)
        {
            if (is_adjacent(last_word, word))
            {
                if (!visited.contains(word))
                {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }

    return {};
}