// Solution for the Subproblems 1, 2 and 3
// 39/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;
typedef std::string str;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

ll n;
str s;

vll result, previousInterval;
vvll letterPrefixCount;

void dp();
bool isIntervalValid(ll left, ll right);
vpll getInterval();

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> n >> s;

	dp();
}

void dp()
{
	letterPrefixCount = vvll(26, vll(n + 1, 0));
	for(ll i = 0; i < 26; i++)
		for(ll j = 1; j <= n; j++)
			letterPrefixCount[i][j] = letterPrefixCount[i][j - 1] + (s[j - 1] == ('a' + i));

	result = vll(n + 1, 0);
	previousInterval = vll(n + 1, -1);

	result[0] = LLONG_MAX;
	for(ll right = 1; right <= n; right++)
	{
		for(ll left = 0; left < right; left++)
		{
			if(!isIntervalValid(left, right))
				continue;

			ll currentResult = std::min(result[left], right - left);

			if(currentResult > result[right])
			{
				result[right] = currentResult;
				previousInterval[right] = left;
			}
		}
	}

	std::cout << result[n] << '\n';

	vpll interval = getInterval();
	std::cout << interval.size() << '\n';
	for(ll i = 0; i < interval.size(); i++)
		std::cout << interval[i].first << ' ' << interval[i].second << '\n';
}

bool isIntervalValid(ll left, ll right)
{
	ll odd = 0;
	for(ll i = 0; i < 26; i++)
	{
		ll letterCount = letterPrefixCount[i][right] - letterPrefixCount[i][left];
		odd += letterCount % 2;
	}

	if(odd == 0 || odd == 1)
		return true;

	return false;
}

vpll getInterval()
{
	vpll interval;
	ll i = n;

	while(i > 0)
	{
		ll j = previousInterval[i];
		interval.push_back({j + 1, i});
		i = j;
	}

	std::reverse(interval.begin(), interval.end());
	return interval;
}
