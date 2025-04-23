// Solution for All Subproblems
// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<bool> vbool;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

ll n, m, k;
vvll graph1, graph2, graph3;
vvll tree1, tree2;
vvll dp;

void s3();
void maketree(vvll &tree, vvll &graph, ll u, ll v);
ll getval(ll u, ll v);

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n >> m >> k;

    graph1.resize(n);
    graph2.resize(m);

    for(ll i = 0; i < n; i++)
        graph1[i].reserve(3);

    for(ll i = 0; i < m; i++)
        graph2[i].reserve(3);

    for(ll i = 0; i < n - 1; i++)
    {
        ll u, v; std::cin >> u >> v; u--; v--;

        graph1[u].push_back(v);
        graph1[v].push_back(u);
    }

    for(ll i = 0; i < m - 1; i++)
    {
        ll u, v;
        std::cin >> u >> v;
        u--;
        v--;

        graph2[u].push_back(v);
        graph2[v].push_back(u);
    }

    s3();

    return 0;
}

void maketree(vvll &tree, vvll &graph, ll u, ll v)
{
    for(ll w : graph[v])
    {
        if(w == u)
            continue;

        tree[v].push_back(w);
        maketree(tree, graph, v, w);
    }
}

ll getval(ll u, ll v)
{
    assert(u < dp.size());
    assert(v < dp[0].size());

    if(dp[u][v] != -1)
        return dp[u][v];

    if(graph3[u].size() > tree2[v].size())
    {
        dp[u][v] = 0;
        return dp[u][v];
    }

    if(graph3[u].size() == 0)
    {
        dp[u][v] = 1;
        return dp[u][v];
    }

    if(graph3[u].size() == 1 && tree2[v].size() == 1)
    {
        dp[u][v] = getval(graph3[u][0], tree2[v][0]);
        return dp[u][v];
    }

    if(graph3[u].size() == 1 && tree2[v].size() == 2)
    {
        dp[u][v] = (getval(graph3[u][0], tree2[v][0]) + getval(graph3[u][0], tree2[v][1])) % k;
        return dp[u][v];
    }

    ll x = (getval(graph3[u][0], tree2[v][0]) * getval(graph3[u][1], tree2[v][1])) % k;
    ll y = (getval(graph3[u][0], tree2[v][1]) * getval(graph3[u][1], tree2[v][0])) % k;
    dp[u][v] = (x + y) % k;
    return dp[u][v];
}

void s3()
{
    ll answer = 0;
    vpll subtrees;
    subtrees.reserve(3 * n);

    for(ll u = 0; u < n; u++)
    {
        if(graph1[u].size() > 2)
            continue;

        subtrees.push_back({-1, u});
    }

    ll fullsubtreecount = subtrees.size();

    for(ll u = 0; u < n; u++)
        for(ll v : graph1[u])
            subtrees.push_back({u, v});

    std::sort(subtrees.begin(), subtrees.end());

    graph3.resize(subtrees.size());

    for(ll i = 0; i < subtrees.size(); i++)
        graph3[i].reserve(2);

    for(auto subtree = subtrees.begin(); subtree != subtrees.end(); subtree++)
    {
        ll u = subtree->first;
        ll v = subtree->second;
        for(ll w : graph1[v])
        {
            if(w == u)
                continue;

            pll req = {v, w};
            ll reqindex = std::distance(subtrees.begin(), std::lower_bound(subtrees.begin(), subtrees.end(), req));

            graph3[std::distance(subtrees.begin(), subtree)].push_back(reqindex);
        }
    }

    ll root2 = 0;
    while(graph2[root2].size() > 2)
        root2++;

    tree2.resize(m);
    for(ll i = 0; i < m; i++)
        tree2[i].reserve(2);
    maketree(tree2, graph2, -1, root2);

    dp.resize(subtrees.size(), vll(m, -1));

    for(ll i = 0; i < fullsubtreecount; i++)
        for(ll j = 0; j < m; j++)
            answer = (answer + getval(i, j)) % k;

    std::cout << answer << '\n';
}
