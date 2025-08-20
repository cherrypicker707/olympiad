// 83/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<bool> vbool;
typedef std::vector<vbool> vvbool;

ll n, m;
vvbool adj;

void brute();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n >> m;

    adj = vvbool(n, vbool(n, false));

    for(ll i = 0; i < m; i++)
    {
        ll u, v;
        std::cin >> u >> v;
        u--;
        v--;

        adj[u][v] = true;
        adj[v][u] = true;
    }

    brute();
    return 0;
}

void brute()
{
    ll result = 0;

    for(ll u = 0; u < n; u++)
        for(ll v = u + 1; v < n; v++)
            for(ll w = v + 1; w < n; w++)
                if(adj[u][v] == adj[v][w] && adj[v][w] == adj[w][u])
                    result++;

    std::cout << result << '\n';
}
