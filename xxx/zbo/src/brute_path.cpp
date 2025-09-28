// Solution for the Subproblems I and II
// 50/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;
typedef std::vector<vpll> vvpll;
typedef std::vector<bool> vbool;

class SegmentTree
{
public:
    SegmentTree(ll n);
    void update(ll i, ll value);
    ll query(ll left, ll right);
private:
    ll n;
    vll tree;
};

ll n, k;
vvpll adj;
vll castle;

void brute();
pll dfs_find(ll u, ll p, const vbool &build);

void path();
void dfs_set_weight(ll u, ll p, ll i, vll &weight);

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

    if(n * k <= 100000)
    {
        brute();
        return 0;
    }

    path();
}

void brute()
{
    vbool build(n, false);
    build[0] = true;

    ll result = 0;
    for(ll i = 0; i < k; i++)
    {
        pll a = dfs_find(castle[i], -1, build);
        build[castle[i]] = true;

        result += 2 * a.second;
        std::cout << result << '\n';
    }
}

pll dfs_find(ll u, ll p, const vbool &build)
{
    pll result = {0, 0};

    for(pll edge : adj[u])
    {
        ll v = edge.first;
        ll weight = edge.second;

        if(v == p)
            continue;

        pll a = dfs_find(v, u, build);
        result.first += a.first;
        result.second += a.second;
        result.second += a.first * weight;
    }

    result.first += build[u];

    return result;
}

void path()
{
    vll weight(n, 0);
    dfs_set_weight(0, -1, 0, weight);

    vll weight_prefix_sum(n, 0);
    for(ll i = 1; i < n; i++)
        weight_prefix_sum[i] = weight_prefix_sum[i - 1] + weight[i];

    SegmentTree count_left(n), count_right(n), sum_left(n), sum_right(n);

    count_left.update(0, 1);
    count_right.update(0, 1);

    ll result = 0;
    for(ll i = 0; i < k; i++)
    {
        ll u = castle[i];

        ll current_count_left = count_left.query(0, u);
        ll current_weight_prefix_sum_left = weight_prefix_sum[u];
        ll current_sum_left = sum_left.query(0, u);
        result += current_count_left * current_weight_prefix_sum_left - current_sum_left;

        ll current_count_right = count_right.query(u, n);
        ll current_weight_prefix_sum_right = weight_prefix_sum[n - 1] - weight_prefix_sum[u];
        ll current_sum_right = sum_right.query(u, n);
        result += current_count_right * current_weight_prefix_sum_right - current_sum_right;

        count_left.update(u, 1);
        count_right.update(u, 1);
        sum_left.update(u, weight_prefix_sum[u]);
        sum_right.update(u, weight_prefix_sum[n - 1] - weight_prefix_sum[u]);

        std::cout << (2 * result) << '\n';
    }
}

void dfs_set_weight(ll u, ll p, ll i, vll &weight)
{
    for(pll edge : adj[u])
    {
        ll v = edge.first;
        ll current_weight = edge.second;

        if(v == p)
            continue;

        weight[i + 1] = current_weight;
        dfs_set_weight(v, u, i + 1, weight);
    }
}

SegmentTree::SegmentTree(ll n)
{
    this->n = n;
    this->tree = vll(2 * n, 0);
}

void SegmentTree::update(ll i, ll value)
{
    i += n;

    while(i > 0)
    {
        tree[i] += value;
        i /= 2;
    }
}

ll SegmentTree::query(ll left, ll right)
{
    left += n;
    right += n;

    ll result = 0;

    while(left < right)
    {
        if(left % 2)
            result += tree[left++];

        if(right % 2)
            result += tree[--right];

        left /= 2;
        right /= 2;
    }

    return result;
}
