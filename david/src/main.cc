#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

#include "node.hh"
#include "damereau-levenshtein.hh"


void search_approx_rec(Node *trie, std::string word, size_t max_dist,
                       std::vector<std::tuple<std::string, size_t>> &results_nodes,
                       std::string acc, size_t dist)
{
    if (word.size() + max_dist < acc.size())
        return;
    
    for (auto child : trie->children_get())
    {
        if (child->data_get() == "$") // leaf
        {
            dist = compute_distance(word, acc);

            if (dist <= max_dist)
            {
                auto cur_tuple = std::make_tuple(acc, child->freq_get());    
                results_nodes.push_back(cur_tuple);

                if (max_dist == 1)
                    return;
            }
        }

        // If child have some children, launch the search on them
        else
        {
            search_approx_rec(child, word, max_dist, results_nodes, acc + child->data_get(), dist);
        }
    }
    
}

std::vector<std::tuple<std::string, size_t>> search_approx(Node *trie, std::string word, size_t max_dist)
{
    std::vector<std::tuple<std::string, size_t>> results_nodes;
    search_approx_rec(trie, word, max_dist, results_nodes, "", 0);

    return results_nodes;
}

void print_node_vect(std::vector<std::tuple<std::string, size_t>> results_vect)
{
    std::cout << "This vector contained " << results_vect.size() << " words:\n" << std::endl;
    for(auto tuple : results_vect)
    {
        std::cout << "(" << std::get<0>(tuple) << ", " << std::get<1>(tuple) << ")" << std::endl;
    }
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Please enter ./TextMiningCompiler /path/to/words.txt /path/to/dict.bin" << std::endl;
        return 1;
    }
    else
    {
        std::ifstream infile(argv[1]);

        if (infile.is_open())
        {
            std::cout << "Opened" << std::endl;

            std::string word;
            int freq;

            // Creating the root of the trie
            Node *root = new Node();

            // Filling the trie with word and freq from file given
            while (infile >> word >> freq)
            {
                root->add_word(word + "$", freq);
            }

            auto results_vect = search_approx(root, "davis", 2);
            print_node_vect(results_vect);
        }

        return 0;
    }
}
