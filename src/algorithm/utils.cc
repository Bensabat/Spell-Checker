#include "utils.hh"

// Function that compares 2 strings and decomposes its into the common part and the 2 non-common parts
// ie: (david, dadou) -> (da, vid, dou)
tuple<string, string, string> common_prefix_decomposition(string word1, string word2)
{
    string common("");
    size_t length_word1 = word1.length();
    size_t length_word2 = word2.length();    
    size_t min_length = min(length_word1, length_word2);
    size_t i = 0;

    // Getting the common part
    while((i < min_length) && (word1[i] == word2[i]))
    {
        common[i] = word1[i];
        i++;
    }
    common[i] = '\0';

    // Getting the non-common part
    string rest_word1 = word1.substr(i, length_word1 - i);
    string rest_word2 = word2.substr(i, length_word2 - i);

    // Creating and return the tuple
    auto tuple_elements = make_tuple(common.c_str(), rest_word1, rest_word2);
    return tuple_elements;
}
