#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

#include "../algorithm/utils.hh"
#include "../algorithm/distance.hh"
#include "../algorithm/patricia_trie.hh"
#include "../algorithm/trie.hh"

using namespace std;

void print_node_vect(vector<tuple<string, size_t, size_t>> results_vect)
{
    cout << "This vector contained " << results_vect.size() << " words:\n" << endl;
    for(auto tuple : results_vect)
    {
        cout << "(" << get<0>(tuple) << ", " << get<1>(tuple) << ", " << get<2>(tuple) << ")" << endl;
    }
    cout << "\nThis vector contained " << results_vect.size() << " words!\n" << endl;
}

int main(int argc, char** argv)
{
    // Test du common_prefix
    if (argc == 1)
    {
        string pipe_word1, pipe_word2;
        cin >> pipe_word1 >> pipe_word2;

        auto tuple_dec = common_prefix_decomposition(pipe_word1, pipe_word2);

        cout << "[" << get<0>(tuple_dec) << ", " << get<1>(tuple_dec) << ", " << get<2>(tuple_dec) << "]" << endl;

        return 0;
    }

    if (argc != 3)
    {
        cerr << "Please enter ./TextMiningCompiler /path/to/words.txt /path/to/dict.bin" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (infile.is_open())
    {
        cout << "Opened" << endl;

        string word;
        int freq;

        // Creating the root of the trie (or patricia)
        //Trie *root = new Trie();
        Patricia_trie *root = new Patricia_trie();        

        // Filling the trie with word and freq from file given
        while (infile >> word >> freq)
        {
            root->add_word(root, word + "$", freq);
        }

        cout << "END | size of child: " << root->children_get().size() << endl;
        //root->pretty_printer(root);

        // Getting "approx dist word" by pipe
        string pipe_approx, pipe_dist_max, pipe_word;
        cin >> pipe_approx >> pipe_dist_max >> pipe_word;

        // Launch the search
        auto results_vect = search_ptrie_approx(root, pipe_word, atoi(pipe_dist_max.c_str()));

        // Sort the resulting vector
        

        // Print the results
        print_node_vect(results_vect);
    }

    return 0;
}
