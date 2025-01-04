// Solution for the Subproblem III
// 35/100 points

#include <bits/stdc++.h>

typedef char char_t;

typedef long long int int_t;
typedef std::vector<int_t> vecint_t;
typedef std::vector<vecint_t> vecvecint_t;

typedef std::pair<char_t, int_t> paircharint_t;
typedef std::vector<paircharint_t> vecpaircharint_t;

int_t query_count;
vecpaircharint_t query;

int_t vertex_count = 0;
vecint_t tree_parent, tree_depth;
vecvecint_t tree_child;

void solve_3();

void set_children();
void set_depth(int_t vertex, int_t depth, int_t parent);

int32_t main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> query_count;

    query.resize(query_count);

    for (int_t query_index = 0; query_index < query_count; query_index++)
        std::cin >> query[query_index].first >> query[query_index].second;

    solve_3();

    return 0;
}

void solve_3()
{
    vecint_t bottom_pointer, top_pointer;
    vecint_t question;

    // We add an abstract, non-existent '0' vertex for practical purposes.
    bottom_pointer.push_back(0);
    top_pointer.push_back(0);
    tree_parent.push_back(-1);
    vertex_count++;

    bottom_pointer.push_back(2);
    top_pointer.push_back(0);
    tree_parent.push_back(0);
    vertex_count++;

    bottom_pointer.push_back(1);
    top_pointer.push_back(0);
    tree_parent.push_back(0);
    vertex_count++;

    for (int_t query_index = 0; query_index < query_count; query_index++)
    {
        char_t query_type = query[query_index].first;
        int_t current_vertex = query[query_index].second;

        if (query_type == 'W')
        {
            bottom_pointer.push_back(current_vertex);
            top_pointer.push_back(tree_parent[current_vertex]);

            tree_parent.push_back(bottom_pointer[current_vertex]);
            bottom_pointer[current_vertex] = vertex_count;

            vertex_count++;

            continue;
        }

        if (query_type == 'Z')
        {
            bottom_pointer.push_back(bottom_pointer[current_vertex]);
            top_pointer.push_back(top_pointer[current_vertex]);

            tree_parent.push_back(tree_parent[current_vertex]);
            tree_parent[current_vertex] = vertex_count;

            vertex_count++;

            continue;
        }

        if (query_type == '?')
        {
            question.push_back(current_vertex);

            continue;
        }
    }

    tree_child.resize(vertex_count);
    set_children();

    tree_depth.resize(vertex_count);
    set_depth(0, 0, -1);

    for (int_t current_vertex : question)
    {
        int_t bottom_depth, top_depth, answer;

        bottom_depth = tree_depth[bottom_pointer[current_vertex]];
        top_depth = tree_depth[top_pointer[current_vertex]];
        answer = bottom_depth - top_depth;

        std::cout << answer << '\n';
    }
}

void set_children()
{
    int_t vertex_count = tree_parent.size();

    for (int_t vertex_index = 1; vertex_index < vertex_count; vertex_index++)
        tree_child[tree_parent[vertex_index]].push_back(vertex_index);
}

void set_depth(int_t vertex, int_t depth, int_t parent)
{
    tree_depth[vertex] = depth;

    for (int_t child : tree_child[vertex])
    {
        if (child == parent)
            continue;

        set_depth(child, depth + 1, vertex);
    }
}
