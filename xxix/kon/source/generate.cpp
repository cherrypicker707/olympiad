// Random Test Data Generator

#include <algorithm>
#include <bits/stdc++.h>

typedef bool bool_t;

typedef char char_t;

typedef long long int int_t;

typedef std::pair<char_t, int_t> paircharint_t;
typedef std::vector<paircharint_t> vecpaircharint_t;

std::mt19937_64 mersenne_twister;

int_t get_random_number(int_t minimum, int_t maximum);

int32_t main(int32_t argument_count, char_t **argument)
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    assert(argument_count == 5);

    const int_t seed = atoi(argument[1]);
    const int_t query_count = atoi(argument[2]);
    const bool_t only_z = atoi(argument[3]);
    const bool_t questions_last = atoi(argument[4]);
    const char_t query_type[] = {'W', 'Z', '?'};

    int_t vertex_count = 2;
    vecpaircharint_t query;

    query.reserve(query_count);

    mersenne_twister.seed(seed);

    std::cout << query_count << '\n';

    for (int_t query_index = 0; query_index < query_count; query_index++)
    {
        uint8_t query_type_index = get_random_number(0, 2);
        int_t vertex = get_random_number(1, vertex_count);

        if (only_z && query_type_index == 0)
            query_type_index = 1;

        if (query_type_index != 2)
            vertex_count++;

        query.push_back({query_type[query_type_index], vertex});
    }

    if (questions_last)
    {
        auto is_not_question = [&](paircharint_t &current_query) { return current_query.first != '?'; };
        std::stable_partition(query.begin(), query.end(), is_not_question);
    }

    for (paircharint_t current_query : query)
        std::cout << current_query.first << ' ' << current_query.second << '\n';

    return 0;
}

int_t get_random_number(int_t minimum, int_t maximum)
{
    return std::uniform_int_distribution<int_t>(minimum, maximum)(mersenne_twister);
}
