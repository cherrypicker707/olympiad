#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;

ll n;
vll a, b, c;

void greedy();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n;

    a = vll(n);
    b = vll(n);
    c = vll(n);

    for(ll i = 0; i < n - 2; i++)
        std::cin >> a[i] >> b[i] >> c[i];

    greedy();
    return 0;
}

void greedy()
{
    ll x = a[0];
    ll y = b[0];
    ll z = c[0];

    if
    (
        y == (x + 1) % n && z == (x + 2) % n ||
        z == (x + 1) % n && y == (x + 2) % n ||
        x == (y + 1) % n && z == (y + 2) % n ||
        z == (y + 1) % n && x == (y + 2) % n ||
        x == (z + 1) % n && y == (z + 2) % n ||
        y == (z + 1) % n && x == (z + 2) % n
    )
    {
        std::cout << "TAK\n";
        return;
    }

    if(n % 2 == 0)
    {
        std::cout << "TAK\n";
        return;
    }

    std::cout << "NIE\n";
}
