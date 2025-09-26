// Solution for the Subproblem I
// 20/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef long double ld;
typedef std::vector<ld> vld;

ll n;
ld d_car, v_car;
vld x, d, v;

void equal();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    ll num, den;
    std::cin >> n >> d_car >> num >> den;
    v_car = (ld)num / (ld)den;

    x = vld(n);
    d = vld(n);
    v = vld(n);
    for(ll i = 0; i < n; i++)
    {
        std::cin >> x[i] >> d[i] >> num >> den;
        v[i] = (ld)num / (ld)den;
    }

    equal();
}

void equal()
{
    ll result = 1;
    for(ll i = 1; i < n; i++)
    {
        ld distance = x[i] - d[i] - x[i - 1];
        result += (distance >= d_car);
    }
    std::cout << result << '\n';
}
