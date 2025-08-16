// 60/100 points

#include <bits/stdc++.h>

typedef std::vector<bool> vbool;
typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;
typedef std::vector<vvll> vvvll;

const ll modulus = 1'000'000'000;

ll n;
vbool plus;

vvvll memo;

void dp_1();
ll getResult(ll left, ll right, bool negate);

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n;
    plus = vbool(n - 1, false);
    for(ll i = 0; i < n - 1; i++)
    {
        char sign;
        std::cin >> sign;

        if(sign == '+')
            plus[i] = true;
    }

    dp_1();
    return 0;
}

void dp_1()
{
    memo = vvvll(n, vvll(n, vll(2, -1)));
    ll result = getResult(0, n - 1, false);
    std::cout << result << '\n';
}

ll getResult(ll left, ll right, bool negate)
{
    if(memo[left][right][negate] != -1)
        return memo[left][right][negate];

    if(left == right)
        return memo[left][right][negate] = 1;

    ll result = 0;
    for(ll middle = left; middle < right; middle++)
    {
        if(plus[middle] == negate)
        {
            ll delta = (getResult(left, middle, negate) * getResult(middle + 1, right, !negate)) % modulus;
            result = (result + delta) % modulus;
        }
    }

    return memo[left][right][negate] = result;
}
