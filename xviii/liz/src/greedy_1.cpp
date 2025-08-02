// 100/100 points

#include <bits/stdc++.h>

typedef std::vector<bool> vbool;
typedef long long ll;
typedef std::vector<ll> vll;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

ll n, m;
vbool a;
vll k;

vll prefixSum;
vpll answer;

void greedy();
void decompose(ll l, ll r);

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

	greedy();

	return 0;
}

void greedy()
{
	prefixSum = vll(n + 1);
	prefixSum[0] = 0;
	for(ll i = 0; i < n; i++)
		prefixSum[i + 1] = prefixSum[i] + (a[i] ? 2 : 1);

	answer = vpll(prefixSum[n] + 1, {-1, -1});
	decompose(0, n);

	ll leftmostOne = -1;
	for(ll i = 0; i < n; i++)
	{
		if(!a[i])
		{
			leftmostOne = i;
			break;
		}
	}

	ll rightmostOne = -1;
	for(ll i = n - 1; i >= 0; i--)
	{
		if(!a[i])
		{
			rightmostOne = i;
			break;
		}
	}

	if(leftmostOne != -1 && rightmostOne != -1)
	{
		ll l = 0, r = rightmostOne;
		if(prefixSum[n] - prefixSum[leftmostOne + 1] > prefixSum[rightmostOne] - prefixSum[0])
		{
			l = leftmostOne + 1;
			r = n;
		}

		decompose(l, r);
	}


	for(ll i = 0; i < m; i++)
	{
		if(k[i] > prefixSum[n] || answer[k[i]].first == -1)
		{
			std::cout << "NIE\n";
			continue;
		}

		std::cout << (answer[k[i]].first + 1) << ' ' << answer[k[i]].second << '\n';
	}
}

void decompose(ll l, ll r)
{
	while(l >= 0 && l < n && r >= 1 && r <= n && prefixSum[r] - prefixSum[l] >= 0)
	{
		answer[prefixSum[r] - prefixSum[l]] = {l, r};

		if(a[l])
		{
			l++;
			continue;
		}

		if(a[r - 1])
		{
			r--;
			continue;
		}

		l++;
		r--;
	}
}
