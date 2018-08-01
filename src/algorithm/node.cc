#include "node.hh"

Node::Node()
{
    data_ = "";
    freq_ = 0;
}

Node::Node(string data, size_t freq)
{
    freq_ = freq;
    data_ = data;
}

void Node::pretty_printer(Node *node, size_t space)
{
    for (auto child : node->children_get())
    {
        for (size_t i = 0; i <= space; i++)
            cout << "+";
        
        child->print();

        if (child->children_get().size() != 0)
            pretty_printer(child, space + 1);
    }
}

void Node::print() const
{
    cout << "Data: " << data_ << ", freq: " << freq_ << endl;
}

void Node::print_children() const
{
    this->print();
    cout << "This current node has " << children_.size() << " children.\n" << endl;

    for (auto child : children_)
        child->print();
}

void Node::add_child(Node *child)
{
    children_.push_back(child);
}

ssize_t index_child(vector<Node *> children, string data)
{
    ssize_t index = 0;
    for (auto node : children)
    {
        if (node->data_get() == data)
            return index;
        
        index++;
    }
    return -1;
}

void Node::add_word(string word, size_t freq)
{
    Node *tmp_node = this;
    size_t index_char = 0;
    size_t flag_freq = 0;

    while (index_char < word.length())
    {
        if (index_char == word.length() - 1)
            flag_freq = freq;

        string cur_char(1, word[index_char]);


        if (tmp_node->children_get().size() == 0)
        {
            Node *n = new Node(cur_char, flag_freq);
            tmp_node->add_child(n);
            tmp_node = tmp_node->children_get()[0];
        }
        else // children_.size() >= 1
        {
            ssize_t index = index_child(tmp_node->children_, cur_char);
            
            if (index == -1)
            {
                Node *n = new Node(cur_char, flag_freq);
                tmp_node->add_child(n);
                tmp_node = tmp_node->children_[tmp_node->children_.size() - 1];
            }
            else // node found
            {
                tmp_node = tmp_node->children_[index];
            }
        }

        index_char++;
    }
}

vector<Node *> Node::children_get() const
{
    return children_;
}

size_t Node::freq_get() const
{
    return freq_;
}

string Node::data_get() const
{
    return data_;
}
