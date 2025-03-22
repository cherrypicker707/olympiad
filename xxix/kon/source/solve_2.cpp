// Solution for the Subproblem II
// 10/100 points

#include <bits/stdc++.h>

typedef bool bool_t;
typedef std::vector<bool_t> vecbool_t;

typedef char char_t;

typedef long long int int_t;
typedef std::vector<int_t> vecint_t;
typedef std::vector<vecint_t> vecvecint_t;

typedef std::pair<char_t, int_t> paircharint_t;
typedef std::vector<paircharint_t> vecpaircharint_t;

int_t query_count;
vecpaircharint_t query;

void solve_2();

int32_t main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> query_count;

    query.resize(query_count);

    for (int_t query_index = 0; query_index < query_count; query_index++)
        std::cin >> query[query_index].first >> query[query_index].second;

    solve_2();

    return 0;
}

void solve_2()
{
    int_t left_group_count = 1, right_group_count = 1;
    vecbool_t group;

    // We add an abstract, non-existent '0' vertex for practical purposes.
    group.push_back(false);
    group.push_back(false);
    group.push_back(true);

    for (int_t query_index = 0; query_index < query_count; query_index++)
    {
        char_t query_type = query[query_index].first;
        int_t current_vertex = query[query_index].second;

        if (query_type == '?')
        {
            if (group[current_vertex])
            {
                std::cout << left_group_count << '\n';
                continue;
            }

            std::cout << right_group_count << '\n';
            continue;
        }

        if (query_type == 'Z')
        {
            if (group[current_vertex])
            {
                group.push_back(true);
                right_group_count++;
                continue;
            }

            group.push_back(false);
            left_group_count++;
            continue;
        }
    }
}
