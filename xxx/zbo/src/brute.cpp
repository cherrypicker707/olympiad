// Solution for the Subproblem I
// 15/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;
typedef std::vector<vpll> vvpll;
typedef std::vector<bool> vbool;

ll n, k;
vvpll adj;
vll castle;

void brute();
pll dfs_find(ll u, ll p, const vbool &build);

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

    brute();
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
