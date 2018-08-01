#include "distance.hh"

size_t distance(string word1, string word2)
{
    size_t i, j, dist;
    const size_t length1 = word1.length();
    const size_t length2 = word2.length();

    vector<vector<size_t>> d(length1 + 1, vector<size_t>(length2 + 1));
    
    for (i = 0; i <= length1; ++i)
        d[i][0] = i;
    
    for (j = 1; j <= length2; ++j)
        d[0][j] = j;

    for (i = 1; i <= length1; ++i)
        for (j = 1; j <= length2; ++j)
        {
            dist = !(word1[i - 1] == word2[j - 1]);

            d[i][j] = min({
                d[i - 1][j] + 1, // deletion
                d[i][j - 1] + 1, // insertion
                d[i - 1][j - 1] + dist // substitution or equal
            });

            if (i > 1 && j > 1 && word1[i - 1] == word2[j - 2] && word1[i - 2] == word2[j - 1])
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + dist); // transposition
        }

    return d[length1][length2];
}