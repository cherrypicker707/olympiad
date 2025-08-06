// Used for generating random test data.

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;

std::random_device device;
std::mt19937_64 mersenne_twister(device());

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    assert(argc == 2);
    ll maxN = std::atoll(argv[1]);

    ll n = std::uniform_int_distribution<ll>(1, maxN)(mersenne_twister);
    ll s = std::uniform_int_distribution<ll>(-(n * n), n * n)(mersenne_twister);

    std::cout << n << ' ' << s << '\n';
    return 0;
}
