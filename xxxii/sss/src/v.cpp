#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;
typedef std::set<ll> sll;
typedef std::queue<ll> qll;

std::random_device dev;
std::mt19937_64 rd(dev());

ll t, n, k;
vll correctAnswer;

int main(int argc, char **argv)
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	assert(argc == 4);
	t = atoi(argv[1]);
	n = atoi(argv[2]);
	k = atoi(argv[3]);

	correctAnswer = vll(t);

	for(ll i = 0; i < t; i++)
		std::cin >> correctAnswer[i];

	ll successCount = 0;
	for(ll i = 0; i < t; i++)
	{
		bool success = false;

		for(ll j = 0; j < k; j++)
		{
			ll possibility;
			std::cin >> possibility;

			if(possibility == correctAnswer[i])
				success = true;
		}

		if(success)
			successCount++;
	}

	float successRate = (float)successCount / (float)t;
	std::cout << successRate << '\n';
}
