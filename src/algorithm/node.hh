#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Node
{
    public:
        Node();
        Node(string data, size_t freq);

        void pretty_printer(Node *node, size_t space = 0);
        void print() const;
        void print_children() const;

        void add_child(Node *child);
        void add_word(string, size_t);

        vector<Node *> children_get() const;
        size_t freq_get() const;
        string data_get() const;

    private:
        vector<Node *> children_;
        size_t freq_;
        string data_;
};