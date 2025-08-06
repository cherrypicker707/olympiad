// Used for testing.

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;

ll n, s, k;
vll a;

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n >> s;
    k = n * (n - 1) / 2;

    std::string firstLine;
    std::cin >> firstLine;

    if(firstLine == "NIE")
    {
        if(s >= -k && s <= k && (s - k) % 2 == 0)
            return 1;
        return 0;
    }

    ll sum = 0, a = 0, b;
    for(ll i = 1; i < n; i++)
    {
        std::cin >> b;
        sum += b;

        if(std::abs(b - a) != 1)
            return 1;

        a = b;
    }

    if(sum != s)
        return 1;
    return 0;
}
