#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <string.h>

using namespace std;

class Trie
{
    public:
        Trie();
        Trie(char data, size_t freq);

        void pretty_printer(Trie *trie, size_t space = 0);
        void print() const;
        void print_children() const;

        void add_child(Trie *child);
        void add_word(string, size_t);

        vector<Trie *> children_get() const;
        size_t freq_get() const;
        char data_get() const;

    private:
        vector<Trie *> children_;
        size_t freq_;
        char data_;
};