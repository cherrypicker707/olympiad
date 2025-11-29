// 100/100

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
    for(ll i = 1; i < n; i++)
        a[i] = std::min(a[i], a[i - 1]);

    ll last = n;
    for(ll i = 0; i < m; i++)
    {
        ll left = 0, right = last;

        if(a[0] < b[i] || left == right)
        {
            last = -1;
            break;
        }

        while(right - left > 1)
        {
            ll mid = (left + right) / 2;

            if(a[mid] >= b[i])
            {
                left = mid;
                continue;
            }

            right = mid;
        }

        last = left;
    }

    std::cout << (last + 1) << '\n';
}
