// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<bool> vbool;
typedef std::vector<vbool> vvbool;

ll n, m;
vvbool adj;

void greedy();

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

    greedy();
    return 0;
}

void greedy()
{
    ll total = (n - 2) * (n - 1) * n / 6;

    ll mixed = 0;
    for(ll u = 0; u < n; u++)
    {
        ll red = 0;
        for(ll v = 0; v < n; v++)
            red += adj[u][v];

        mixed += red * (n - 1 - red);
    }
    mixed /= 2;

    ll result = total - mixed;
    std::cout << result << '\n';
}
