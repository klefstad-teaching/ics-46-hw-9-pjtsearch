#include "ladder.h"

bool edit_distance_within(const string &str1, const string &str2, int d)
{
    int str1_size = str1.size();
    int str2_size = str2.size();

    vector<int> prev_distances(str2_size + 1, 0);
    for (int i = 0; i <= str2_size; ++i) // initialize first row
        prev_distances[i] = i;

    vector<int> curr_distances(str2_size + 1, 0);
    for (int i = 0; i < str1_size; ++i)
    {
        curr_distances[0] = i + 1;
        for (int j = 0; j < str2_size; ++j)
        {
            int deletionCost = prev_distances[j + 1] + 1;
            int insertionCost = curr_distances[j] + 1;
            int substitutionCost;
            if (str1[i] == str2[j])
                substitutionCost = prev_distances[j];
            else
                substitutionCost = prev_distances[j] + 1;

            curr_distances[j + 1] = min(min(deletionCost, insertionCost), substitutionCost);
        }
        prev_distances = curr_distances;
    }
    return prev_distances[str2_size] <= d;
}

bool is_adjacent(const string &word1, const string &word2)
{
    if (abs(int(word1.size()) - int(word2.size())) > 1)
        return false;
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
    if (ladder.size() > 0)
    {
        cout << "Word ladder found: ";
        for (string word : ladder)
        {
            cout << word << " ";
        }
    }
    else
    {
        cout << "No word ladder found.";
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
