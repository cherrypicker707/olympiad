// Solution for the Subproblem 4
// 12/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::string str;

ll n;
str s;

void ab();

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> n >> s;

	ab();
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
