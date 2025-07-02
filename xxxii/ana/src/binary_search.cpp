// Solution for all Subproblems
// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;
typedef std::string str;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;
typedef std::map<ll, ll> mll;

ll n;
str s;

void binary_search();
bool check(ll k, vpll &interval);

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> n >> s;

	binary_search();
}

void binary_search()
{
	vpll interval;
	interval.reserve(n);

	ll result = 0;
	ll left = 1, right = n + 1;
	while(left < right)
	{
		ll middle = (left + right) / 2;

		if(check(middle, interval))
		{
			result = std::max(result, middle);
			left = middle + 1;
			continue;
		}

		right = middle;
	}

	check(result, interval);

	std::cout << result << '\n';
	std::cout << interval.size() << '\n';
	for(ll i = 0; i < interval.size(); i++)
		std::cout << interval[i].first << ' ' << interval[i].second << '\n';
}

bool check(ll k, vpll &interval)
{
	mll available;
	vll parity(n + 1);
	vll previous(n + 1);

	parity[0] = previous[0] = 0;
	for(ll i = 1; i <= n; i++)
	{
		if(i - k >= 0 && previous[i - k] != -1)
			available[parity[i - k]] = i - k;

		parity[i] = parity[i - 1] ^ (1 << (s[i - 1] - 'a'));

		previous[i] = -1;

		if(available.count(parity[i]))
		{
			previous[i] = available[parity[i]];
			continue;
		}

		for(ll j = 0; j < 26; j++)
		{
			ll alternative = parity[i] ^ (1 << j);
			if(available.count(alternative))
			{
				previous[i] = available[alternative];
				break;
			}
		}
	}

	interval.clear();

	if(previous[n] == -1)
		return false;

	ll pointer = n;
	while(previous[pointer] != pointer)
	{
		interval.push_back({previous[pointer] + 1, pointer});
		pointer = previous[pointer];
	}

	std::reverse(interval.begin(), interval.end());

	return true;
}
