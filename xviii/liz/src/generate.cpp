// Random Test Data Generator

#include <bits/stdc++.h>

typedef long long ll;

std::random_device device;
std::mt19937_64 mersenne_twister(device());

int main(int argc, char **argv)
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	ll n = std::atoll(argv[1]);
	ll m = std::atoll(argv[2]);
	ll p = std::atoll(argv[3]);

	std::cout << n << ' ' << m << '\n';

	for(ll i = 0; i < n; i++)
		std::cout << (std::uniform_int_distribution<ll>(0, 1)(mersenne_twister) ? 'W' : 'T');
	std::cout << '\n';

	for(ll i = 0; i < m; i++)
		std::cout << std::uniform_int_distribution<ll>(1, p)(mersenne_twister) << '\n';

	return 0;
}
