// 100/100 points

#include <bits/stdc++.h>

typedef std::vector<bool> vbool;
typedef long long ll;

ll n, s;

void greedy();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n >> s;
    greedy();

    return 0;
}

void greedy()
{
    if(n == 1)
    {
        if(s == 0)
            std::cout << 0 << '\n';
        else
            std::cout << "NIE\n";

        return;
    }

    vbool increase(n, false);

    ll k = (n - 1) * n / 2 + s;

    if(k < 0 || k % 2)
    {
        std::cout << "NIE\n";
        return;
    }

    for(ll i = n - 1; i >= 0; i--)
    {
        if(2 * i <= k)
        {
            increase[i] = true;
            k -= 2 * i;
        }
    }

    if(k > 0)
    {
        std::cout << "NIE\n";
        return;
    }

    ll x = 0;
    for(ll i = n - 1; i >= 0; i--)
    {
        std::cout << x << '\n';

        x--;
        if(increase[i])
            x += 2;
    }
}
