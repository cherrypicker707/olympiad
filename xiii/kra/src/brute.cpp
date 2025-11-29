// 36/100

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;

void solve();

ll n, m;
vll a, b;

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n >> m;

    a = vll(n);
    for(ll i = 0; i < n; i++)
        std::cin >> a[i];

    b = vll(m);
    for(ll i = 0; i < m; i++)
        std::cin >> b[i];

    solve();
    return 0;
}

void solve()
{
    ll result;
    for(ll i = 0; i < m; i++)
    {
        result = -1;
        for(ll j = 0; j < n; j++)
        {
            if(a[j] < b[i])
                break;

            result = j;
        }

        if(result == -1)
            break;

        a[result] = 0;
    }

    std::cout << (result + 1) << '\n';
}
