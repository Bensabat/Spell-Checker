#include <iostream>
#include <string>

#include "../algorithm/utils.hh"
#include "../algorithm/distance.hh"
#include "../algorithm/patricia_trie.hh"
#include "../algorithm/trie.hh"

using namespace std;
//using json = nlohmann::json;

void print_node_vect(vector<tuple<string, size_t, size_t>> results_vect)
{
    //cout << "This vector contained " << results_vect.size() << " words:\n" << endl;
    cout << "[";
    char commat = '\0';
    for(auto tuple : results_vect)
    {
        cout << commat << "{\"word\":\"" << get<0>(tuple) << "\",\"freq\":" << get<1>(tuple) 
             << ",\"distance\":" << get<2>(tuple) << "}";
        commat = ',';
    }
    cout << "]" << endl;
    //cout << "\nThis vector contained " << results_vect.size() << " words!\n" << endl;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cerr << "Please enter ./TextMiningCompiler /path/to/dict.bin" << endl;
        return 1;
    }

    else
    {
        // Deserialize
        //cout << "\nDeserializing trie" << endl;

        string dict_path = argv[1];
        cout << dict_path << endl;    
        ifstream input_stream(dict_path, ios::binary);
        auto *deserialized_trie = Patricia_trie::deserialize(input_stream);
        input_stream.close();
        //deserialized_trie->pretty_printer(deserialized_trie);

        // Getting "approx dist word" by pipe
        string pipe_approx, pipe_dist_max, pipe_word;
        cin >> pipe_approx >> pipe_dist_max >> pipe_word;

        // Launch the search
        //cout << "\nLaunch the search on deserialise:" << endl;
        auto results_vect = search_ptrie_approx(deserialized_trie, pipe_word, atoi(pipe_dist_max.c_str()));

        // Print the results
        print_node_vect(results_vect);

        return 0;
    }
}
