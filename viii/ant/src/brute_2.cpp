// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

void brute2();
void generateNumbers(ll currentNumber, ll primeIndex, ll maxExponent, ll dividerCount);

ll n;

vll prime, antiprime;
vpll number;

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n;

    brute2();
    return 0;
}

void brute2()
{
    prime = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    generateNumbers(1, 0, 30, 1);
    std::sort(number.begin(), number.end());

    ll max = 0;
    for(ll i = 0; i < number.size(); i++)
    {
        if(number[i].second > max)
        {
            max = number[i].second;
            antiprime.push_back(number[i].first);
        }
    }

    ll result = antiprime.back();
    std::cout << result << '\n';
}

void generateNumbers(ll currentNumber, ll primeIndex, ll maxExponent, ll dividerCount)
{
    if(primeIndex == prime.size())
    {
        number.push_back({currentNumber, dividerCount});
        return;
    }

    for(ll i = 0; i <= maxExponent; i++)
    {
        generateNumbers(currentNumber, primeIndex + 1, i, dividerCount * (i + 1));

        currentNumber *= prime[primeIndex];
        if(currentNumber > n)
            break;
    }
}
