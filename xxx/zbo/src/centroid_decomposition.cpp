// Full Solution
// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;
typedef std::vector<vpll> vvpll;
typedef std::vector<bool> vbool;

class BinaryLift
{
public:
    BinaryLift(vvpll adj);
    ll get_distance(ll u, ll v);
private:
    void set_parent(ll u, ll p);
    void set_depth(ll u, ll p);
    pll get_ancestor(ll u, ll k);
    ll n, m;
    vll depth;
    vvpll ancestor;
};

ll n, k;
vvpll adj;
vll castle;

vbool removed;
vll subtree_size, centroid_tree_parent;

void centroid_decomposition();
void build_centroid_tree(ll u, ll p);
void set_subtree_size(ll u, ll p);
ll find_centroid(ll u, ll p, ll local_n);

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n >> k;

    adj = vvpll(n);
    for(ll i = 0; i < n - 1; i++)
    {
        ll u, v, weight;
        std::cin >> u >> v >> weight;
        u--;
        v--;

        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    castle = vll(k);
    for(ll i = 0; i < k; i++)
    {
        std::cin >> castle[i];
        castle[i]--;
    }

    centroid_decomposition();
}

void centroid_decomposition()
{
    BinaryLift binary_lift(adj);

    subtree_size = vll(n, false);
    centroid_tree_parent = vll(n, false);
    removed = vbool(n, false);

    build_centroid_tree(0, -1);

    vll path_sum(n, 0), parent_path_sum(n, 0), castle_count(n, 0);

    ll result = 0;
    for(ll i = -1; i < k; i++)
    {
        ll orig = (i == -1 ? 0 : castle[i]);
        ll u = orig;
        ll v = -1;

        while(u != -1)
        {
            ll new_castles = castle_count[u] - (v == -1 ? 0 : castle_count[v]);
            ll distance = binary_lift.get_distance(orig, u);
            ll current_path_sum = path_sum[u] - (v == -1 ? 0 : parent_path_sum[v]);

            result += new_castles * distance + current_path_sum;

            v = u;
            u = centroid_tree_parent[u];
        }

        u = orig;
        v = -1;

        while(u != -1)
        {
            ll distance = binary_lift.get_distance(orig, u);
            path_sum[u] += distance;

            ll p = centroid_tree_parent[u];
           if(p != -1)
                parent_path_sum[u] += binary_lift.get_distance(orig, p);

            castle_count[u]++;

            u = centroid_tree_parent[u];
        }

        if(i != -1)
            std::cout << (2 * result) << '\n';
    }
}

void build_centroid_tree(ll u, ll p)
{
    set_subtree_size(u, -1);
    u = find_centroid(u, -1, subtree_size[u]);
    centroid_tree_parent[u] = p;

    removed[u] = true;

    for(pll edge : adj[u])
    {
        ll v = edge.first;

        if(v == p || removed[v])
            continue;

        build_centroid_tree(v, u);
    }
}

void set_subtree_size(ll u, ll p)
{
    subtree_size[u] = 1;

    for(pll edge : adj[u])
    {
        ll v = edge.first;

        if(v == p || removed[v])
            continue;

        set_subtree_size(v, u);
        subtree_size[u] += subtree_size[v];
    }
}

ll find_centroid(ll u, ll p, ll local_n)
{
    for(pll edge : adj[u])
    {
        ll v = edge.first;

        if(v == p || removed[v])
            continue;

        if(subtree_size[v] > local_n / 2)
            return find_centroid(v, u, local_n);
    }

    return u;
}

BinaryLift::BinaryLift(vvpll adj)
{
    n = adj.size();
    m = std::floor(std::log2(n - 1)) + 1;

    ancestor = vvpll(n, vpll(m, {-1, 0}));
    set_parent(0, -1);

    depth = vll(n, 0);
    set_depth(0, -1);

}

void BinaryLift::set_parent(ll u, ll p)
{
    for(ll i = 1; i < m; i++)
    {
        if(ancestor[u][i - 1].first == -1)
            break;

        ancestor[u][i] = {ancestor[ancestor[u][i - 1].first][i - 1].first, ancestor[u][i - 1].second + ancestor[ancestor[u][i - 1].first][i - 1].second};
    }

    for(pll edge : adj[u])
    {
        ll v = edge.first;
        ll weight = edge.second;

        if(v == p)
            continue;

        ancestor[v][0] = {u, weight};
        set_parent(v, u);
    }
}

void BinaryLift::set_depth(ll u, ll p)
{
    for(pll edge : adj[u])
    {
        ll v = edge.first;
        ll weight = edge.second;

        if(v == p)
            continue;

        depth[v] = depth[u] + 1;
        set_depth(v, u);
    }
}

ll BinaryLift::get_distance(ll u, ll v)
{
    ll result = 0;

    assert(u >= 0 && u < n);
    assert(v >= 0 && v < n);

    if(depth[u] < depth[v])
        std::swap(u, v);
    pll u_ancestor = get_ancestor(u, depth[u] - depth[v]);

    u = u_ancestor.first;
    result += u_ancestor.second;

    if(u == v)
        return result;

    for(ll i = m - 1; i >= 0; i--)
    {
        assert(u != -1 && v != -1);
        if(ancestor[u][i].first != ancestor[v][i].first)
        {
            result += ancestor[u][i].second;
            result += ancestor[v][i].second;

            u = ancestor[u][i].first;
            v = ancestor[v][i].first;
        }
    }

    assert(u >= 0 && u < n);
    assert(v >= 0 && v < n);

    result += ancestor[u][0].second;
    result += ancestor[v][0].second;

    u = ancestor[u][0].first;
    v = ancestor[v][0].first;

    return result;
}

pll BinaryLift::get_ancestor(ll u, ll k)
{
    ll distance = 0;
    for(ll i = 0; i < m; i++)
    {
        if(u == -1)
            break;

        if(k & (1 << i))
        {
            assert(u >= 0 && u < n);

            distance += ancestor[u][i].second;
            u = ancestor[u][i].first;
        }
    }

    return {u, distance};
}
