// Invalid Solution for the Subproblem III
// 0/100 points
// This solution does not satisfy the time limits. I made it according to the editorial, yet it does not work.

#include <bits/stdc++.h>

typedef long long int int_t;
typedef std::vector<int_t> vecint_t;

int_t given_number, sequence_fragment_left_bound, sequence_fragment_right_bound, sequence_fragment_count;
int_t given_number_prime_factor_count;
vecint_t given_number_prime_factor;

void set_given_number_prime_factors();
int_t find_sequence_element(int_t sequence_element_index);
int_t get_coprime_count_on_prefix(int_t prefix_lenght);

void solve_3();

int32_t main()
{
    std::cin >> given_number >> sequence_fragment_left_bound >> sequence_fragment_count;
    sequence_fragment_right_bound = sequence_fragment_left_bound + sequence_fragment_count;

    solve_3();

    return 0;
}

void solve_3()
{
    set_given_number_prime_factors();

    for (int_t sequence_element_index = sequence_fragment_left_bound; sequence_element_index < sequence_fragment_right_bound; sequence_element_index++)
        std::cout << find_sequence_element(sequence_element_index) << ' ';
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

int_t find_sequence_element(int_t sequence_element_index)
{
    int_t left_bound = 1, right_bound = 8 * sequence_fragment_right_bound, result = -1;

    while (left_bound < right_bound)
    {
        int_t current_number = (left_bound + right_bound) / 2;

        if (get_coprime_count_on_prefix(current_number) < sequence_element_index)
        {
            left_bound = current_number + 1;
            continue;
        }

        result = current_number;
        right_bound = current_number;
    }

    return result;
}

int_t get_coprime_count_on_prefix(int_t prefix_lenght)
{
    int_t combination_count = 1 << given_number_prime_factor_count, coprime_count = 0;

    for (int_t combination = 0; combination < combination_count; combination++)
    {
        int_t current_prime_factor_count = 0, product = 1, coefficient = 1;

        for (int_t given_number_prime_factor_index = 0; given_number_prime_factor_index < given_number_prime_factor_count; given_number_prime_factor_index++)
        {
            if (((1 << given_number_prime_factor_index) & combination) == 0)
                continue;

            current_prime_factor_count++;
            product *= given_number_prime_factor[given_number_prime_factor_index];
        }

        if (current_prime_factor_count % 2)
            coefficient = -1;

        coprime_count += coefficient * (prefix_lenght / product);
    }

    return coprime_count;
}
