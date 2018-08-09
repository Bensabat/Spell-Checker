#include <iostream>
#include <string>

#include "../algorithm/utils.hh"
#include "../algorithm/distance.hh"
#include "../algorithm/patricia_trie.hh"
#include "../algorithm/trie.hh"

using namespace std;

void print_node_vect(vector<tuple<string, size_t, size_t>> results_vect)
{
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
        string dict_path = argv[1];
        ifstream input_stream(dict_path, ios::binary);
        auto *deserialized_trie = Patricia_trie::deserialize(input_stream);
        input_stream.close();


        string pipe_approx, pipe_dist_max, pipe_word;
        cin >> pipe_approx >> pipe_dist_max >> pipe_word;
        int flag = pipe_approx.size();
        int i = 0;

        while (flag != 0 && i < 4)
        {
            // Launch the search
            auto results_vect = search_ptrie_approx(deserialized_trie, pipe_word, atoi(pipe_dist_max.c_str()));

            // Print the results
            print_node_vect(results_vect);

            // Getting "approx dist word" by pipe
            string pipe_approx;
            string new_line;
            cin >> new_line;

            // cat style
            if (new_line == "approx")
            {
                pipe_approx = new_line;
                cin >> pipe_dist_max >> pipe_word >> new_line;
            }

            // echo style
            else
            {
                cin >> pipe_approx >> pipe_dist_max >> pipe_word >> new_line;
            }
            
            flag = pipe_approx.size();

            i++;
        }

        return 0;
    }
}
