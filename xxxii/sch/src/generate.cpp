// Random Test Data Generator

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;

std::random_device device;
std::mt19937_64 mersenne_twister(device());

void printRandomArray(ll n, ll s);

int main(int argc, char **argv)
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	assert(argc == 3);
	ll n = std::atoll(argv[1]);
	ll s = std::atoll(argv[2]);

	std::cout << n << '\n';

	for(ll i = 0; i < 2; i++)
		printRandomArray(n, s);
}

void printRandomArray(ll n, ll s)
{
	for(ll i = 0; i < n - 1; i++)
	{
		ll a = std::uniform_int_distribution<ll>(0, 2 * s / (n - 1))(mersenne_twister);

		if(std::uniform_int_distribution<ll>(0, 3)(mersenne_twister) == 0)
			a = 0;

		a = std::min(a, s);
		s -= a;

		std::cout << a << ' ';
	}

	std::cout << s << '\n';
}
