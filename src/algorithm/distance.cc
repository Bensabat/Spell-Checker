#include "distance.hh"

size_t distance(string word1, string word2)
{
    size_t i, j, dist;
    const size_t length1 = word1.length();
    const size_t length2 = word2.length();

    vector<vector<size_t>> d(length1 + 1, vector<size_t>(length2 + 1));
    
    for (i = 0; i <= length1; ++i)
        d[i][0] = i;
    
    for (j = 1; j <= length2; ++j)
        d[0][j] = j;

    for (i = 1; i <= length1; ++i)
        for (j = 1; j <= length2; ++j)
        {
            dist = !(word1[i - 1] == word2[j - 1]);

            d[i][j] = min(min(d[i - 1][j] + 1,     // deletion
                          d[i][j - 1] + 1),        // insertion
                          d[i - 1][j - 1] + dist); // substitution or equal

            if (i > 1 && j > 1 && word1[i - 1] == word2[j - 2] && word1[i - 2] == word2[j - 1])
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + dist); // transposition
        }

    return d[length1][length2];
}

void search_trie_approx_rec(Trie *trie, string word, size_t max_dist,
                            vector<tuple<string, size_t>> &results_nodes,
                            string acc, size_t dist)
{
    if (word.size() + max_dist < acc.size())
        return;
    
    for (auto child : trie->children_get())
    {
        if (child->data_get() == '$') // leaf
        {
            dist = distance(word, acc);

            if (dist <= max_dist)
            {
                auto cur_tuple = make_tuple(acc, child->freq_get());    
                results_nodes.push_back(cur_tuple);

                if (max_dist == 1)
                    return;
            }
        }

        // If child have some children, launch the search on them
        else
        {
            search_trie_approx_rec(child, word, max_dist, results_nodes, acc + child->data_get(), dist);
        }
    }
}

vector<tuple<string, size_t>> search_trie_approx(Trie *trie, string word, size_t max_dist)
{
    vector<tuple<string, size_t>> results_nodes;
    search_trie_approx_rec(trie, word, max_dist, results_nodes, "", 0);

    return results_nodes;
}

// Function that compares 2 strings and decomposes its into the common part and the 2 non-common parts
// ie: (david, dadou) -> (da, vid, dou)
tuple<string, string, string> common_prefix_decomposition(string word1, string word2)
{
    string common("");
    size_t length_word1 = word1.length();
    size_t length_word2 = word2.length();    
    size_t min_length = min(length_word1, length_word2);
    size_t i = 0;

    // Getting the common part
    while((i < min_length) && (word1[i] == word2[i]))
    {
        common[i] = word1[i];
        i++;
    }
    common[i] = '\0';

    // Getting the non-common part
    string rest_word1 = word1.substr(i, length_word1 - i);
    string rest_word2 = word2.substr(i, length_word2 - i);

    // Creating and return the tuple
    auto tuple_elements = make_tuple(common.c_str(), rest_word1, rest_word2);
    return tuple_elements;
}
