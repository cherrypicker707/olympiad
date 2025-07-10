// Solution for All Subproblems
// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::pair<ll, ll> pll;
typedef std::deque<ll> dll;

ll n;
vll a, b;

ll result, offset;
vll move;
dll gap;

void greedy();
void process(ll x, ll y);

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> n;

	a = vll(n);
	for(ll i = 0; i < n; i++)
		std::cin >> a[i];

	b = vll(n);
	for(ll i = 0; i < n; i++)
		std::cin >> b[i];

	greedy();
}

void greedy()
{
	result = 0;

	move = vll(n - 1);
	for(ll i = 0; i < n - 1; i++)
		move[i] = (i > 0 ? move[i - 1] : 0) + a[i] - b[i];

	offset = 0;
	gap = dll();
	for(ll i = 0; i < n - 1; i++)
	{
		if(move[i] <= 0)
		{
			offset = 0;
			gap = dll();
			continue;
		}

		process(a[i], move[i]);
	}

	offset = 0;
	gap = dll();
	for(ll i = n - 2; i >= 0; i--)
	{
		if(move[i] >= 0)
		{
			offset = 0;
			gap = dll();
			continue;
		}

		process(a[i + 1], -move[i]);
	}

	std::cout << result << '\n';
}

void process(ll x, ll y)
{
	gap.push_back(-offset);

	for(ll i = 0; i < x; i++)
	{
		if(gap.empty())
			break;

		gap.pop_back();
	}

	while(!gap.empty() && gap.front() + offset - gap.size() + 1 >= y)
		gap.pop_front();

	result = std::max(result, (ll)(y + gap.size()));
	offset++;
}
