// Solution for the Subproblem I
// 20/100 points

#include <bits/stdc++.h>

typedef char char_t;

typedef long long int int_t;
typedef std::vector<int_t> vecint_t;
typedef std::vector<vecint_t> vecvecint_t;

typedef std::pair<char_t, int_t> paircharint_t;
typedef std::vector<paircharint_t> vecpaircharint_t;

int_t query_count;
vecpaircharint_t query;

void solve_1();

int32_t main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> query_count;

    query.resize(query_count);

    for (int_t query_index = 0; query_index < query_count; query_index++)
        std::cin >> query[query_index].first >> query[query_index].second;

    solve_1();

    return 0;
}

void solve_1()
{
    int_t vertex_count;
    vecvecint_t graph;

    // We add an abstract, non-existent '0' vertex for practical purposes.
    graph.push_back({});
    graph.push_back({2});
    graph.push_back({1});
    vertex_count = 3;

    for (int_t query_index = 0; query_index < query_count; query_index++)
    {
        char_t query_type = query[query_index].first;
        int_t current_vertex = query[query_index].second;

        if (query_type == '?')
        {
            std::cout << graph[current_vertex].size() << '\n';

            continue;
        }

        if (query_type == 'W')
        {
            graph.push_back({});

            graph[vertex_count].push_back(current_vertex);
            graph[current_vertex].push_back(vertex_count);

            vertex_count++;
            continue;
        }

        if (query_type == 'Z')
        {
            graph.push_back({});

            for (int_t neighbour_index = 0; neighbour_index < graph[current_vertex].size(); neighbour_index++)
            {
                int_t neigbour_vertex = graph[current_vertex][neighbour_index];
                graph[vertex_count].push_back(neigbour_vertex);
                graph[neigbour_vertex].push_back(vertex_count);
            }

            vertex_count++;
            continue;
        }
    }
}
