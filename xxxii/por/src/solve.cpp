#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::list<ll> lll;

int main()
{
	ll n;
	std::cin >> n;

	ll inversionCount;
	std::cout << 1 << ' ' << 1 << std::endl;
	std::cin >> inversionCount;

	if(inversionCount == 0)
		return 0;

	lll list;
	list.push_back(0);
	auto previousIterator = list.begin();
	for(ll i = 1; i < n; i++)
	{
		list.push_front(-i);
		list.push_back(i);
	}

	// for(ll e : list)
	// 	std::cerr << e << ' ';
	// std::cerr << std::endl;

	vll array(n);
	for(ll i = n - 1; i >= 1; i--)
	{
		std::cout << 1 << ' ' << (i + 1) << std::endl;

		ll nextInversionCount;
		std::cin >> nextInversionCount;

		ll difference = nextInversionCount - inversionCount;
		if(difference > 0)
			difference++;
		if(difference < 0)
			difference--;
		difference /= 2;

		inversionCount = nextInversionCount;

		auto iterator = previousIterator;
		std::advance(iterator, difference);

		array[i] = *iterator;
		std::swap(array[0], array[i]);

		// std::cerr << *previousIterator << " -(" << difference << ")-> " << *iterator << std::endl;
		list.erase(previousIterator);
		previousIterator = iterator;
	}

	// auto leftCandidate = previousIterator;
	// auto rightCandidate = previousIterator;
	// leftCandidate--;
	// rightCandidate--;

	// std::cerr << "Unprocessed array: ";
	// for(ll i = 0; i < n; i++)
	// 	std::cerr << array[i] << ' ';
	// std::cerr << std::endl;

	ll offset = 0;
	for(ll i = 0; i < n; i++)
		offset = std::min(offset, array[i]);

	for(ll i = 0; i < n; i++)
		array[i] -= offset;

	// std::cerr << "Decoded array: ";
	// for(ll i = 0; i < n; i++)
	// 	std::cerr << (array[i] + 1) << ' ';
	// std::cerr << std::endl;

	vll location(n, 0);
	for(ll i = 0; i < n; i++)
		location[array[i]] = i;

	// std::cerr << "Locations: ";
	// for(ll i = 0; i < n; i++)
	// 	std::cerr << (location[i] + 1) << ' ';
	// std::cerr << std::endl;

	for(ll i = 0; i < n; i++)
	{
		std::cout << (i + 1) << ' ' << (location[i] + 1) << std::endl;
		// std::cerr << (i + 1) << ' ' << (location[i] + 1) << std::endl;

		ll leftIndex = i;
		ll rightIndex = location[i];
		ll leftValue = array[leftIndex];
		ll rightValue = array[rightIndex];

		std::swap(array[leftIndex], array[rightIndex]);
		std::swap(location[leftValue], location[rightValue]);

		std::cin >> inversionCount;

		if(inversionCount == 0)
			return 0;
	}

	return -1;
}
