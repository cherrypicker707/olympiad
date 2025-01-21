// Solution for All Subproblems
// 100/100

#include <bits/stdc++.h>

typedef long long int int_t;

typedef std::bitset<700> bitset_t;
typedef std::vector<bitset_t> vecbitset_t;
typedef struct
{
    vecbitset_t left, right;
} matrix_t;

std::string initial_genotype;
int_t genotype_length, day_count;

matrix_t operator*(const matrix_t &left_matrix, const matrix_t &right_matrix);
bitset_t operator*(const matrix_t &matrix, const bitset_t &vector);
matrix_t get_matrix_power(const matrix_t &matrix, int_t exponent);

void solve_3();

int32_t main()
{
    std::cin >> genotype_length >> day_count >> initial_genotype;

    solve_3();

    return 0;
}

void solve_3()
{
    bitset_t vector;
    matrix_t matrix;
    matrix.left = vecbitset_t(genotype_length);
    matrix.right = vecbitset_t(genotype_length);

    for (int_t gene_index = 0; gene_index < genotype_length; gene_index++)
        vector[gene_index] = (initial_genotype[gene_index] == '1');

    for (int_t index = 0; index < genotype_length - 1; index++)
        matrix.left[index][index + 1] = matrix.right[index + 1][index] = true;

    matrix.left[genotype_length - 1][0] = matrix.right[0][genotype_length - 1] = true;
    matrix.left[genotype_length - 1][1] = matrix.right[1][genotype_length - 1] = true;

    matrix_t matrix_power = get_matrix_power(matrix, day_count);
    bitset_t result = matrix_power * vector;

    for (int_t gene_index = 0; gene_index < genotype_length; gene_index++)
        std::cout << result[gene_index];
    std::cout << '\n';
}

matrix_t operator*(const matrix_t &left, const matrix_t &right)
{
    assert(left.left.size());
    assert(right.right.size());

    matrix_t product;
    product.left = vecbitset_t(left.left.size());
    product.right = vecbitset_t(right.right.size());

    for (int_t row = 0; row < product.left.size(); row++)
    {
        for (int_t column = 0; column < product.right.size(); column++)
        {
            bitset_t bitset = left.left[row] & right.right[column];
            product.left[row][column] = product.right[column][row] = bitset.count() % 2;
        }
    }

    return product;
}

bitset_t operator*(const matrix_t &matrix, const bitset_t &vector)
{
    assert(matrix.left.size());

    bitset_t product;

    for (int_t component = 0; component < matrix.left.size(); component++)
    {
        bitset_t bitset = matrix.left[component] & vector;
        product[component] = bitset.count() % 2;
    }

    return product;
}

matrix_t get_matrix_power(const matrix_t &matrix, int_t exponent)
{
    matrix_t factor, result;

    if (exponent == 1)
        return matrix;

    factor = get_matrix_power(matrix, exponent / 2);
    result = factor * factor;

    if (exponent % 2)
        result = matrix * result;

    return result;
}
