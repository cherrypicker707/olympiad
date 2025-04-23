#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::set<ll> sll;

std::mt19937_64 mt;

ll getrannum(ll min, ll max);
template <typename T> T getranel(std::multiset<T> &multiset);
void maketree(ll n);

int main(int argc, char **argv)
{
    assert(argc == 5);
    ll n = atoi(argv[1]);
    ll m = atoi(argv[2]);
    ll k = atoi(argv[3]);
    ll seed = atoi(argv[4]);
    assert(n <= m);

    mt.seed(seed);

    std::cout << n << ' ' << m << ' ' << k << '\n';

    maketree(n);
    maketree(m);

    return 0;
}

ll getrannum(ll min, ll max)
{
    return std::uniform_int_distribution<ll>(min, max)(mt);
}

template <typename T> T getranel(std::set<T> &multiset)
{
    auto it = multiset.begin();
    std::advance(it, getrannum(0, multiset.size() - 1));
    return *it;
}

void maketree(ll n)
{
    vll deg(n, 0);
    sll verts, places;

    for(ll i = 0; i < n; i++)
        verts.insert(i);

    ll root = getrannum(0, n - 1);
    verts.erase(root);
    places.insert(root);

    while(!verts.empty())
    {
        ll u = getranel(verts);
        ll v = getranel(places);

        verts.erase(u);
        places.insert(u);

        deg[u]++;
        deg[v]++;

        if(deg[v] == 3)
            places.erase(v);

        std::cout << (u + 1) << ' ' << (v + 1) << '\n';
    }
}
