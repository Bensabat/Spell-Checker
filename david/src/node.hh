#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Node
{
    public:
        Node();
        Node(std::string data, size_t freq);

        void pretty_printer(Node *node, size_t space = 0);
        void print() const;
        void print_children() const;

        void add_child(Node *child);
        void add_word(std::string, size_t);

        std::vector<Node *> children_get() const;
        size_t freq_get() const;
        std::string data_get() const;

    private:
        std::vector<Node *> children_;
        size_t freq_;
        std::string data_;
};
