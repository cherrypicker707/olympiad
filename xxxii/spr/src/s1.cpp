// Solution for the Subproblems I and II
// 19/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;

ll n;
vll a, b;

bool check(ll comb);
void printcomb(ll comb);

void s1();

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n;

    a.resize(n);
    b.resize(n);

    for(ll i = 0; i < n; i++)
        std::cin >> a[i];

    for(ll i = 0; i < n; i++)
        std::cin >> b[i];

    s1();

    return 0;
}

void s1()
{
    ll combcount = 1 << n;

    for(ll comb = 0; comb < combcount; comb++)
    {
        if(check(comb))
        {
            printcomb(comb);
            return;
        }
    }
}

bool check(ll comb)
{
    ll asuma = 0, amina = LLONG_MAX, bsuma = 0, bmina = LLONG_MAX;
    ll asumb = 0, aminb = LLONG_MAX, bsumb = 0, bminb = LLONG_MAX;

    for(ll i = 0; i < n; i++)
    {
        if((comb & (1 << i)) == 0)
        {
            asuma += a[i];
            amina = std::min(amina, a[i]);
            asumb += b[i];
            aminb = std::min(aminb, b[i]);
            continue;
        }

        bsuma += a[i];
        bmina = std::min(bmina, a[i]);
        bsumb += b[i];
        bminb = std::min(bminb, b[i]);
    }

    if(amina == LLONG_MAX)
        amina = 0;

    if(bmina == LLONG_MAX)
        bmina = 0;

    if(aminb == LLONG_MAX)
        aminb = 0;

    if(bminb == LLONG_MAX)
        bminb = 0;

    if(asuma < bsuma - bmina)
        return false;

    if(bsumb < asumb - aminb)
        return false;

    return true;
}

void printcomb(ll comb)
{
    for(ll i = 0; i < n; i++)
    {
        if((comb & (1 << i)) == 0)
        {
            std::cout << 0 << ' ';
            continue;
        }

        std::cout << 1 << ' ';
    }

    std::cout << '\n';
}
