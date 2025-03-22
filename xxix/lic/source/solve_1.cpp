// Solution for the Subproblem I
// 10/100 points

#include <bits/stdc++.h>

typedef long long int int_t;
typedef std::vector<int_t> vecint_t;

int_t given_number, sequence_fragment_left_bound, sequence_fragment_right_bound, sequence_fragment_count;

void solve_1();

int32_t main()
{
    std::cin >> given_number >> sequence_fragment_left_bound >> sequence_fragment_count;
    sequence_fragment_right_bound = sequence_fragment_left_bound + sequence_fragment_count;

    solve_1();

    return 0;
}

void solve_1()
{
    int_t current_number = 0, coprime_count = 0;

    while (coprime_count < sequence_fragment_right_bound)
    {
        int_t gcd = std::gcd(++current_number, given_number);

        if (gcd != 1)
            continue;

        coprime_count++;

        if (coprime_count >= sequence_fragment_left_bound)
            std::cout << current_number << ' ';
    }

    std::cout << '\n';
}
