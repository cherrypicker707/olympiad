// Random Test Data Generator

#include <bits/stdc++.h>

typedef long long ll;

std::random_device device;
std::mt19937_64 mersenne_twister(device());

ll n, m, p, q;

void printRandomString();
void printRandomQuery();

int main(int argc, char **argv)
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	assert(argc == 4);
	n = std::atoll(argv[1]);
	m = std::atoll(argv[3]);
	p = (1 << n);
	q = std::atoll(argv[2]);

	std::cout << n << ' ' << q << '\n';

	for(ll i = 0; i < 2; i++)
		printRandomString();

	for(ll i = 0; i < q; i++)
		printRandomQuery();

	return 0;
}

void printRandomString()
{
	for(ll i = 0; i < p; i++)
	{
		char c = 'a' + std::uniform_int_distribution<ll>(0, m - 1)(mersenne_twister);
		std::cout << c;
	}
	std::cout << '\n';
}

void printRandomQuery()
{
	ll type = std::uniform_int_distribution<ll>(1, 2)(mersenne_twister);
	ll i = std::uniform_int_distribution<ll>(0, p - 1)(mersenne_twister);
	char c = 'a' + std::uniform_int_distribution<ll>(0, m - 1)(mersenne_twister);
	std::cout << type << ' ' << (i + 1) << ' ' << c << '\n';
}
