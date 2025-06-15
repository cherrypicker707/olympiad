// Solution for Subproblems I, II and III
// 80/100

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;
typedef std::set<ll> sll;
typedef std::queue<ll> qll;

ll t, n, k;
vvll adj;

void s1();

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

		s1();
	}

	return 0;
}

void s1()
{
	vll deg(n);
	qll leafs;

	for(ll i = 0; i < n; i++)
	{
		deg[i] = adj[i].size();

		if(deg[i] == 1)
			leafs.push(i);
	}

	sll vertices;
	for(ll i = 0; i < n; i++)
		vertices.insert(i);

	while(vertices.size() > k)
	{
		ll u = leafs.front();
		leafs.pop();

		deg[u]--;
		vertices.erase(u);

		for(ll v : adj[u])
		{
			deg[v]--;

			if(deg[v] == 1)
				leafs.push(v);
		}
	}

	for(ll u : vertices)
		std::cout << (u + 1) << ' ';
	std::cout << '\n';
}
