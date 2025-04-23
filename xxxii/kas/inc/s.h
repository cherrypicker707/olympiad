// Functions Used in the Final Solution
// Used to obtain the threshold values with 'src/a.cpp' file.

#include <bits/stdc++.h>
#include "kaslib.h"

#define MAXIMAL_CONSIDERED_PRIME 100'000LL

typedef long long ll;
typedef std::vector<bool> vbool;
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;
typedef std::vector<float> vfloat;

extern vfloat threshold;

ll n, group_count;
vll group_product;
vvll group;

void init();
ll run();
bool check(ll discovered_part, ll group_index, bool second_part);
ll get_second_part(ll discovered_part, ll group_index);

void init()
{
    n = DajN();

    vbool sieve_of_eratosthenes(MAXIMAL_CONSIDERED_PRIME + 1LL, true);

    sieve_of_eratosthenes[0] = false;
    sieve_of_eratosthenes[1] = false;

    for(ll i = 2; i <= MAXIMAL_CONSIDERED_PRIME; i++)
        for(ll j = 2 * i; j <= MAXIMAL_CONSIDERED_PRIME; j += i)
            sieve_of_eratosthenes[j] = false;

    group_product.push_back(1);
    group.push_back({});

    for(ll i = 0; i <= MAXIMAL_CONSIDERED_PRIME; i++)
    {
        if(sieve_of_eratosthenes[i] == false)
            continue;

        if(i <= n / group_product.back())
        {
            group_product.back() *= i;
            group.back().push_back(i);
            continue;
        }

        group_product.push_back(i);
        group.push_back({i});
    }

    group_count = group.size();
}

ll run()
{
    OdNowa();

    while(!GraZakonczona())
    {
        ll discovered_part = 1;
        bool number_succesfully_guessed = false;

        for(ll i = 0; i < group_count; i++)
        {
            discovered_part *= Pytaj(group_product[i]);
            if(GraZakonczona() || !check(discovered_part, i, false))
                break;

            discovered_part *= get_second_part(discovered_part, i);
            if(GraZakonczona() || !check(discovered_part, i, true))
                break;

            if(discovered_part >= n / group[i].back()) // !!!
            {
                Odpowiedz(discovered_part);
                break;
            }
        }

        if(!GraZakonczona() && !number_succesfully_guessed)
            Szturchnij();
    }

    return Wygrane();
}

bool check(ll discovered_part, ll group_index, bool second_part)
{
    if(!second_part)
    {
        if(group_index < 5 && discovered_part < exp(threshold[group_index]))
            return false;

        return true;
    }

    if(group_index < 10 && discovered_part < exp(threshold[5 + group_index]))
        return false;

    switch(group_index)
    {
        case 15:
            if(discovered_part < exp(threshold[15]))
                return false;
            break;
        case 40:
            if(discovered_part < exp(threshold[16]))
                return false;
            break;
        case 100:
            if(discovered_part < exp(threshold[17]))
                return false;
            break;
        case 300:
            if(discovered_part < exp(threshold[18]))
                return false;
            break;
        case 700:
            if(discovered_part < exp(threshold[19]))
                return false;
            break;
        case 1700:
            if(discovered_part < exp(threshold[20]))
                return false;
            break;
        case 4200:
            if(discovered_part < exp(threshold[21]))
                return false;
            break;
        case 10000:
            if(discovered_part < exp(threshold[22]))
                return false;
            break;
        case 25000:
            if(discovered_part < exp(threshold[23]))
                return false;
            break;
        case 50000:
            if(discovered_part < exp(threshold[24]))
                return false;
            break;
    }

    return true;
}

ll get_second_part(ll discovered_part, ll group_index)
{
    ll second_part = 1;

    for(ll prime : group[group_index])
    {
        if(discovered_part % prime)
            continue;

        ll power = 1;
        while(power <= n / prime)
            power *= prime;

        second_part *= (Pytaj(power) / prime);
    }

    return second_part;
}
