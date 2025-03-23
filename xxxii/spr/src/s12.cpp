// Solution for the Subproblems I, II and III
// 59/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::vector<bool> vbool;

ll n;
vll a, b;

bool check(ll comb);
void printcomb(ll comb);

void s1();
void s2();

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

    if(n <= 20)
    {
        s1();
        return 0;
    }

    s2();
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

void s2()
{
    vbool owner(n, false);
    vll order(n);
    for(ll i = 0; i < n; i++)
        order[i] = i;
    std::sort(order.begin(), order.end(), [&](ll left, ll right){return a[left] > a[right];});

    ll asum = 0, bsum = 0;
    for(ll i = 0; i < n; i++)
    {
        if(asum < bsum)
        {
            asum += a[order[i]];
            continue;
        }

        bsum += b[order[i]];
        owner[order[i]] = true;
    }

    for(ll i = 0; i < n; i++)
        std::cout << owner[i]<< ' ';
    std::cout << '\n';
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
