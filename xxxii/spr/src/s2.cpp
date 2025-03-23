// Solution for the Subproblem III
// 40/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<bool> vbool;

ll n;
vll a, b;

void s2();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n;

    a.resize(n);
    b.resize(n);

    for(ll i = 0; i < n; i++)
        std::cin >> a[i];

    for(ll i = 0; i < n; i++)
        std::cin >> b[i];

    s2();

    return 0;
}

void s2()
{
    vbool owner(n, false);
    vll order(n);
    for(ll i = 0; i < n; i++)
        order[i] = i;
    std::sort(order.begin(), order.end(), [&](ll left, ll right){return a[left] > a[right];});

    ll asum = 0, bsum = 0;
    for(ll i = 0; i < n; i++)
    {
        if(asum < bsum)
        {
            asum += a[order[i]];
            continue;
        }

        bsum += b[order[i]];
        owner[order[i]] = true;
    }

    for(ll i = 0; i < n; i++)
        std::cout << owner[i]<< ' ';
    std::cout << '\n';
}
