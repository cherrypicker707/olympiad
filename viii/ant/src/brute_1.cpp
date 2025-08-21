// 41/100 points

#include <bits/stdc++.h>

typedef long long ll;

void brute1();
ll getDividerCount(ll x);

ll n;

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n;

    brute1();
    return 0;
}

void brute1()
{
    ll maxDividerCount = 0;
    ll maxI = 0;
    for(ll i = 1; i <= n; i++)
    {
        ll dividerCount = getDividerCount(i);

        if(dividerCount > maxDividerCount)
        {
            maxDividerCount = dividerCount;
            maxI = i;
        }
    }

    std::cout << maxI << '\n';
}

ll getDividerCount(ll x)
{
    ll dividerCount = 0;
    float squareRoot = sqrt(x);

    for(ll y = 1; y <= squareRoot; y++)
    {
        if(x % y == 0)
            dividerCount += 2;
    }

    float roundSquareRoot = std::round(squareRoot);
    if(roundSquareRoot == squareRoot && x % (ll)squareRoot == 0)
        dividerCount--;

    return dividerCount;
}
