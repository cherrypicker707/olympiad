// Random Test Data Generator

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::set<ll> sll;

std::random_device device;
std::mt19937_64 mersenne_twister(device());

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    assert(argc == 5);
    const ll n = std::atoll(argv[1]);
    const ll maxX = std::atoll(argv[2]);
    const ll minA = std::atoll(argv[3]);
    const ll maxA = std::atoll(argv[4]);
    assert(n < maxX);

    std::cout << n << ' ' << maxX << '\n';

    vll all;
    all.reserve(maxX - 1);
    for(ll i = 1; i < maxX; i++)
        all.push_back(i);

    vll x;
    x.reserve(n);
    std::sample(all.begin(), all.end(), std::back_inserter(x), n, mersenne_twister);

    ll previousX = 0;
    ll previousA = std::uniform_int_distribution<ll>(minA, maxA)(mersenne_twister);
    ll previousB = std::uniform_int_distribution<ll>(minA, maxA)(mersenne_twister);
    for(ll currentX : x)
    {
        ll a = previousA + std::uniform_int_distribution<ll>(previousX - currentX, currentX - previousX)(mersenne_twister);
        ll b = previousB + std::uniform_int_distribution<ll>(previousX - currentX, currentX - previousX)(mersenne_twister);

        a = std::max(a, minA);
        a = std::min(a, maxA);
        b = std::max(b, minA);
        b = std::min(b, maxA);

        if(a > b)
            std::swap(a, b);

        std::cout << currentX << ' ' << a << ' ' << b << '\n';

        previousX = currentX;
        previousA = a;
        previousB = b;
    }
}
