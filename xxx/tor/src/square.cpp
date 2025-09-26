// Solution for the Subproblem I
// 4/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef long double ld;

struct Vertex
{
    ld x, y;
};
typedef std::vector<Vertex> vVertex;

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout << std::setprecision(10) << std::fixed;

    ll n, k;
    vVertex vertex;

    std::cin >> n >> k;

    vertex = vVertex(n);
    ld x = 0, y = 0, d;
    for(ll i = 0; i < n; i++)
    {
        std::cin >> vertex[i].x >> vertex[i].y;
        x += vertex[i].x;
        y += vertex[i].y;
    }

    x /= n;
    y /= n;

    d = sqrtl(x * x + y * y);
    x /= d;
    y /= d;

    std::cout << x << ' ' << y << '\n';
}

