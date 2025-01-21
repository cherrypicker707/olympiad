// Solution for the Subproblems I and II
// 19/100 points

#include <bits/stdc++.h>

typedef bool bool_t;
typedef std::vector<bool_t> vecbool_t;
typedef long long int int_t;

std::string initial_genotype;
int_t genotype_length, day_count;

void solve_1();

int32_t main()
{
    std::cin >> genotype_length >> day_count >> initial_genotype;

    solve_1();

    return 0;
}

void solve_1()
{
    vecbool_t gene_sequence(genotype_length + day_count);

    for (int_t gene_index = 0; gene_index < genotype_length; gene_index++)
        gene_sequence[gene_index] = (initial_genotype[gene_index] == '1');

    for (int_t gene_index = genotype_length; gene_index < genotype_length + day_count; gene_index++)
        gene_sequence[gene_index] = (gene_sequence[gene_index - genotype_length] != gene_sequence[gene_index - genotype_length + 1]);

    for (int_t gene_index = day_count; gene_index < day_count + genotype_length; gene_index++)
    {
        if (gene_sequence[gene_index])
        {
            std::cout << 1;
            continue;
        }

        std::cout << 0;
    }

    std::cout << '\n';
}
