// Random Test Generator

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;

std::mt19937_64 mt;

ll getrannum(ll min, ll max);

int main(int argc, char **argv)
{
    ll n = atoi(argv[1]);
    ll max_a = atoi(argv[2]);
    ll equal = atoi(argv[3]);
    mt.seed(atoi(argv[4]));

    std::cout << n << '\n';

    vll a(n);

    for(ll i = 0; i < n; i++)
        a[i] = getrannum(1, max_a);

    if(equal)
    {
        for(ll i = 0; i < n; i++)
            std::cout << a[i] << ' ';
        std::cout << '\n';

        for(ll i = 0; i < n; i++)
            std::cout << a[i] << ' ';
        std::cout << '\n';

        return 0;
    }

    for(ll i = 0; i < n; i++)
        std::cout << a[i] << ' ';
    std::cout << '\n';

    for(ll i = 0; i < n; i++)
        std::cout << getrannum(1, max_a) << ' ';
    std::cout << '\n';

    return 0;
}

ll getrannum(ll min, ll max)
{
    return std::uniform_int_distribution<ll>(min, max)(mt);
}
