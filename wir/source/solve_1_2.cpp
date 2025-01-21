// Solution for Subproblems I, II and III
// 84/100 points

#include <bits/stdc++.h>

typedef bool bool_t;
typedef std::vector<bool_t> vecbool_t;
typedef std::vector<vecbool_t> matbool_t;
typedef long long int int_t;

std::string initial_genotype;
int_t genotype_length, day_count;

matbool_t operator*(const matbool_t &left_matrix, const matbool_t &right_matrix);
vecbool_t operator*(const matbool_t &matrix, const vecbool_t &vector);
matbool_t get_matrix_power(const matbool_t &matrix, int_t exponent);

void solve_1();
void solve_2();

int32_t main()
{
    std::cin >> genotype_length >> day_count >> initial_genotype;

    if (genotype_length > 100)
    {
        solve_1();
        return 0;
    }

    solve_2();
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

void solve_2()
{
    vecbool_t vector(genotype_length, false);
    matbool_t matrix(genotype_length, vecbool_t(genotype_length, false));

    for (int_t gene_index = 0; gene_index < genotype_length; gene_index++)
        vector[gene_index] = (initial_genotype[gene_index] == '1');

    for (int_t index = 0; index < genotype_length - 1; index++)
        matrix[index][index + 1] = true;

    matrix[genotype_length - 1][0] = true;
    matrix[genotype_length - 1][1] = true;

    matbool_t matrix_power = get_matrix_power(matrix, day_count);
    vecbool_t result = matrix_power * vector;

    for (int_t gene_index = 0; gene_index < genotype_length; gene_index++)
        std::cout << result[gene_index];
    std::cout << '\n';
}

matbool_t operator*(const matbool_t &left, const matbool_t &right)
{
    assert(left.size());
    assert(left[0].size());
    assert(right.size());
    assert(right[0].size());
    assert(left[0].size() == right.size());

    matbool_t product(left.size(), vecbool_t(right[0].size(), false));

    for (int_t row = 0; row < product.size(); row++)
    {
        for (int_t column = 0; column < product[0].size(); column++)
        {
            for (int_t index = 0; index < right.size(); index++)
                product[row][column] = (product[row][column] != (left[row][index] && right[index][column]));
        }
    }

    return product;
}

vecbool_t operator*(const matbool_t &matrix, const vecbool_t &vector)
{
    assert(matrix.size());
    assert(matrix[0].size());
    assert(vector.size());
    assert(matrix[0].size() == vector.size());

    vecbool_t product(matrix.size(), false);

    for (int_t component = 0; component < product.size(); component++)
    {
        for (int_t index = 0; index < vector.size(); index++)
            product[component] = (product[component] != (matrix[component][index] && vector[index]));
    }

    return product;
}

matbool_t get_matrix_power(const matbool_t &matrix, int_t exponent)
{
    matbool_t factor, result;

    if (exponent == 1)
        return matrix;

    factor = get_matrix_power(matrix, exponent / 2);
    result = factor * factor;

    if (exponent % 2)
        result = matrix * result;

    return result;
}
