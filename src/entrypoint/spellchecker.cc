#include <iostream>
#include <string>

#include "algorithm/patricia_trie.hh"
#include "third_party/json.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char** argv)
{
    json j = {
        { "currency", "USD" },
        { "value", 42.99 },
    };

    cout << "Spellchecker ..." << endl;
    cout << j.dump(4) << endl;

    return 0;
}