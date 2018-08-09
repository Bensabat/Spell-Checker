#include "patricia_trie.hh"

void Patricia_trie::serialize(ofstream& stream)
{
    int data_length = data_.length();
    int children_size = children_.size();

    // cout << "data_length: " << data_length
    //     << ", children_size: " << children_size
    //     << ", data: " << data_
    //     << ", freq: " << freq_
    //     << endl;

    stream.write(reinterpret_cast<char*>(&data_length), sizeof(int));
    stream.write(reinterpret_cast<const char*>(data_.c_str()), data_length);
    stream.write(reinterpret_cast<char*>(&freq_), sizeof(int));
    stream.write(reinterpret_cast<char*>(&children_size), sizeof(int));

    for (auto child : children_get())
        child->serialize(stream);
}

Patricia_trie* Patricia_trie::deserialize(ifstream& stream)
{
    Patricia_trie* root = new Patricia_trie();

    int data_length;
    int children_size;
    
    stream.read(reinterpret_cast<char*>(&data_length), sizeof(int));

    //char *data = new char[data_length + 1];
    char data[data_length + 1];
    data[data_length] = '\0';

    stream.read(reinterpret_cast<char*>(&data), data_length);
    stream.read(reinterpret_cast<char*>(&(root->freq_)), sizeof(int));
    stream.read(reinterpret_cast<char*>(&children_size), sizeof(int));
    root->data_ = string(data);

    // cout << "data_length: " << data_length
    //     << ", children_size: " << children_size
    //     << ", data: " << root->data_
    //     << ", freq: " << root->freq_
    //     << endl;

    for (int i = 0; i < children_size; i++)
        root->children_.push_back(deserialize(stream));

    return root;
}

Patricia_trie::Patricia_trie()
{
    string str = "";
    data_ = str;
    freq_ = 0;
}

Patricia_trie::Patricia_trie(string &data, size_t freq)
{
    freq_ = freq;
    data_ = data;
}

void Patricia_trie::pretty_printer(Patricia_trie *node, size_t space)
{
    for (auto child : node->children_get())
    {
        for (size_t i = 0; i <= space; i++)
            cout << "+";
        
        child->print();

        //cout << child->children_get().size() << endl;
        if (child->children_get().size() != 0)
            pretty_printer(child, space + 1);
    }
}

void Patricia_trie::print() const
{
    cout << "Data: " << data_ << ", freq: " << freq_ << endl;
}

void Patricia_trie::print_children() const
{
    this->print();
    cout << "This current node has " << children_.size() << " children.\n" << endl;

    for (auto child : children_)
    {
        child->print();
    }
    cout << endl;
}

void Patricia_trie::add_child(Patricia_trie *ptrie, string &word, size_t freq)
{
    Patricia_trie *child = new Patricia_trie(word, freq);
    ptrie->children_get().push_back(child);
}

ssize_t get_index(vector<Patricia_trie*> children, string data)
{
    ssize_t index = 0;
    for (auto child : children)
    {
        if (child->data_get() == data)
        {
            return index;
        }

        index++;
    }  
    return -1;
    
}

void Patricia_trie::add_word(Patricia_trie *ptrie, string word, size_t freq)
{
    auto cur_children = ptrie->children_get();

    // If cur node hasn't child
    if (cur_children.size() == 0)
    {
        this->add_child(ptrie, word, freq);
    }

    // Cur node has some child
    else
    {
        for(auto child : cur_children)
        {
            auto tuple_dec = common_prefix_decomposition(child->data_get(), word);

            // If cur node's child has common prefix
            if (get<0>(tuple_dec) != "")
            {
                if (get<1>(tuple_dec) == "")
                {
                    this->add_word(child, get<2>(tuple_dec), freq);
                }
                else
                {
                    // 1
                    Patricia_trie *father = new Patricia_trie(get<0>(tuple_dec), 0);

                    // 2
                    ptrie->children_get().push_back(father);

                    // 3
                    father->children_get().push_back(child);

                    // 4
                    size_t index = get_index(ptrie->children_, child->data_get());
                    ptrie->children_.erase(ptrie->children_.begin() + index);

                    // 5
                    child->data_set(get<1>(tuple_dec));

                    // 6
                    this->add_child(father, get<2>(tuple_dec), freq);
                }

                return;
            }

            // Cur node's child hasn't common prefix
            else
            {
                continue;
            }
        }

        // If all the cur node's children havn't common prefix
        this->add_child(ptrie, word, freq);
    }

}

vector<Patricia_trie *>& Patricia_trie::children_get()
{
    return children_;
}

size_t Patricia_trie::freq_get() const
{
    return freq_;
}

string Patricia_trie::data_get() const
{
    return data_;
}

void Patricia_trie::data_set(string &data)
{
    data_ = data;
}
