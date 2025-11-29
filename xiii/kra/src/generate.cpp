// Program for generating random test data.

#include <bits/stdc++.h>
#define RANDOM(X, Y) std::uniform_int_distribution<ll>(X, Y)(mersenne_twister)

typedef long long ll;

std::random_device device;
std::mt19937_64 mersenne_twister(device());

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    ll n = std::atoll(argv[1]);
    ll m = std::atoll(argv[2]);
    ll min_a = std::atoll(argv[3]);
    ll max_a = std::atoll(argv[4]);
    ll min_b = std::atoll(argv[5]);
    ll max_b = std::atoll(argv[6]);

    std::cout << n << ' ' << m << '\n';

    for(ll i = 0; i < n; i++)
        std::cout << RANDOM(min_a, max_a) << ' ';
    std::cout << '\n';

    for(ll i = 0; i < m; i++)
        std::cout << RANDOM(min_b, max_b) << ' ';
    std::cout << '\n';

    return 0;
}
