// Solution for All Subproblems
// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;

ll a, b;

void s1();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> a >> b;

    s1();

    return 0;
}

void s1()
{
    ll x, y, result;

    x = (b - a + 1) / 2;
    y = (b - a + 1) - x;

    result = (x / 2) * 2 + (y / 2) * 2;

    std::cout << result << '\n';
}
