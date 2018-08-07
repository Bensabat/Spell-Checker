#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

#include "./trie.hh"
#include "./patricia_trie.hh"

using namespace std;

size_t distance(string word1, string word2);

void add_tuple_result(vector<tuple<string, size_t, size_t>> &results_nodes, tuple<string, size_t, size_t> &cur_tuple);

void search_trie_approx_rec(Trie *trie, string word, size_t max_dist,
                            vector<tuple<string, size_t>> &results_nodes,
                            string acc, size_t dist);

vector<tuple<string, size_t>> search_trie_approx(Trie *trie, string word, size_t max_dist);

void search_ptrie_approx_rec(Patricia_trie *ptrie, string word, size_t max_dist,
                             vector<tuple<string, size_t, size_t>> &results_nodes,
                             string acc, size_t dist);

vector<tuple<string, size_t, size_t>> search_ptrie_approx(Patricia_trie *ptrie, string word, size_t max_dist);
