// Solution for the Subproblem IV
// 10/100 points

#include <bits/stdc++.h>

typedef long long int int_t;
typedef std::vector<int_t> vecint_t;
typedef std::vector<vecint_t> vecvecint_t;

int_t city_count, agent_count;
vecint_t agent;
vecvecint_t city_neighbour;

void solve_1();

int_t get_depth(int_t vertex, int_t parent);

int32_t main()
{
    int_t road_count;

    std::cin >> city_count >> agent_count;

    road_count = city_count - 1;

    city_neighbour.resize(city_count);
    agent.resize(agent_count);

    for (int_t agent_index = 0; agent_index < agent_count; agent_index++)
    {
        std::cin >> agent[agent_index];
        agent[agent_index]--;
    }

    for (int_t road_index = 0; road_index < road_count; road_index++)
    {
        int_t left_city, right_city;

        std::cin >> left_city >> right_city;
        left_city--;
        right_city--;

        city_neighbour[left_city].push_back(right_city);
        city_neighbour[right_city].push_back(left_city);
    }

    solve_1();
}

void solve_1()
{
    int_t depth = get_depth(agent[0], -1);
    int_t answer = 2 * (city_count - 1) - depth;

    std::cout << answer << '\n';
}

int_t get_depth(int_t vertex, int_t parent)
{
    int_t depth = 0;

    for (int_t child : city_neighbour[vertex])
    {
        if (child == parent)
            continue;

        depth = std::max(depth, get_depth(child, vertex) + 1);
    }

    return depth;
}
