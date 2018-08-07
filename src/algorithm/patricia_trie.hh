#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <string.h>

#include "./utils.hh"

using namespace std;

class Patricia_trie
{
    public:
        Patricia_trie();
        Patricia_trie(string &data, size_t freq);

        void pretty_printer(Patricia_trie *node, size_t space = 0);
        void print() const;
        void print_children() const;

        void add_child(Patricia_trie *ptrie, string &word, size_t freq);
        void add_word(Patricia_trie *ptrie, string, size_t);

        vector<Patricia_trie *>& children_get();
        size_t freq_get() const;
        string data_get() const;
        void data_set(string &data);

        vector<Patricia_trie *> children_;        

    private:
        size_t freq_;
        string data_;
};
