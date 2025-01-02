#include <bits/stdc++.h>

typedef bool bool_t;

typedef char char_t;

typedef long long int int_t;
typedef std::set<int_t> setint_t;

std::mt19937_64 mersenne_twister;

int_t get_random_number(int_t minimum, int_t maximum);
int_t get_random_element(setint_t &set);
void print_random_tree(int_t vertex_count);

int32_t main(int32_t argument_count, char_t **argument)
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie();

    assert(argument_count == 4);
    const int_t seed = atoi(argument[1]);
    const int_t vertex_count = atoi(argument[2]);
    const int_t initial_vertex_count = atoi(argument[3]);
    setint_t initial_vertices;

    mersenne_twister.seed(seed);

    std::cout << vertex_count << ' ' << initial_vertex_count << '\n';

    while (initial_vertices.size() != initial_vertex_count)
        initial_vertices.insert(get_random_number(1, vertex_count));

    for (int_t initial_vertex : initial_vertices)
        std::cout << initial_vertex << ' ';
    std::cout << '\n';

    print_random_tree(vertex_count);
}

int_t get_random_number(int_t minimum, int_t maximum)
{
    return std::uniform_int_distribution<int_t>(minimum, maximum)(mersenne_twister);
}

int_t get_random_element(setint_t &set)
{
    auto iterator = set.begin();
    std::advance(iterator, get_random_number(0, set.size() - 1));
    return *iterator;
}

void print_random_tree(int_t vertex_count)
{
    int_t root = get_random_number(1, vertex_count);
    setint_t used_vertices, unused_vertices;

    for (int_t index = 1; index <= vertex_count; index++)
        unused_vertices.insert(index);

    used_vertices.insert(root);
    unused_vertices.erase(root);

    while (!unused_vertices.empty())
    {
        int_t random_used_vertex = get_random_element(used_vertices);
        int_t random_unused_vertex = get_random_element(unused_vertices);

        used_vertices.insert(random_unused_vertex);
        unused_vertices.erase(random_unused_vertex);

        bool_t used_first = get_random_number(0, 1);
        if (used_first)
        {
            std::cout << random_used_vertex << ' ' << random_unused_vertex << '\n';
            continue;
        }

        std::cout << random_unused_vertex << ' ' << random_used_vertex << '\n';
    }
}
