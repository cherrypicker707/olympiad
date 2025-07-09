#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;

std::random_device device;
ll seed = device();
std::mt19937_64 mersenne_twister(seed);

ll n, m;
vll permutation;

ll getInversionCount();

int main(int argc, char **argv)
{
	assert(argc == 3);
	n = std::atoll(argv[1]);
	m = std::atoll(argv[2]);

	permutation = vll(n);
	for(ll i = 0; i < n; i++)
		permutation[i] = i;
	std::shuffle(permutation.begin(), permutation.end(), mersenne_twister);
	// permutation = {1, 0, 2, 3, 4, 5};

	// std::cerr << "Actual array: ";
	// for(ll i = 0; i < n; i++)
	// 	std::cerr << (permutation[i] + 1) << ' ';
	// std::cerr << '\n';

	std::cout << n << '\n';

	for(ll i = 0; i < m; i++)
	{
		ll x, y;
		std::cin >> x >> y;
		// std::cerr << x << ' ' << y << std::endl;
		x--;
		y--;

		if(x < 0 || x >= n || y < 0 || y >= n)
		{
			std::cerr << "Invalid swap! " << x << ' ' << y << std::endl;
			return 2;
		}

		std::swap(permutation[x], permutation[y]);

		ll inversionCount = getInversionCount();
		std::cout << inversionCount << '\n';

		if(inversionCount == 0)
		{
			std::cerr << "Operation count: " << (i + 1) << " (" << seed << ")" << std::endl;
			return 0;
		}
	}

	return 1;
	std::cerr << "Operation count exceeds m!" << std::endl;
}

ll getInversionCount()
{
	ll inversionCount = 0;

	for(ll i = 0; i < n; i++)
		for(ll j = i + 1; j < n; j++)
			if(permutation[i] > permutation[j])
				inversionCount++;

	return inversionCount;
}
