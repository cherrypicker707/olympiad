// Solution for All Subproblems
// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<bool> vbool;

ll n;
vll a, b;

void s3();

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

    s3();

    return 0;
}

void s3()
{
    vbool owner(n, false);
    vll order(n);
    for(ll i = 0; i < n; i++)
        order[i] = i;
    std::sort(order.begin(), order.end(), [&](ll left, ll right){return a[left] > a[right];});

    ll asuma = 0, bsuma = 0;
    for(ll i = 0; i < n; i++)
    {
        if(asuma < bsuma)
        {
            asuma += a[order[i]];
            continue;
        }

        bsuma += a[order[i]];
        owner[order[i]] = true;
    }

    ll asumb = 0, bsumb = 0;
    for(ll i = 0; i < n; i++)
    {
        if(owner[i])
        {
            bsumb += b[i];
            continue;
        }

        asumb += b[i];
    }

    bool change = (asumb > bsumb);

    for(ll i = 0; i < n; i++)
        std::cout << (owner[i] ^ change) << ' ';
    std::cout << '\n';
}
