#include "ladder.h"

bool edit_distance_within(const string &str1, const string &str2, int d)
{
    // subtract from d each time, and then follow Levenshtein
    if (d < 0)
        return false;
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
    if (begin_word == end_word)
    {
        error(begin_word, end_word, "Begin and end words cannot be equal");
        return {};
    }
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

void error(string word1, string word2, string msg)
{
    cout << "Error with " << word1 << " " << word2 << ": " << msg << endl;
}

void load_words(set<string> &word_list, const string &file_name)
{
    ifstream infile(file_name);
    string line;
    while (getline(infile, line))
    {
        word_list.insert(line);
    }
}

void print_word_ladder(const vector<string> &ladder)
{
    for (string word : ladder)
    {
        cout << word << ",";
    }
    cout << endl;
}

#define my_assert(e)                                         \
    {                                                        \
        cout << #e << ((e) ? " passed" : " failed") << endl; \
    }
void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "./src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
