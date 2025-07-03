// Solution for All Subproblems
// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::string str;
typedef std::vector<str> vstr;
typedef std::tuple<bool, ll, char> tboolllchar;
typedef std::vector<tboolllchar> vtboolllchar;

class HashSegmentTree
{
public:
	HashSegmentTree();
	HashSegmentTree(str string);
	void update(ll index, char letter);
	ll getHash();

private:
	ll count, maxLayer;
	vll subtreeHash;
	void calculateHash(ll i);
};

typedef std::vector<HashSegmentTree> vHashSegmentTree;

const ll p = 29LL;
const ll mod = 1'000'000'009LL;

ll n, q;
vstr unsorted;
vtboolllchar query;
vHashSegmentTree hashSegmentTree;
vll exponent;

void hash();
void check();

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> n >> q;

	unsorted = vstr(2);
	std::cin >> unsorted[0] >> unsorted[1];

	query.reserve(q);
	for(ll i = 0; i < q; i++)
	{
		ll type, index;
		char c;
		std::cin >> type >> index >> c;

		query.push_back({type == 2, index - 1, c});
	}

	hash();
	return 0;
}

void hash()
{
	exponent = vll(n + 1);
	exponent[0] = p;
	for(ll i = 1; i <= n; i++)
		exponent[i] = (exponent[i - 1] * exponent[i - 1]) % mod;

	hashSegmentTree = vHashSegmentTree(2);

	for(ll i = 0; i < 2; i++)
		hashSegmentTree[i] = HashSegmentTree(unsorted[i]);

	check();

	for(ll i = 0; i < q; i++)
	{
		hashSegmentTree[std::get<0>(query[i])].update(std::get<1>(query[i]), std::get<2>(query[i]));
		check();
	}
}

void check()
{
	if(hashSegmentTree[0].getHash() == hashSegmentTree[1].getHash())
	{
		std::cout << "TAK\n";
		return;
	}

	std::cout << "NIE\n";
}

HashSegmentTree::HashSegmentTree()
{
	count = 0;
}

HashSegmentTree::HashSegmentTree(str string)
{
	count = string.size();
	maxLayer = log2(2 * count - 1);
	subtreeHash = vll(2 * count);

	for(ll i = count; i < 2 * count; i++)
		subtreeHash[i] = string[i - count] - 'a';

	for(ll i = count - 1; i >= 1; i--)
		calculateHash(i);
}

void HashSegmentTree::update(ll index, char letter)
{
	index += count;
	subtreeHash[index] = letter - 'a';
	index /= 2;

	while(index >= 1)
	{
		calculateHash(index);
		index /= 2;
	}
}

ll HashSegmentTree::getHash()
{
	return subtreeHash[1];
}

void HashSegmentTree::calculateHash(ll i)
{
	ll left = subtreeHash[2 * i];
	ll right = subtreeHash[2 * i + 1];
	if(left > right)
		std::swap(left, right);

	ll layer = log2(i);
	ll layerDifference = maxLayer - layer;
	ll coefficient = exponent[layerDifference];

	subtreeHash[i] = ((coefficient * left) % mod + right) % mod;
}

