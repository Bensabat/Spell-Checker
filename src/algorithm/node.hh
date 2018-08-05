#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <string.h>

using namespace std;

class Node
{
    public:
        Node();
        Node(char data, size_t freq);

        void pretty_printer(Node *node, size_t space = 0);
        void print() const;
        void print_children() const;

        void add_child(Node *child);
        void add_word(string, size_t);

        vector<Node *> children_get() const;
        size_t freq_get() const;
        char data_get() const;

    private:
        vector<Node *> children_;
        size_t freq_;
        char data_;
};