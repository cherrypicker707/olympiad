// Solution for Subproblems I, II and III
// 27/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::vector<str> vstr;
typedef std::tuple<bool, ll, char> tboolllchar;
typedef std::vector<tboolllchar> vtboolllchar;

ll n, q;
vstr unsorted, sorted;
vtboolllchar query;

void brute();
str sort(str string);
void check();

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> n >> q;

	unsorted = vstr(2);
	std::cin >> unsorted[0] >> unsorted[1];

	query.reserve(q);
	for(ll i = 0; i < q; i++)
	{
		ll type, index;
		char c;
		std::cin >> type >> index >> c;

		query.push_back({type == 2, index - 1, c});
	}

	brute();
	return 0;
}

void brute()
{
	sorted = vstr(2);
	sorted[0] = sort(unsorted[0]);
	sorted[1] = sort(unsorted[1]);

	check();

	for(ll i = 0; i < q; i++)
	{
		unsorted[std::get<0>(query[i])][std::get<1>(query[i])] = std::get<2>(query[i]);
		sorted[std::get<0>(query[i])] = sort(unsorted[std::get<0>(query[i])]);

		check();
	}
}


str sort(str string)
{
	if(string.size() == 1)
		return string;

	ll half = string.size() / 2;
	str left = sort(string.substr(0, half));
	str right = sort(string.substr(half, half));

	if(left > right)
		return right + left;

	return left + right;
}

void check()
{
	if(sorted[0] == sorted[1])
	{
		std::cout << "TAK\n";
		return;
	}

	std::cout << "NIE\n";
}
