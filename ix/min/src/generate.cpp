// Random Test Data Generator

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<char> vchar;

std::random_device device;
std::mt19937_64 mersenne_twister(device());

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    assert(argc == 2);
    const ll n = std::atoll(argv[1]);

    std::cout << n << '\n';
    std::cout << '-' << '\n';

    for(ll i = 0; i < n - 2; i++)
        std::cout << (std::uniform_int_distribution<ll>(0, 1)(mersenne_twister) ? '-' : '+') << '\n';

    return 0;
}
