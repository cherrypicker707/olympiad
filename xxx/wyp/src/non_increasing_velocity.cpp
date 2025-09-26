// Solution for the Subproblems I and II
// 30/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef long double ld;
typedef std::vector<ld> vld;

ll n;
ld d_car, v_car;
vld x, d, v;

void non_increasing_velocity();
bool are_values_equal(ld left, ld right);

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

    non_increasing_velocity();
}

void non_increasing_velocity()
{
    ll result = 1;
    for(ll i = 1; i < n; i++)
    {
        ld time = (x[i] - d[i]) / (v_car - v[i]);
        ld distance = (x[i] + v[i] * time) - d[i] - (x[i - 1] + v[i - 1] * time);
        result += (distance > d_car || are_values_equal(distance, d_car));
    }
    std::cout << result << '\n';
}

bool are_values_equal(ld left, ld right)
{
    const ld epsilon = 0.0000000001;
    if(std::abs(left - right) < epsilon)
        return true;
    return false;
}
