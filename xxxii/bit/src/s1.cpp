// Solution for the Subproblem I
// 8/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<bool> vbool;
typedef std::vector<ll> vll;
typedef std::pair<ll, ll> pll;
typedef std::set<pll> spll;

ll n, m, k;
spll tree1, tree2;

bool check(vll &perm);
void s1();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n >> m >> k;

    for(ll i = 0; i < n - 1; i++)
    {
        ll u, v;
        std::cin >> u >> v;
        u--;
        v--;

        tree1.insert({std::min(u, v), std::max(u, v)});
    }

    for(ll i = 0; i < m - 1; i++)
    {
        ll u, v;
        std::cin >> u >> v;
        u--;
        v--;

        tree2.insert({std::min(u, v), std::max(u, v)});
    }

    s1();

    return 0;
}

void s1()
{
    ll answer = 0;
    vbool comb;

    comb.resize(m, false);
    std::fill(comb.end() - n, comb.end(), true);

    do
    {
        vll perm;
        for(ll i = 0; i < m; i++)
            if(comb[i])
                perm.push_back(i);

        do
        {
            if(check(perm))
                answer = (answer + 1) % k;
        } while(std::next_permutation(perm.begin(), perm.end()));
    } while(std::next_permutation(comb.begin(), comb.end()));

    std::cout << answer << '\n';
}

bool check(vll &perm)
{
    for(pll edge : tree1)
    {
        ll u = perm[edge.first];
        ll v = perm[edge.second];

        if(!tree2.count({std::min(u, v), std::max(u, v)}))
            return false;
    }

    return true;
}
