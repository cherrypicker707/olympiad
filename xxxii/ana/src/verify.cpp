// Program for Verifying Correctness of Output of a Solution

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::string str;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

ll n, result, intervalCount;
vpll interval;
str s;

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> n >> s;

	std::cin >> result >> intervalCount;

	interval = vpll(intervalCount);
	for(ll i = 0; i < intervalCount; i++)
		std::cin >> interval[i].first >> interval[i].second;

	for(ll i = 0; i < intervalCount; i++)
	{
		if(i == 0 && interval[i].first != 1)
			return -1;

		if(i == intervalCount - 1 && interval[i].second != n)
			return -1;

		if(i + 1 < intervalCount && interval[i].second + 1 != interval[i + 1].first)
			return -1;

		if(interval[i].second - interval[i].first + 1 < result)
			return -1;

		ll odd = 0;
		vll letterCount(26, 0);
		for(ll j = interval[i].first - 1; j < interval[i].second; j++)
		{
			letterCount[s[j] - 'a']++;

			odd--;
			if(letterCount[s[j] - 'a'] % 2)
				odd += 2;
		}

		if(odd > 1)
			return -1;
	}

	return 0;
}
