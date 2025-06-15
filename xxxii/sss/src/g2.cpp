#include <bits/stdc++.h>

typedef long long ll;
typedef std::set<ll> sll;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

std::random_device dev;
std::mt19937_64 rd(dev());

ll t, n, k;

ll getRandomNumber(ll min, ll max);
ll getRandomElement(sll &set);
void printRandomTree(ll n, ll root);

int main(int argc, char **argv)
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	assert(argc == 4);
	t = atoi(argv[1]);
	n = atoi(argv[2]);
	k = atoi(argv[3]);

	std::cout << t << '\n';

	for(ll i = 0; i < t; i++)
	{
		ll root;
		std::cin >> root;

		assert(1 <= root && root <= n);

		std::cout << n << ' ' << k << '\n';
		printRandomTree(n, root);
	}

	return 0;
}

ll getRandomNumber(ll min, ll max)
{
	return std::uniform_int_distribution<ll>(min, max)(rd);
}

ll getRandomElement(sll &set)
{
	ll count = set.size();
	ll index = getRandomNumber(0, count - 1);
	auto it = set.begin();
	std::advance(it, index);
	return *it;
}

void printRandomTree(ll n, ll root)
{
	sll added, unadded;

	for(ll i = 1; i <= n; i++)
	{
		if(i == root)
		{
			added.insert(i);
			continue;
		}

		unadded.insert(i);
	}

	vpll edge;
	edge.reserve(n - 1);
	for(ll i = 0; i < n - 1; i++)
	{
		ll u = getRandomElement(added);
		ll v = getRandomElement(unadded);

		unadded.erase(v);
		added.insert(v);

		if(getRandomNumber(0, 1))
			std::swap(u, v);

		edge.push_back({u, v});
	}

	std::shuffle(edge.begin(), edge.end(), rd);

	for(ll i = 0; i < n - 1; i++)
		std::cout << edge[i].first << ' ' << edge[i].second << '\n';
}
