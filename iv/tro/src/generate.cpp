// Random Test Data Generator

#include <bits/stdc++.h>

typedef long long ll;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

std::random_device device;
std::mt19937_64 mersenne_twister(device());

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    assert(argc == 3);
    const ll n = std::atoll(argv[1]);
    const ll k = std::atoll(argv[2]);

    vpll edge;
    for(ll u = 0; u < n; u++)
        for(ll v = u + 1; v < n; v++)
            if(std::uniform_int_distribution<ll>(1, k)(mersenne_twister) == k)
                edge.push_back({u, v});

    ll m = edge.size();

    std::shuffle(edge.begin(), edge.end(), mersenne_twister);
    for(ll i = 0; i < m; i++)
        if(std::uniform_int_distribution<ll>(0, 1)(mersenne_twister))
            std::swap(edge[i].first, edge[i].second);

    std::cout << n << '\n' << m << '\n';
    for(ll i = 0; i < m; i++)
        std::cout << (edge[i].first + 1) << ' ' << (edge[i].second + 1) << '\n';

    return 0;
}
