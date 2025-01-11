// Flawed Solution for All Subproblems
// 36/100 points
// This solution was meant to be a full solution, but unfortunately for some reason it does not work exactly as expected and works only on a few first subproblems.
// If you know what is wrong with it, you can let me know.

#include <bits/stdc++.h>

#define MINUS_INFINITY -1'000'000'000LL

typedef long long int int_t;
typedef std::vector<int_t> vecint_t;
typedef std::vector<vecint_t> vecvecint_t;

int_t city_count, agent_count;
vecint_t agent, city_is_agent;
vecvecint_t city_neighbour;

vecint_t dp_up, dp_down, dp;

void solve_2();

void set_dp(int_t vertex, int_t parent);

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

    solve_2();
}

void solve_2()
{
    city_is_agent.resize(city_count, false);
    for (int_t agent_index = 0; agent_index < agent_count; agent_index++)
        city_is_agent[agent[agent_index]] = true;

    dp_down.resize(city_count, -1);
    dp_up.resize(city_count, -1);
    dp.resize(city_count, -1);

    set_dp(0, -1);
    int_t answer = 2 * (city_count - agent_count) - dp[0];

    std::cout << answer << '\n';
}

void set_dp(int_t vertex, int_t parent)
{
    int_t sum = 0;
    int_t maximal_dp_down_difference = MINUS_INFINITY;
    int_t maximal_dp_up_difference = MINUS_INFINITY;
    int_t second_maximal_dp_down_difference = MINUS_INFINITY;
    int_t second_maximal_dp_up_difference = MINUS_INFINITY;
    int_t maximal_dp_down_difference_index = -1;
    int_t maximal_dp_up_difference_index = -1;
    int_t alternative_value;

    for (int_t child : city_neighbour[vertex])
    {
        int_t current_dp_down_difference, current_dp_up_difference;

        if (child == parent)
            continue;

        set_dp(child, vertex);

        current_dp_down_difference = dp_down[child] - dp[child];
        current_dp_up_difference = dp_up[child] - dp[child];

        sum += dp[child];

        if (current_dp_down_difference > maximal_dp_down_difference)
        {
            maximal_dp_down_difference = current_dp_down_difference;
            maximal_dp_down_difference_index = child;
        }

        if (current_dp_up_difference > maximal_dp_up_difference)
        {
            maximal_dp_up_difference = current_dp_up_difference;
            maximal_dp_up_difference_index = child;
        }
    }

    for (int_t child : city_neighbour[vertex])
    {
        int_t current_dp_down_difference, current_dp_up_difference;

        if (child == parent)
            continue;

        current_dp_down_difference = dp_down[child] - dp[child];
        current_dp_up_difference = dp_up[child] - dp[child];

        if (child != maximal_dp_down_difference_index && current_dp_down_difference > second_maximal_dp_down_difference)
            second_maximal_dp_down_difference = current_dp_down_difference;

        if (child != maximal_dp_up_difference_index && current_dp_up_difference > second_maximal_dp_up_difference)
            second_maximal_dp_up_difference = current_dp_up_difference;
    }

    if (city_is_agent[vertex])
    {
        dp_down[vertex] = MINUS_INFINITY;
        dp_up[vertex] = sum;
        dp[vertex] = std::max(sum, sum + maximal_dp_down_difference + 1);

        return;
    }

    dp_down[vertex] = std::max(sum + maximal_dp_down_difference + 1, 0LL);
    dp_up[vertex] = sum + maximal_dp_up_difference + 1;
    dp[vertex] = std::max(sum, dp_up[vertex]);

    alternative_value = sum + maximal_dp_down_difference + maximal_dp_up_difference + 2;
    if (maximal_dp_down_difference_index == maximal_dp_up_difference_index)
        alternative_value = std::max(sum + second_maximal_dp_down_difference + maximal_dp_up_difference + 2, sum + maximal_dp_down_difference + second_maximal_dp_up_difference + 2);
    dp[vertex] = std::max(dp[vertex], alternative_value);

    return;
}
