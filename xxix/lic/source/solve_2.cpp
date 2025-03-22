// Solution for the Subproblem I and II
// 46/100 points

#include <bits/stdc++.h>

typedef long long int int_t;
typedef std::vector<int_t> vecint_t;
typedef std::set<int_t> setint_t;

int_t given_number, sequence_fragment_left_bound, sequence_fragment_right_bound, sequence_fragment_count;
int_t given_number_prime_factor_count;
vecint_t given_number_prime_factor;

void set_given_number_prime_factors();

void solve_2();

int32_t main()
{
    int_t array_count;

    std::cin >> given_number >> sequence_fragment_left_bound >> sequence_fragment_count;
    sequence_fragment_right_bound = sequence_fragment_left_bound + sequence_fragment_count;

    solve_2();

    return 0;
}

void solve_2()
{
    int_t first_coprime = 0, last_coprime = 0;
    int_t previous_non_coprime = 0, coprime_count = 0;
    setint_t non_coprimes;

    set_given_number_prime_factors();

    for (int_t given_number_prime_factor_index = 0; given_number_prime_factor_index < given_number_prime_factor_count; given_number_prime_factor_index++)
    {
        int_t current_number = given_number_prime_factor[given_number_prime_factor_index];

        while (current_number <= given_number)
        {
            non_coprimes.insert(current_number);
            current_number += given_number_prime_factor[given_number_prime_factor_index];
        }
    }

    for (int_t non_coprime : non_coprimes)
    {
        coprime_count += (non_coprime - previous_non_coprime - 1);

        if (coprime_count >= sequence_fragment_left_bound && first_coprime == 0)
            first_coprime = non_coprime + sequence_fragment_left_bound - coprime_count - 1;

        if (coprime_count >= sequence_fragment_right_bound && last_coprime == 0)
            last_coprime = non_coprime + sequence_fragment_right_bound - coprime_count - 1;

        previous_non_coprime = non_coprime;
    }

    for (int_t current_number = first_coprime; current_number <= last_coprime; current_number++)
    {
        if (non_coprimes.count(current_number))
            continue;

        std::cout << current_number << ' ';
    }

    std::cout << '\n';
}

void set_given_number_prime_factors()
{
    int_t current_number = given_number;

    for (int_t factor = 2; factor * factor <= current_number; factor++)
    {
        if (current_number % factor == 0)
            given_number_prime_factor.push_back(factor);

        while (current_number % factor == 0)
            current_number /= factor;
    }

    if (current_number != 1)
        given_number_prime_factor.push_back(current_number);

    given_number_prime_factor_count = given_number_prime_factor.size();
}
