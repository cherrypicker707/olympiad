#include <bits/stdc++.h>

typedef std::vector<bool> vbool;
typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;

ll n, m, k;
vvll adjacentLeft, adjacentRight;

vvll binaryTreeLeft, binaryTreeRight;
vvll memo;

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

	ll result = 0;
	for(ll rootLeft = 0; rootLeft < n; rootLeft++)
	{
		if(adjacentLeft[rootLeft].size() > 2)
			continue;

		binaryTreeLeft = vvll(n);
		createBinaryTreeWithDFS(binaryTreeLeft, adjacentLeft, rootLeft, -1);

		memo = vvll(n, vll(m, -1));
		for(ll u = 0; u < m; u++)
			result = (result + getValue(rootLeft, u)) % k;
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

    if(binaryTreeLeft[u].size() > binaryTreeRight[v].size())
        return memo[u][v] = 0;

    if(binaryTreeLeft[u].size() == 0)
        return memo[u][v] = 1;

    if(binaryTreeLeft[u].size() == 1 && binaryTreeRight[v].size() == 1)
        return memo[u][v] = getValue(binaryTreeLeft[u][0], binaryTreeRight[v][0]);

    if(binaryTreeLeft[u].size() == 1 && binaryTreeRight[v].size() == 2)
        return memo[u][v] = (getValue(binaryTreeLeft[u][0], binaryTreeRight[v][0]) + getValue(binaryTreeLeft[u][0], binaryTreeRight[v][1])) % k;

    ll x = (getValue(binaryTreeLeft[u][0], binaryTreeRight[v][0]) * getValue(binaryTreeLeft[u][1], binaryTreeRight[v][1])) % k;
    ll y = (getValue(binaryTreeLeft[u][0], binaryTreeRight[v][1]) * getValue(binaryTreeLeft[u][1], binaryTreeRight[v][0])) % k;
    return memo[u][v] = (x + y) % k;
}
