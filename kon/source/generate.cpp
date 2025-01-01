// Random Test Data Generator

#include <bits/stdc++.h>

typedef char char_t;

typedef long long int int_t;

std::mt19937_64 mersenne_twister;

int_t get_random_number(int_t minimum, int_t maximum);

int32_t main(int32_t argument_count, char_t **argument)
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    assert(argument_count == 3);

    const int_t seed = atoi(argument[1]);
    const int_t query_count = atoi(argument[2]);
    const char_t query_type[] = {'?', 'Z', 'W'};
    int_t vertex_count = 2;

    mersenne_twister.seed(seed);

    std::cout << query_count << '\n';

    for (int_t query_index = 0; query_index < query_count; query_index++)
    {
        uint8_t query_type_index = get_random_number(0, 2);
        int_t vertex = get_random_number(1, vertex_count);

        if (query_type_index != 0)
            vertex_count++;

        std::cout << query_type[query_type_index] << ' ' << vertex << '\n';
    }

    return 0;
}

int_t get_random_number(int_t minimum, int_t maximum)
{
    return std::uniform_int_distribution<int_t>(minimum, maximum)(mersenne_twister);
}
