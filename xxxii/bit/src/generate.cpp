#include <bits/stdc++.h>

typedef std::vector<bool> vbool;
typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

std::random_device device;
std::mt19937_64 mersenne_twister(device());

void printRandomTree(ll n);

int main(int argc, char **argv)
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	assert(argc == 4);
	const ll n = std::atoll(argv[1]);
	const ll m = std::atoll(argv[2]);
	const ll k = std::atoll(argv[3]);

	std::cout << n << ' ' << m << ' ' << k << '\n';
	printRandomTree(n);
	printRandomTree(m);

	return 0;
}

void printRandomTree(ll n)
{
	vll code(n - 2);
	vll degree(n, 1);

	for(ll i = 0; i < n - 2; i++)
	{
		ll u;
		do
			u = std::uniform_int_distribution<ll>(0, n - 1)(mersenne_twister);
		while(degree[u] > 2);

		code[i] = u;
		degree[u]++;
	}

	vpll edge;
	edge.reserve(n - 1);

	ll pointer = 0, leaf = 0;
	for(ll i = 0; i < n - 2; i++)
	{
		while(leaf > pointer || degree[leaf] > 1)
			leaf = ++pointer;

		edge.push_back({leaf, code[i]});
		degree[leaf]--;
		degree[code[i]]--;
		leaf = code[i];
	}

	for(ll u = 0; u < n; u++)
	{
		if(degree[u] == 1)
		{
			edge.push_back({u, n - 1});
			degree[u]--;
			degree[n - 1]--;
		}
	}

	for(ll i = 0; i < n - 1; i++)
		if(std::uniform_int_distribution<ll>(0, 1)(mersenne_twister))
			std::swap(edge[i].first, edge[i].second);

	std::shuffle(edge.begin(), edge.end(), mersenne_twister);

	for(ll i = 0; i < n - 1; i++)
		std::cout << (edge[i].first + 1) << ' ' << (edge[i].second + 1) << '\n';
}
