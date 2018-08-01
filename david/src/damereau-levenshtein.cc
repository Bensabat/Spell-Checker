#include "damereau-levenshtein.hh"


size_t compute_distance(std::string mot_1, std::string mot_2)
{
    const size_t mot_1_len = mot_1.length();
    const size_t mot_2_len = mot_2.length();
    std::vector<std::vector<size_t>> d(mot_1_len + 1, std::vector<size_t>(mot_2_len + 1));
    size_t i, j, dist;

    for(i = 0; i <= mot_1_len; ++i)
        d[i][0] = i;
    
    for(j = 1; j <= mot_2_len; ++j)
        d[0][j] = j;

    for(i = 1; i <= mot_1_len; ++i)
    {
        for(j = 1; j <= mot_2_len; ++j)
        {
            if (mot_1[i - 1] == mot_2[j - 1])
                dist = 0;
            else
                dist = 1;

            d[i][j] = std::min(std::min(d[i - 1][j] + 1, // Deletion
                               d[i][j - 1] + 1),         // insertion
                               d[i - 1][j - 1] + dist);  // substitution or equal

            if (i > 1 && j > 1 && mot_1[i - 1] == mot_2[j - 2] && mot_1[i - 2] == mot_2[j - 1])
            {
                d[i][j] = std::min(d[i][j], d[i - 2][j - 2] + dist); // transposition
            }
        }
    }

    size_t dist_res = d[mot_1_len][mot_2_len];
    return dist_res;
}
