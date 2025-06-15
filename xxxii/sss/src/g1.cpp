#include <bits/stdc++.h>

typedef long long ll;

std::random_device dev;
std::mt19937_64 rd(dev());

ll t, n, k;

int main(int argc, char **argv)
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	assert(argc == 4);
	t = atoi(argv[1]);
	n = atoi(argv[2]);
	k = atoi(argv[3]);

	for(ll i = 0; i < t; i++)
		std::cout << std::uniform_int_distribution<ll>(1, n)(rd) << '\n';

	return 0;
}
