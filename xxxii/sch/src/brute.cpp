// Solution for the Subproblems I and II
// 17/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<bool> vbool;

ll n;
vll a, b;

ll count;
vll move;

void brute();
bool check();

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

	brute();
}

void brute()
{
	count = 0;

	move = vll(n - 1);
	for(ll i = 0; i < n - 1; i++)
		move[i] = (i > 0 ? move[i - 1] : 0) + a[i] - b[i];

	while(!check())
	{
		vll aPrime = a;

		for(ll i = 0; i < n - 1; i++)
		{
			if(move[i] > 0 && a[i] > 0)
			{
				aPrime[i]--;
				aPrime[i + 1]++;
				move[i]--;
			}

			if(move[i] < 0 && a[i + 1] > 0)
			{
				aPrime[i]++;
				aPrime[i + 1]--;
				move[i]++;
			}
		}

		a = aPrime;
		count++;
	}

	std::cout << count << '\n';
}

bool check()
{
	for(ll i = 0; i < n; i++)
		if(a[i] != b[i])
			return false;
	return true;
}
