#include <bits/stdc++.h>

typedef bool bool_t;
typedef std::vector<bool_t> vecbool_t;
typedef char char_t;
typedef long long int int_t;

int32_t main(int32_t argument_count, char_t **argument)
{
    assert(argument_count == 4);

    const int_t seed = atoi(argument[1]);
    const int_t genotype_length = atoi(argument[2]);
    const int_t day_count = atoi(argument[3]);

    std::mt19937_64 mersenne_twister(seed);

    std::cout << genotype_length << ' ' << day_count << '\n';

    for (int_t gene_index = 0; gene_index < genotype_length; gene_index++)
        std::cout << (std::uniform_int_distribution<int_t>(0, 1)(mersenne_twister));
    std::cout << '\n';

    return 0;
}
