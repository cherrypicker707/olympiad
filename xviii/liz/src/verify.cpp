// Used for testing.

#include <bits/stdc++.h>

typedef std::vector<bool> vbool;
typedef long long ll;
typedef std::vector<ll> vll;

ll n, m;
vbool a;
vll k;

vbool p;

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

	vll prefixSum(n + 1);
	prefixSum[0] = 0;
	for(ll i = 0; i < n; i++)
		prefixSum[i + 1] = prefixSum[i] + (a[i] ? 2 : 1);

	p = vbool(m, false);
	for(ll i = 0; i < m; i++)
	{
		std::string s;
		std::cin >> s;

		if(s == "NIE")
			continue;

		p[i] = true;

		ll l = std::stoll(s) - 1, r;
		std::cin >> r;

		if(prefixSum[r] - prefixSum[l] != k[i])
		{
			std::cerr << "Wrong Interval! First file, line " << (i + 1) <<'\n';
			return 1;
		}
	}

	for(ll i = 0; i < m; i++)
	{
		std::string s;
		std::cin >> s;

		if(s == "NIE")
		{
			if(p[i])
			{
				std::cerr << "Mismatch! Line " << (i + 1) << '\n';
				return 1;
			}

			continue;
		}

		if(!p[i])
		{
			std::cerr << "Mismatch! Line " << (i + 1) << '\n';
			return 1;
		}

		ll l = std::stoll(s) - 1, r;
		std::cin >> r;

		if(prefixSum[r] - prefixSum[l] != k[i])
		{
			std::cerr << "Wrong Interval! Second file, line " << (i + 1) <<'\n';
			return 1;
		}
	}

	return 0;
}
