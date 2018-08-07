#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

#include "./trie.hh"

using namespace std;

size_t distance(string word1, string word2);

void search_trie_approx_rec(Trie *trie, string word, size_t max_dist,
                            vector<tuple<string, size_t>> &results_nodes,
                            string acc, size_t dist);

vector<tuple<string, size_t>> search_trie_approx(Trie *trie, string word, size_t max_dist);

tuple<string, string, string> common_prefix_decomposition(string word1, string word2);
