#include <iostream>
#include <string>

#include "algorithm/patricia_trie.hh"

using namespace std;

int main(int argc, char** argv)
{
    PatriciaTrie* trie = new PatriciaTrie();
    trie->setValue(21);

    cout << "Compiler ... " << trie->getValue() << endl;

    return 0;
}