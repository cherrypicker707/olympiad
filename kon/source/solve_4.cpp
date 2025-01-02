// Solution for the Subproblem III
// 35/100 points

#include <bits/stdc++.h>

typedef char char_t;

typedef long long int int_t;
typedef std::vector<int_t> vecint_t;
typedef std::vector<vecint_t> vecvecint_t;

const int_t root = -1;

void set_children(vecvecint_t &tree_children, vecint_t &root_children, vecint_t &tree_parent);
void set_depth(vecint_t &tree_depth, vecvecint_t &tree_children, vecint_t &root_children);
void set_depth_dfs(int_t vertex, int_t depth, int_t parent, vecint_t &tree_depth, vecvecint_t &tree_children);

int32_t main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int_t query_count, current_vertex_count = 0;

    vecint_t bottom_pointer, top_pointer;

    vecint_t tree_parent, tree_depth;
    vecint_t root_children;
    vecvecint_t tree_children;

    vecint_t question;

    bottom_pointer.push_back(1);
    top_pointer.push_back(root);
    tree_parent.push_back(root);
    current_vertex_count++;

    bottom_pointer.push_back(0);
    top_pointer.push_back(root);
    tree_parent.push_back(root);
    current_vertex_count++;

    std::cin >> query_count;

    for (int_t query_index = 0; query_index < query_count; query_index++)
    {
        char_t query_type;
        int_t current_vertex_index;

        std::cin >> query_type >> current_vertex_index;
        current_vertex_index--;

        if (query_type == 'W')
        {
            bottom_pointer.push_back(current_vertex_index);
            top_pointer.push_back(tree_parent[current_vertex_index]);

            tree_parent.push_back(bottom_pointer[current_vertex_index]);
            bottom_pointer[current_vertex_index] = current_vertex_count;

            current_vertex_count++;

            continue;
        }

        if (query_type == 'Z')
        {
            bottom_pointer.push_back(bottom_pointer[current_vertex_index]);
            top_pointer.push_back(top_pointer[current_vertex_index]);

            tree_parent.push_back(tree_parent[current_vertex_index]);
            tree_parent[current_vertex_index] = current_vertex_count;

            current_vertex_count++;

            continue;
        }

        if (query_type == '?')
        {
            question.push_back(current_vertex_index);

            continue;
        }
    }

    set_children(tree_children, root_children, tree_parent);
    set_depth(tree_depth, tree_children, root_children);

    for (int_t current_vertex_index : question)
    {
        int_t bottom_depth, top_depth;

        bottom_depth = tree_depth[bottom_pointer[current_vertex_index]];
        top_depth = 0;

        if (top_pointer[current_vertex_index] != root)
            top_depth = tree_depth[top_pointer[current_vertex_index]];

        int_t answer = bottom_depth - top_depth;

        std::cout << answer << '\n';
    }

    return 0;
}

void set_children(vecvecint_t &tree_children, vecint_t &root_children, vecint_t &tree_parent)
{
    int_t vertex_count = tree_parent.size();

    tree_children.resize(vertex_count);

    for (int_t vertex_index = 0; vertex_index < vertex_count; vertex_index++)
    {
        if (tree_parent[vertex_index] == root)
        {
            root_children.push_back(vertex_index);
            continue;
        }

        tree_children[tree_parent[vertex_index]].push_back(vertex_index);
    }
}

void set_depth(vecint_t &tree_depth, vecvecint_t &tree_children, vecint_t &root_children)
{
    int_t vertex_count = tree_children.size();

    tree_depth.resize(vertex_count);

    for (int_t root_child : root_children)
        set_depth_dfs(root_child, 1, -1, tree_depth, tree_children);
}

void set_depth_dfs(int_t vertex, int_t depth, int_t parent, vecint_t &tree_depth, vecvecint_t &tree_children)
{
    tree_depth[vertex] = depth;

    for (int_t child : tree_children[vertex])
    {
        if (child == parent)
            continue;

        set_depth_dfs(child, depth + 1, vertex, tree_depth, tree_children);
    }
}
