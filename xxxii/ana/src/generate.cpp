// Random Test Data Generator

#include <bits/stdc++.h>

typedef long long ll;

std::random_device device;
std::mt19937_64 mersenne_twister(device());

int main(int argc, char **argv)
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	assert(argc == 3);
	ll n = std::atoll(argv[1]);
	assert(n >= 1 && n <= 200000);
	ll m = std::atoll(argv[2]);
	assert(m >= 0 && m <= 26);

	std::cout << n << '\n';
	for(ll i = 0; i < n; i++)
		std::cout << (char)('a' + std::uniform_int_distribution<ll>(0, m - 1)(mersenne_twister));
	std::cout << '\n';
}
