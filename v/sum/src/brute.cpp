// 30/100 points

#include <bits/stdc++.h>

typedef std::vector<bool> vbool;
typedef long long ll;

ll n, s;

void brute();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n >> s;
    brute();

    return 0;
}

void brute()
{
    ll combinationCount = (1 << (n - 1));
    for(ll combination = 0; combination < combinationCount; combination++)
    {
        ll k = 0, sum = 0;
        for(ll i = 0; i < n - 1; i++)
        {
            k--;
            if(combination & (1 << i))
                k += 2;

            sum += k;
        }

        if(sum == s)
        {
            k = 0;
            std::cout << 0 << '\n';

            for(ll i = 0; i < n - 1; i++)
            {
                k--;
                if(combination & (1 << i))
                    k += 2;

                std::cout << k << '\n';
            }

            return;
        }
    }

    std::cout << "NIE\n";
}
