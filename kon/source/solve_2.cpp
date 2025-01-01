// Solution for the Subproblem II
// 10/100 points

#include <bits/stdc++.h>

typedef bool bool_t;
typedef std::vector<bool_t> vecbool_t;

typedef char char_t;

typedef long long int int_t;
typedef std::vector<int_t> vecint_t;
typedef std::vector<vecint_t> vecvecint_t;

int32_t main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int_t query_count;
    vecbool_t group;
    int_t left_group_count = 1, right_group_count = 1;

    std::cin >> query_count;

    group.push_back(false);
    group.push_back(true);

    for (int_t query_index = 0; query_index < query_count; query_index++)
    {
        char_t current_query_type;
        int_t current_vertex;

        std::cin >> current_query_type >> current_vertex;
        current_vertex--;

        switch (current_query_type)
        {
        case '?':
            if (group[current_vertex])
            {
                std::cout << left_group_count << '\n';
                break;
            }

            std::cout << right_group_count << '\n';
            break;
        case 'Z':
            if (group[current_vertex])
            {
                group.push_back(true);
                right_group_count++;
                break;
            }

            group.push_back(false);
            left_group_count++;
            break;
        }
    }

    return 0;
}
