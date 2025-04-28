// Solution for All Subproblems
// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::string str;

#define BIG_NUMBER 1'000'000'000LL

ll n;
vll a;
str s;

void s1();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> s;

    n = s.size();

    a.resize(n);
    for(ll i = 0; i < n; i++)
        a[i] = (s[i] - '0');

    s1();
    return 0;
}

void s1()
{
    ll power_of_ten, sum_of_digits, answer;
    vll left(n + 1, 0), right(n + 1, 0);

    sum_of_digits = 0;
    for(ll i = 0; i < n; i++)
        sum_of_digits += a[i];

    if(sum_of_digits == 1 && a[0] == 1)
    {
        if(n == 1)
        {
            std::cout << 0 << '\n';
            return;
        }

        std::cout << 1 << '\n';
        return;
    }

    left[0] = 0;
    for (ll i = 1; i <= n; i++)
    {
        if(a[i - 1] == 0)
        {
            left[i] = left[i - 1];
            continue;
        }

        left[i] = left[i - 1] + 1 + (9 - a[i - 1]);
    }

    power_of_ten = 1;
    right[0] = 0;
    for (ll i = 1; i <= n; i++)
    {
        if(power_of_ten == BIG_NUMBER && a[n - i] == 9)
        {
            right[i] = right[i - 1];
            continue;
        }

        if(power_of_ten == BIG_NUMBER)
        {
            right[i] = BIG_NUMBER;
            continue;
        }

        right[i] = std::min(right[i - 1] + power_of_ten * (9 - a[n - i]), BIG_NUMBER);
        power_of_ten *= 10;
        continue;
    }

    answer = LLONG_MAX;
    for(ll i = 0; i <= n; i++)
        answer = std::min(answer, left[i] + right[n - i]);
    std::cout << (answer + 2) << '\n';
}
