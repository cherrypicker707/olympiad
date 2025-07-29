#include <bits/stdc++.h>

typedef std::vector<bool> vbool;
typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;

ll n, m, k;
vvll adjacentLeft, adjacentRight;

void readAdjacent(vvll &adjacent, const ll &count);
void solve();
bool check(const vbool &combination, const vll &permutation);

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> n >> m >> k;
	readAdjacent(adjacentLeft, n);
	readAdjacent(adjacentRight, m);

	solve();

	return 0;
}

void readAdjacent(vvll &adjacent, const ll &count)
{
	adjacent.resize(count);
	for(ll i = 0; i < count - 1; i++)
	{
		ll u, v;
		std::cin >> u >> v;
		u--;
		v--;

		adjacent[u].push_back(v);
		adjacent[v].push_back(u);
	}

	for(ll i = 0; i < count; i++)
		std::sort(adjacent[i].begin(), adjacent[i].end());
}

void solve()
{
	vbool combination(m, false);
	std::fill(combination.end() - n, combination.end(), true);

	vll permutation(n);
	for(ll i = 0; i < n; i++)
		permutation[i] = i;

	ll result = 0;
	do
		do
			result = (result + check(combination, permutation)) % k;
		while(std::next_permutation(permutation.begin(), permutation.end()));
	while(std::next_permutation(combination.begin(), combination.end()));

	std::cout << result << '\n';
}

bool check(const vbool &combination, const vll &permutation)
{
	vll mapping(n);
	for(ll i = 0, j = 0; i < m; i++)
	{
		if(!combination[i])
			continue;

		mapping[permutation[j++]] = i;
	}

	for(ll u = 0; u < n; u++)
		for(ll v : adjacentLeft[u])
			if(!std::binary_search(adjacentRight[mapping[u]].begin(), adjacentRight[mapping[u]].end(), mapping[v]))
				return false;

	return true;
}
