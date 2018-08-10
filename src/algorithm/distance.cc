#include "distance.hh"


// Function that calculate the Damerau-Levenshtein distance between 2 words
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

// Function that add tuple into vecto by ASC distance, DSC frequence, ASC lexical order
void add_tuple_result(vector<tuple<string, size_t, size_t>> &results_nodes, tuple<string, size_t, size_t> &cur_tuple)
{
    vector<tuple<string, size_t, size_t>>::iterator it = results_nodes.begin();

    size_t index = 0;

    for(; index < results_nodes.size(); index++)
    {
        if (get<2>(cur_tuple) <= get<2>(results_nodes[index]))
        {
            if (get<2>(cur_tuple) < get<2>(results_nodes[index]))
                break;
            
            if (get<1>(cur_tuple) >= get<1>(results_nodes[index]))
            {
                if (get<1>(cur_tuple) > get<1>(results_nodes[index]))
                    break;            

                if (get<0>(cur_tuple) <= get<0>(results_nodes[index]))
                    break;
            }
        }
    }

    // Insert at the good position
    results_nodes.insert(it + index, cur_tuple);
}

// Recursive function for search_trie_approx
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

// Function that search words with dist of max_dist on a Trie
vector<tuple<string, size_t>> search_trie_approx(Trie *trie, string word, size_t max_dist)
{
    vector<tuple<string, size_t>> results_nodes;
    search_trie_approx_rec(trie, word, max_dist, results_nodes, "", 0);

    return results_nodes;
}

// Recursive function for search_ptrie_approx
void search_ptrie_approx_rec(Patricia_trie *ptrie, string word, size_t max_dist,
                            vector<tuple<string, size_t, size_t>> &results_nodes,
                            string acc, size_t dist)
{
    if (word.size() + max_dist < acc.size())
        return;
    
    for (auto child : ptrie->children_get())
    {
        if (child->data_get().back() == '$') // leaf
        {
            string cur_acc = acc + child->data_get();
            dist = distance(word, cur_acc);

            if (dist <= max_dist)
            {
                // remove the '$' at the end of the word
                cur_acc.pop_back();
                auto cur_tuple = make_tuple(cur_acc, child->freq_get(), dist);
                add_tuple_result(results_nodes, cur_tuple);

                if (max_dist == 0)
                    return;
            }
        }

        // If child have some children, launch the search on them
        else
        {
            search_ptrie_approx_rec(child, word, max_dist, results_nodes, acc + child->data_get(), dist);
        }
    }
}

// Function that search words with dist of max_dist on a Trie
vector<tuple<string, size_t, size_t>> search_ptrie_approx(Patricia_trie *ptrie, string word, size_t max_dist)
{
    vector<tuple<string, size_t, size_t>> results_nodes;
    search_ptrie_approx_rec(ptrie, word + "$", max_dist, results_nodes, "", 0);

    return results_nodes;
}
