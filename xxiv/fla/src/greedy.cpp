// Solution for All Subproblems
// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;

ll n, maxX;
vll x, a, b;

void greedy();

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

    greedy();
}

void greedy()
{
    ll space = 0;
    ll previousX = 0;
    ll jumpCount = 0;
    for(ll i = 0; i < n; i++)
    {
        ll width = x[i] - previousX;

        ll minJumpCount = ceil((x[i] + a[i] + 1) / 2.0);
        ll maxJumpCount = floor((x[i] + b[i] - 1) / 2.0);

        minJumpCount = std::max(minJumpCount, 0LL);

        space = std::min(space + width, maxJumpCount - jumpCount);

        ll currentJumps = std::max(minJumpCount - jumpCount, 0LL);

        space -= currentJumps;
        previousX = x[i];
        jumpCount += currentJumps;

        if(space < 0)
        {
            std::cout << "NIE\n";
            return;
        }
    }

    std::cout << jumpCount << '\n';
}
