// Solution for All Subproblems
// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<bool> vbool;

ll n;
vll s, z;

void s1();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n;

    s.resize(n);
    z.resize(n);

    for(ll i = 0; i < n; i++)
    {
        std::cin >> s[i] >> z[i];
        s[i]--;
        z[i]--;
    }

    s1();

    return 0;
}

void s1()
{
    bool undefeatable_appeared;
    ll undefeatable_count, min, max;
    vbool is_undefeatable(n, false);
    vll a(n);

    for(ll i = 0; i < n; i++)
        a[s[i]] = z[i];

    undefeatable_count = 0;
    max = LLONG_MIN;
    for(ll i = n - 1; i >= 0; i--)
    {
        if(a[i] > max)
        {
            is_undefeatable[i] = true;
            undefeatable_count++;
            max = a[i];
        }
    }

    if(undefeatable_count % 2 == 0)
    {
        std::cout << "TAK\n";
        return;
    }

    min = LLONG_MAX;
    for(ll i = n - 1; i >= 0; i--)
    {
        if(is_undefeatable[i])
        {
            min = std::min(min, a[i]);
            continue;
        }

        if(a[i] > min)
        {
            std::cout << "TAK\n";
            return;
        }
    }

    undefeatable_appeared = false;
    for(ll i = 0; i < n; i++)
    {
        undefeatable_appeared |= is_undefeatable[i];

        if(!is_undefeatable[i] && undefeatable_appeared)
        {
            std::cout << "TAK\n";
            return;
        }
    }

    std::cout << "NIE\n";
    return;
}
