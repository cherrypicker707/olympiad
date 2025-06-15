#include <bits/stdc++.h>

typedef long long ll; typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;
typedef std::set<ll> sll;
typedef std::queue<ll> qll;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

ll t, n, k;
vvll adj;

vll subtreeSum;

void s2();
ll setSubtreeSum(ll u, ll p);

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> t;

	for(ll i = 0; i < t; i++)
	{
		std::cin >> n >> k;

		adj = vvll(n);

		for(ll j = 0; j < n - 1; j++)
		{
			ll u, v;
			std::cin >> u >> v;
			u--;
			v--;

			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		s2();
	}

	return 0;
}

void s2()
{
	subtreeSum = vll(n);

	setSubtreeSum(0, -1);

	vpll largestSubtreeList;
	largestSubtreeList.reserve(n);
	for(ll u = 0; u < n; u++)
	{
		ll largestSubtree = 0;

		for(ll v : adj[u])
		{
			if(subtreeSum[u] < subtreeSum[v])
				continue;

			largestSubtree = std::max(largestSubtree, subtreeSum[v]);
		}

		largestSubtree = std::max(largestSubtree, n - subtreeSum[u]);

		largestSubtreeList.push_back({largestSubtree, u});
	}

	std::sort(largestSubtreeList.begin(), largestSubtreeList.end());

	for(ll i = 0; i < k; i++)
		std::cout << (largestSubtreeList[i].second + 1) << ' ';
	std::cout << '\n';
}

ll setSubtreeSum(ll u, ll p)
{
	subtreeSum[u] = 1;

	for(ll v : adj[u])
	{
		if(v == p)
			continue;

		subtreeSum[u] += setSubtreeSum(v, u);
	}

	return subtreeSum[u];
}
