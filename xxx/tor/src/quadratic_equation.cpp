// Solution for All Subproblems
// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef long double ld;

struct Vertex
{
    ld x, y, t, sign, area, a, b, c;
};
typedef std::vector<Vertex> vVertex;

ld quadratic_equation(ld a, ld b, ld c, ld left, ld right);

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout << std::setprecision(20) << std::fixed;

    ll n, k;
    vVertex vertex;
    ld area, fragment_area;
    ld a = 0, b = 0, c = 0;

    std::cin >> n >> k;

    vertex = vVertex(n);
    for(ll i = 0; i < n; i++)
    {
        std::cin >> vertex[i].x >> vertex[i].y;
        vertex[i].t = vertex[i].y / vertex[i].x;
    }

    for(ll i = 0; i < n; i++)
    {
        vertex[i].sign = (i % 2 ? 1 : -1);
        area += vertex[i].sign * vertex[i].x * vertex[i].y;
    }

    if(area < 0)
    {
        area = -area;
        for(ll i = 0; i < n; i++)
            vertex[i].sign *= -1;
    }

    fragment_area = area / (k + 1);

    std::sort(vertex.begin(), vertex.end(), [](const Vertex &left, const Vertex &right)
    {
        return left.t < right.t;
    });

    for(ll i = 0; i < n; i++)
    {
        a -= vertex[i].sign * 0.5 * vertex[i].x * vertex[i].x;
        b += vertex[i].sign * vertex[i].x * vertex[i].y;
        c -= vertex[i].sign * 0.5 * vertex[i].y * vertex[i].y;

        vertex[i].a = a;
        vertex[i].b = b;
        vertex[i].c = c;
        vertex[i].area = a * vertex[i].t + b + c / vertex[i].t;
    }

    ll i = 0, j = 0;
    while(i < n - 1 && j < k)
    {
        ld p = (j + 1) * fragment_area;

        if(vertex[i + 1].area <= p)
        {
            i++;
            continue;
        }

        ld t = quadratic_equation(vertex[i].a, vertex[i].b - p, vertex[i].c, vertex[i].t, vertex[i + 1].t);
        j++;

        ld x = 1 / sqrtl(1 + t * t);
        ld y = t * x;
        std::cout << x << ' ' << y << '\n';
    }
}

ld quadratic_equation(ld a, ld b, ld c, ld left, ld right)
{
    if(a == 0)
        return -c / b;

    ld delta = b * b - 4 * a * c;
    ld sqrt_delta = sqrtl(delta);
    ld x_1 = (-b - sqrt_delta) / (2 * a);
    ld x_2 = (-b + sqrt_delta) / (2 * a);

    ld x = x_1;
    ld middle = (left + right) / 2;
    if(fabsl(x_1 - middle) > fabsl(x_2 - middle))
        x = x_2;

    return x;
}
