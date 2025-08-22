#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::vector<str> vstr;
typedef std::set<str> sstr;

void brute();
void generate(str base, sstr &derivatives);
ll moveLeft(char dir, ll k);
bool simplify(str &code);
void sort(str &code);
str alt(str code);

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    ll t;
    std::cin >> t;

    for(ll i = 0; i < t; i++)
        brute();
    return 0;
}

void brute()
{
    char c;
    std::cin >> c;

    if(c == 'K')
    {
        str code;
        std::cin >> code;

        sstr derivatives;
        generate(code, derivatives);

        ll n = derivatives.size();
        std::cout << n << '\n';

        for(str derivative : derivatives)
            std::cout << derivative << ' ';
        std::cout << '\n';

        return;
    }

    ll size;
    std::cin >> size;

    sstr derivatives;
    derivatives.insert("eee");

    for(ll i = 2; i <= size; i++)
    {
        sstr newDerivatives;
        for(str derivative : derivatives)
            generate(derivative, newDerivatives);
        derivatives = newDerivatives;
    }

    ll n = derivatives.size();
    std::cout << n << '\n';
    for(str derivative : derivatives)
        std::cout << derivative << ' ';
    std::cout << '\n';
}

void generate(str base, sstr &derivatives)
{
    ll n = base.size();

    for(ll i = 0; i < n; i++)
    {
        str currentDerivative = base;
        currentDerivative[i] = moveLeft(currentDerivative[i], 1);
        currentDerivative[(i + 1) % n] = moveLeft(currentDerivative[(i + 1) % n], 1);
        currentDerivative.insert((i + 1) % n, 1, 'e');

        while(!simplify(currentDerivative));

        str alternativeDerivative = alt(currentDerivative);

        sort(currentDerivative);
        sort(alternativeDerivative);

        if(alternativeDerivative < currentDerivative)
            currentDerivative = alternativeDerivative;

        derivatives.insert(currentDerivative);
    }
}

ll moveLeft(char dir, ll k)
{
    k %= 6;
    return 'a' + ((dir - 'a') + 6 - k) % 6;
}

bool simplify(str &code)
{
    ll n = code.size();
    for(ll i = 0; i < code.size(); i++)
    {
        if(code[i] != 'f')
            continue;

        ll dir = code[(i + 1) % n];
        ll k = 'f' - code[(i + n - 1) % n];
        code[(i + 1) % n] = moveLeft(dir, k);
        code.erase((i + n - 1) % n, 1);
        break;
    }

    for(ll i = 0; i < code.size(); i++)
    {
        if(code[i] != 'f')
            continue;

        code.erase(i, 1);
        break;
    }

    bool success = true;
    for(ll i = 0; i < code.size(); i++)
    {
        if(code[i] != 'f')
            continue;
        success = false;
    }
    return success;
}

void sort(str &code)
{
    ll n = code.size();
    vstr variant(n, code);

    for(ll i = 0; i < n; i++)
        for(ll j = 0; j < n; j++)
            variant[i][j] = code[(i + j) % n];

    std::sort(variant.begin(), variant.end());
    code = variant[0];
}

str alt(str code)
{
    std::reverse(code.begin(), code.end());
    return code;
}
