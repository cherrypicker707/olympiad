// Program for Generating Random Test Cases

#include <bits/stdc++.h>

#define RAND(X,Y) std::uniform_int_distribution<ll>(X, Y)(mersenne_twister);

typedef long long ll;
typedef std::vector<ll> vll;

enum Mode { MODE_DEFAULT = 0, MODE_NON_INCREASING_VELOCITY = 1, MODE_EQUAL = 2 };

struct Frac
{
    ll num, den;
};
typedef std::vector<Frac> vFrac;

std::random_device device;
std::mt19937_64 mersenne_twister(device());

bool operator<(const Frac &left, const Frac &right);

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    assert(argc == 4);
    const ll n = std::atoll(argv[1]);
    const ll p = std::atoll(argv[2]);
    const ll mode = std::atoll(argv[3]);

    vll x(n), d(n);
    for(ll i = 0; i < n; i++)
    {
        ll dist = RAND(0, p);
        d[i] = RAND(1, p);
        x[i] = (i > 0 ? x[i - 1] : 1) + dist + d[i];
    }

    Frac v_car = { 0, 1 };
    vFrac v(n);
    for(ll i = 0; i < n; i++)
    {
        v[i].num = RAND(1, p);
        v[i].den = RAND(1, p);
        v_car = std::max(v_car, v[i]);
    }

    if(mode == MODE_NON_INCREASING_VELOCITY)
        std::sort(v.begin(), v.end());
    if(mode == MODE_EQUAL)
        for(ll i = 1; i < n; i++)
            v[i] = v[0];

    v_car.num += RAND(1, p);
    ll d_car = RAND(1, p);

    std::cout << n << ' ' << d_car << ' ' << v_car.num << ' ' << v_car.den << '\n';
    for(ll i = 0; i < n; i++)
        std::cout << x[i] << ' ' << d[i] << ' ' << v[i].num << ' ' << v[i].den << '\n';
}

bool operator<(const Frac &left, const Frac &right)
{
    return (left.num * right.den) < (right.num * left.den);
}
