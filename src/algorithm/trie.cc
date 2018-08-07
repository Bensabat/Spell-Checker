#include "trie.hh"

Trie::Trie()
{
    char c = ' ';
    data_ = c;
    freq_ = 0;
}

Trie::Trie(char data, size_t freq)
{
    freq_ = freq;
    data_ = data;
}

void Trie::pretty_printer(Trie *trie, size_t space)
{
    for (auto child : trie->children_get())
    {
        for (size_t i = 0; i <= space; i++)
            cout << "+";
        
        child->print();

        if (child->children_get().size() != 0)
            pretty_printer(child, space + 1);
    }
}

void Trie::print() const
{
    cout << "Data: " << data_ << ", freq: " << freq_ << endl;
}

void Trie::print_children() const
{
    this->print();
    cout << "This current node has " << children_.size() << " children.\n" << endl;

    for (auto child : children_)
        child->print();
}

void Trie::add_child(Trie *child)
{
    children_.push_back(child);
}

ssize_t index_child(vector<Trie *> children, char data)
{
    ssize_t index = 0;
    for (auto trie : children)
    {
        if (trie->data_get() == data)
        {
            return index;
        }

        index++;
    }  
    return -1;
}

void Trie::add_word(string word, size_t freq)
{
    Trie *tmp_trie = this;
    size_t index_char = 0;
    size_t flag_freq = 0;

    while (index_char < word.length())
    {
        if (index_char == word.length() - 1)
            flag_freq = freq;

        char cur_char = word[index_char];

        // Has not children
        if (tmp_trie->children_get().size() == 0)
        {
            Trie *n = new Trie(cur_char, flag_freq);
            tmp_trie->add_child(n);
            tmp_trie = tmp_trie->children_get()[0];
        }
        else // children_.size() >= 1
        {
            ssize_t index = index_child(tmp_trie->children_, cur_char);

            if (index == -1) // node not found
            {
                Trie *n = new Trie(cur_char, flag_freq);
                tmp_trie->add_child(n);
                tmp_trie = tmp_trie->children_[tmp_trie->children_.size() - 1];
            }
            else // node found
            {
                tmp_trie = tmp_trie->children_[index];
            }
        }

        index_char++;
    }
}

vector<Trie *> Trie::children_get() const
{
    return children_;
}

size_t Trie::freq_get() const
{
    return freq_;
}

char Trie::data_get() const
{
    return data_;
}
