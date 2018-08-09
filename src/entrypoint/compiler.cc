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

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        cerr << "Please enter ./TextMiningCompiler /path/to/words.txt /path/to/dict.bin" << endl;
        return 1;
    }

    else
    {
        ifstream infile(argv[1]);
        if (infile.is_open())
        {
            string word;
            int freq;

            // Creating the root of the trie (or patricia)
            cout << "Creating the patricia trie ..." << endl;
            Patricia_trie *root = new Patricia_trie();        

            // Filling the trie with word and freq from file given
            while (infile >> word >> freq)
            {
                root->add_word(root, word + "$", freq);
            }

            infile.close();

            //root->pretty_printer(root);

            // Serialize
            cout << "Serializing patricia trie ..." << endl;     
            string dict_path = argv[2];
            ofstream output_stream(dict_path, ios::binary);
            root->serialize(output_stream);
            output_stream.close();

            cout << "Done !" << endl;
        }
    }

    return 0;
}
