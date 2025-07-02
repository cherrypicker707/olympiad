// Solution for Subproblems 1 and 4
// 20/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::string str;

ll n;
str s;

void brute();
ll checkCombination(ll combination);
void printCombination(ll combination);
void ab();

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> n >> s;

	if(n <= 10)
	{
		brute();
		return 0;
	}

	ab();
}

void brute()
{
	ll m = (1 << n);

	ll maxResult = -1;
	ll maxCombination = -1;
	for(ll combination = 0; combination < m; combination++)
	{
		ll result = checkCombination(combination);

		if(result > maxResult)
		{
			maxResult = result;
			maxCombination = combination;
		}
	}

	std::cout << maxResult << '\n';
	printCombination(maxCombination);
}

ll checkCombination(ll combination)
{
	if(!(combination & (1 << 0)))
		return -1;

	vll letterCount(26, 0);
	ll odd = 0;

	ll length = LLONG_MAX;
	ll minLength = LLONG_MAX;

	for(ll i = 0; i <= n; i++)
	{
		if(combination & (1 << i) || i == n)
		{
			if(odd > 1)
				return -1;

			letterCount = vll(26, 0);
			odd = 0;

			minLength = std::min(minLength, length);
			length = 0;
		}

		if(i == n)
			continue;

		letterCount[s[i] - 'a']++;

		odd--;
		if(letterCount[s[i] - 'a'] % 2)
			odd += 2;

		length++;
	}

	return minLength;
}

void printCombination(ll combination)
{
	vll intervalBeginning;
	intervalBeginning.reserve(n);

	for(ll i = 0; i < n; i++)
		if(combination & (1 << i))
			intervalBeginning.push_back(i);

	std::cout << intervalBeginning.size() << '\n';
	for(ll i = 0; i < intervalBeginning.size(); i++)
	{
		std::cout << (intervalBeginning[i] + 1) << ' ';

		if(i + 1 < intervalBeginning.size())
		{
			std::cout << intervalBeginning[i + 1] << '\n';
			continue;
		}

		std::cout << n << '\n';
	}
}

void ab()
{
	bool aParity = 0, bParity = 0;
	for(ll i = 0; i < n; i++)
	{
		if(s[i] == 'a')
			aParity = !aParity;
		if(s[i] == 'b')
			bParity = !bParity;
	}

	if(aParity == 0 || bParity == 0)
	{
		std::cout << n << '\n';
		std::cout << 1 << '\n';
		std::cout << 1 << ' ' << n << '\n';
		return;
	}

	aParity = 0;
	bParity = 0;
	ll maxMinLength = -1;
	ll split = -1;
	for(ll i = 0; i < n; i++)
	{
		if(s[i] == 'a')
			aParity = !aParity;
		if(s[i] == 'b')
			bParity = !bParity;

		if(aParity == bParity)
			continue;

		ll minLength = std::min(i + 1, n - i - 1);
		if(minLength > maxMinLength)
		{
			maxMinLength = minLength;
			split = i;
		}
	}

	std::cout << maxMinLength << '\n';
	std::cout << 2 << '\n';
	std::cout << 1 << ' ' << (split + 1) << '\n';
	std::cout << (split + 2) << ' ' << n << '\n';
}
