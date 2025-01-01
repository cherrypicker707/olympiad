// Solution for the Subproblem I and II
// 30/100 points

#include <bits/stdc++.h>

typedef bool bool_t;
typedef std::vector<bool_t> vecbool_t;

typedef char char_t;

typedef long long int int_t;
typedef std::vector<int_t> vecint_t;
typedef std::vector<vecint_t> vecvecint_t;

int_t query_count;

void solve_1();
void solve_2();

int32_t main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> query_count;

    if (query_count <= 5000)
    {
        solve_1();
        return 0;
    }

    solve_2();
    return 0;
}

void solve_1()
{
    vecvecint_t graph;

    graph.push_back({1});
    graph.push_back({0});

    for (int_t query_index = 0; query_index < query_count; query_index++)
    {
        char_t current_query_type;
        int_t current_vertex;

        std::cin >> current_query_type >> current_vertex;
        current_vertex--;

        int_t new_vertex = graph.size();
        switch (current_query_type)
        {
        case '?':
            std::cout << graph[current_vertex].size() << '\n';
            break;
        case 'W':
            graph.push_back({});
            graph[new_vertex].push_back(current_vertex);
            graph[current_vertex].push_back(new_vertex);
            break;
        case 'Z':
            graph.push_back({});
            for (int_t neighbour_index = 0; neighbour_index < graph[current_vertex].size(); neighbour_index++)
            {
                int_t neigbour_vertex = graph[current_vertex][neighbour_index];
                graph[new_vertex].push_back(neigbour_vertex);
                graph[neigbour_vertex].push_back(new_vertex);
            }
            break;
        }
    }
}

void solve_2()
{
    vecbool_t group;
    int_t left_group_count = 1, right_group_count = 1;

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
}
