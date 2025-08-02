// 16/100 points

#include <bits/stdc++.h>

typedef std::vector<bool> vbool;
typedef long long ll;
typedef std::vector<ll> vll;

ll n, m;
vbool a;
vll k;

void brute();

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> n >> m;

	a = vbool(n, false);
	for(ll i = 0; i < n; i++)
	{
		char c;
		std::cin >> c;

		if(c == 'T')
			a[i] = true;
	}

	k = vll(m);
	for(ll i = 0 ; i < m; i++)
		std::cin >> k[i];

	brute();

	return 0;
}

void brute()
{
	vll prefixSumArray(n + 1);
	prefixSumArray[0] = 0;
	for(ll i = 0; i < n; i++)
		prefixSumArray[i + 1] = prefixSumArray[i] + (a[i] ? 2 : 1);

	for(ll i = 0; i < m; i++)
	{
		bool done = false;
		for(ll l = 0; l < n; l++)
		{
			for(ll r = l; r <= n; r++)
			{
				ll sum = prefixSumArray[r] - prefixSumArray[l];
				if(sum == k[i])
				{
					std::cout << (l + 1) << ' ' << r << '\n';
					done = true;
					break;
				}
			}

			if(done)
				break;
		}

		if(!done)
			std::cout << "NIE\n";
	}
}
