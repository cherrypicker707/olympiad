// Solution for the Subproblem I
// 28/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;

ll n, maxX;
vll x, a, b;

ll minAB, maxAB;
vvll available, memo;

void dp();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n >> maxX;

    x.resize(n);
    a.resize(n);
    b.resize(n);

    for(ll i = 0; i < n; i++)
        std::cin >> x[i] >> a[i] >> b[i];

    dp();
}

void dp()
{
    ll bottom = -maxX + 1;
    ll top = maxX - 1;

    available = vvll(maxX, vll(top - bottom + 1, true));
    for(ll i = 0; i < n; i++)
    {
        for(ll y = bottom; y <= a[i] && y <= top; y++)
            available[x[i]][y - bottom] = false;

        for(ll y = top; y >= b[i] && y >= bottom; y--)
            available[x[i]][y - bottom] = false;
    }

    memo = vvll(maxX, vll(top - bottom + 1, LLONG_MAX - 1));
    memo[0][0 - bottom] = 0;

    for(ll x = 1; x < maxX; x++)
    {
        for(ll y = bottom; y <= top; y++)
        {
            if(y + 1 <= top && available[x][y - bottom])
                memo[x][y - bottom] = std::min(memo[x][y - bottom], memo[x - 1][y + 1 - bottom]);

            if(y - 1 >= bottom && available[x][y - bottom])
                memo[x][y - bottom] = std::min(memo[x][y - bottom], memo[x - 1][y - 1 - bottom] + 1);
        }
    }

    ll answer = LLONG_MAX;
    for(ll y = bottom; y <= top; y++)
        answer = std::min(memo[maxX - 1][y - bottom], answer);

    if(answer == LLONG_MAX - 1)
    {
        std::cout << "NIE\n";
        return;
    }

    std::cout << answer << '\n';
}
