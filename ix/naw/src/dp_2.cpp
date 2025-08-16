// 100/100 points

#include <bits/stdc++.h>

typedef std::vector<bool> vbool;
typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;
typedef std::vector<vvll> vvvll;

const ll modulus = 1'000'000'000;

ll n;
vbool plus;

vvll memo;

void dp_2();

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

    dp_2();
    return 0;
}

void dp_2()
{
    if(plus[0])
    {
        std::cout << 0 << '\n';
        return;
    }

    vvll memo = vvll(2, vll(n - 1, 0));
    memo[0][0] = 1;

    for(ll i = 1; i < n - 1; i++)
    {
        ll sum = 0;
        for(ll j = i; j >= 0; j--)
        {
            if(j - 1 >= 0)
                sum = (sum + memo[(i + 1) % 2][j - 1]) % modulus;

            if(j % 2 == plus[i])
            {
                memo[i % 2][j] = sum;
                continue;
            }

            memo[i % 2][j] = 0;
        }
    }

    ll result = 0;
    for(ll i = 0; i < n - 1; i++)
        result = (result + memo[n % 2][i]) % modulus;

    std::cout << result << '\n';
}
