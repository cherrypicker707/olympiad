#include <bits/stdc++.h>

typedef std::vector<bool> vbool;
typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

ll n, m, k;
vvll adjacentLeft, adjacentRight;

vvll binaryTreeLeft, binaryTreeRight;
vvll memo;

vvll dag;

void readAdjacent(vvll &adjacent, const ll &count);
void solve();
void createBinaryTreeWithDFS(vvll &binaryTree, const vvll &adjacent, ll u, ll parent);
ll getValue(ll u, ll v);

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
	ll rootRight = -1;
	while(adjacentRight[++rootRight].size() > 2);
	binaryTreeRight = vvll(m);
	createBinaryTreeWithDFS(binaryTreeRight, adjacentRight, rootRight, -1);

	vpll subtree;
	subtree.reserve(3 * n + 2);

	for(ll u = 0; u < n; u++)
		if(adjacentLeft[u].size() < 3)
			subtree.push_back({-1, u});

	for(ll u = 0; u < n; u++)
		for(ll v : adjacentLeft[u])
			subtree.push_back({u, v});

	ll q = subtree.size();

	dag = vvll(q);
	for(ll i = 0; i < q; i++)
	{
		for(ll u : adjacentLeft[subtree[i].second])
		{
			if(u == subtree[i].first)
				continue;

			pll dependency = { subtree[i].second, u };
			ll j = std::distance(subtree.begin(), std::lower_bound(subtree.begin(), subtree.end(), dependency));
			dag[i].push_back(j);
		}
	}

	ll result = 0;
	memo = vvll(q, vll(m, -1));
	for(ll i = 0; i < q; i++)
	{
		if(subtree[i].first != -1)
			break;

		for(ll j = 0; j < m; j++)
			result = (result + getValue(i, j)) % k;
	}

	std::cout << result << '\n';
}

void createBinaryTreeWithDFS(vvll &binaryTree, const vvll &adjacent, ll u, ll parent)
{
	if(binaryTree.size() < adjacent.size())
		binaryTree = vvll(adjacent.size());

	for(ll v : adjacent[u])
	{
		if(v == parent)
			continue;

		createBinaryTreeWithDFS(binaryTree, adjacent, v, u);
		binaryTree[u].push_back(v);
	}
}

ll getValue(ll u, ll v)
{
    if(memo[u][v] != -1)
        return memo[u][v];

    if(dag[u].size() > binaryTreeRight[v].size())
        return memo[u][v] = 0;

    if(dag[u].size() == 0)
        return memo[u][v] = 1;

    if(dag[u].size() == 1 && binaryTreeRight[v].size() == 1)
        return memo[u][v] = getValue(dag[u][0], binaryTreeRight[v][0]);

    if(dag[u].size() == 1 && binaryTreeRight[v].size() == 2)
        return memo[u][v] = (getValue(dag[u][0], binaryTreeRight[v][0]) + getValue(dag[u][0], binaryTreeRight[v][1])) % k;

    ll x = (getValue(dag[u][0], binaryTreeRight[v][0]) * getValue(dag[u][1], binaryTreeRight[v][1])) % k;
    ll y = (getValue(dag[u][0], binaryTreeRight[v][1]) * getValue(dag[u][1], binaryTreeRight[v][0])) % k;
    return memo[u][v] = (x + y) % k;
}
