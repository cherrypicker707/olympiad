// Solution for the Subproblem I, II, III and IV
// 100/100 points

#include <bits/stdc++.h>

typedef char char_t;

typedef long long int int_t;
typedef std::vector<int_t> vecint_t;
typedef std::vector<vecint_t> vecvecint_t;

typedef std::pair<char_t, int_t> paircharint_t;
typedef std::vector<paircharint_t> vecpaircharint_t;

class segment_tree_t
{
  public:
    void resize(int_t new_count);
    void add(int_t position, int_t value);
    int_t get_sum(int_t left_bound, int_t right_bound);

  private:
    int_t count;
    vecint_t tree;
};

int_t query_count;
vecpaircharint_t query;

int_t vertex_count = 0;
vecint_t tree_parent;
vecvecint_t tree_child;

vecint_t vertex_left_bound, vertex_right_bound;

void solve_4();

void set_children();
int_t set_bounds(int_t vertex, int_t parent, int_t time);

int32_t main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> query_count;

    query.resize(query_count);

    for (int_t query_index = 0; query_index < query_count; query_index++)
        std::cin >> query[query_index].first >> query[query_index].second;

    solve_4();

    return 0;
}

void segment_tree_t::resize(int_t new_count)
{
    count = new_count;
    tree.resize(2 * new_count, 0);
}

void segment_tree_t::add(int_t position, int_t value)
{
    assert(position >= 0);
    assert(position < count);

    position += count;

    while (position > 0)
    {
        tree[position] += value;
        position /= 2;
    }
}

int_t segment_tree_t::get_sum(int_t left_bound, int_t right_bound)
{
    int_t sum = 0;

    left_bound += count;
    right_bound += count;

    while (left_bound < right_bound)
    {
        if (left_bound % 2)
            sum += tree[left_bound++];

        if (right_bound % 2)
            sum += tree[--right_bound];

        left_bound /= 2;
        right_bound /= 2;
    }

    return sum;
}

void solve_4()
{
    vecint_t bottom_pointer, top_pointer;
    vecint_t question;
    segment_tree_t segment_tree;
    int_t local_vertex_count;

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
    }

    tree_child.resize(vertex_count);
    set_children();

    vertex_left_bound.resize(vertex_count);
    vertex_right_bound.resize(vertex_count);
    set_bounds(0, -1, 0);

    segment_tree.resize(2 * vertex_count);

    segment_tree.add(vertex_left_bound[1], 1);
    segment_tree.add(vertex_right_bound[1], -1);

    segment_tree.add(vertex_left_bound[2], 1);
    segment_tree.add(vertex_right_bound[2], -1);

    local_vertex_count = 3;
    for (paircharint_t current_query : query)
    {
        char_t query_type = current_query.first;
        int_t current_vertex = current_query.second;

        if (query_type == 'W' || query_type == 'Z')
        {
            segment_tree.add(vertex_left_bound[local_vertex_count], 1);
            segment_tree.add(vertex_right_bound[local_vertex_count], -1);

            local_vertex_count++;
            continue;
        }

        if (query_type == '?')
        {
            int_t current_vertex_left_bound = vertex_left_bound[top_pointer[current_vertex]] + 1;
            int_t current_vertex_right_bound = vertex_left_bound[bottom_pointer[current_vertex]] + 1;
            int_t answer = segment_tree.get_sum(current_vertex_left_bound, current_vertex_right_bound);

            std::cout << answer << '\n';
            continue;
        }
    }
}

void set_children()
{
    int_t vertex_count = tree_parent.size();

    for (int_t vertex_index = 1; vertex_index < vertex_count; vertex_index++)
        tree_child[tree_parent[vertex_index]].push_back(vertex_index);
}

int_t set_bounds(int_t vertex, int_t parent, int_t time)
{
    vertex_left_bound[vertex] = time++;

    for (int_t child : tree_child[vertex])
    {
        if (child == parent)
            continue;

        time = set_bounds(child, vertex, time);
    }

    vertex_right_bound[vertex] = time++;

    return time;
}
