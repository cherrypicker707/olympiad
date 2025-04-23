// Solution for the Subproblems I, II, III and IV
// 51/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<bool> vbool;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;

ll n, m, k;
vvll graph1, graph2;
vvll tree1, tree2;
vvll dp;

void s2();
void maketree(vvll &tree, vvll &graph, ll u, ll v);
ll getval(ll u, ll v);

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n >> m >> k;

    graph1.resize(n);
    graph2.resize(m);

    for(ll i = 0; i < n - 1; i++)
    {
        ll u, v;
        std::cin >> u >> v;
        u--;
        v--;

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

    s2();

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

    if(tree1[u].size() > tree2[v].size())
    {
        dp[u][v] = 0;
        return dp[u][v];
    }

    if(tree1[u].size() == 0)
    {
        dp[u][v] = 1;
        return dp[u][v];
    }

    if(tree1[u].size() == 1 && tree2[v].size() == 1)
    {
        dp[u][v] = getval(tree1[u][0], tree2[v][0]);
        return dp[u][v];
    }

    if(tree1[u].size() == 1 && tree2[v].size() == 2)
    {
        dp[u][v] = (getval(tree1[u][0], tree2[v][0]) + getval(tree1[u][0], tree2[v][1])) % k;
        return dp[u][v];
    }

    ll x = (getval(tree1[u][0], tree2[v][0]) * getval(tree1[u][1], tree2[v][1])) % k;
    ll y = (getval(tree1[u][0], tree2[v][1]) * getval(tree1[u][1], tree2[v][0])) % k;
    dp[u][v] = (x + y) % k;
    return dp[u][v];
}

void s2()
{
    ll answer = 0;

    ll root2 = 0;
    while(graph2[root2].size() > 2)
        root2++;

    tree2.resize(m);
    maketree(tree2, graph2, -1, root2);

    for(ll root1 = 0; root1 < n; root1++)
    {
        if(graph1[root1].size() > 2)
            continue;

        tree1.clear();
        tree1.resize(n);
        maketree(tree1, graph1, -1, root1);

        dp.clear();
        dp.resize(n, vll(m, -1));

        for(ll i = 0; i < m; i++)
            answer = (answer + getval(root1, i)) % k;
    }

    std::cout << answer << '\n';
}
