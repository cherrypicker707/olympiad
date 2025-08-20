// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<char> vchar;

ll n;
vchar a;

void greedy();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n;

    a = vchar(n - 1);
    for(ll i = 0; i < n - 1; i++)
        std::cin >> a[i];

    greedy();
    return 0;
}

void greedy()
{
    std::cout << '-';

    for(ll i = 1; i < n - 1; i++)
    {
        if(a[i - 1] == '-' && a[i] == '+')
            std::cout << '(';

        std::cout << '-';

        if(a[i] == '+' && (i >= n - 2 || a[i + 1] == '-'))
            std::cout << ')';
    }

    std::cout << '\n';
}
