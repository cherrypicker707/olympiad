#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;

int main()
{
	ll n;
	std::cin >> n;

	ll inversionCount;
	std::cout << 1 << ' ' << 1 << '\n';
	std::cin >> inversionCount;

	for(ll i = 0; i < n; i++)
	{
		for(ll j = n - 1; j >= i + 1; j--)
		{
			ll nextInversionCount;

			std::cout << (i + 1) << ' ' << (j + 1) << '\n';
			std::cin >> nextInversionCount;

			if(nextInversionCount > inversionCount)
			{
				std::cout << (i + 1) << ' ' << (j + 1) << '\n';
				std::cin >> nextInversionCount;
			}

			inversionCount = nextInversionCount;

			if(inversionCount == 0)
				return 0;
		}
	}

	return 0;
}
