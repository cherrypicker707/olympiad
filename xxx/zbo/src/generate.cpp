// Program for Generating Random Test Data

#include <bits/stdc++.h>

#define RANDOM(x,y) std::uniform_int_distribution<ll>(x, y - 1)(mersenne_twister)

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;
typedef std::vector<vpll> vvpll;
typedef std::set<ll> sll;

std::random_device device;
std::mt19937_64 mersenne_twister(device());

void print_random_tree(ll n, ll max_c);
void print_random_path(ll n, ll max_c);
ll get_random_element(const sll &set);

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    ll n = std::atoll(argv[1]);
    ll k = std::atoll(argv[2]);
    ll max_c = std::atoll(argv[3]);
    ll mode = std::atoll(argv[4]);

    std::cout << n << ' ' << k << '\n';

    if(mode == 0)
        print_random_tree(n, max_c);
    else
        print_random_path(n, max_c);

    sll locations;
    for(ll i = 1; i < n; i++)
        locations.insert(i);

    for(ll i = 0; i < k; i++)
    {
        ll castle = get_random_element(locations);
        locations.erase(castle);
        std::cout << (castle + 1) << '\n';
    }
}

void print_random_tree(ll n, ll max_c)
{
    vll prufer_code(n - 2);
    for(ll i = 0; i < n - 2; i++)
        prufer_code[i] = RANDOM(0, n);

    vll degree(n, 1);
    for(ll i = 0; i < n - 2; i++)
        degree[prufer_code[i]]++;

    vpll edge;
    ll pointer = 0, leaf = 0;
    for(ll i = 0; i < n - 2; i++)
    {
        while(degree[leaf] != 1 || leaf > pointer)
            leaf = ++pointer;

        degree[leaf]--;
        degree[prufer_code[i]]--;
        edge.push_back({leaf, prufer_code[i]});
        leaf = prufer_code[i];
    }

    for(ll i = 0; i < n - 1; i++)
    {
        if(degree[i] == 1)
        {
            degree[i]--;
            degree[n - 1]--;
            edge.push_back({i, n - 1});

            break;
        }
    }

    for(ll i = 0; i < n - 1; i++)
        if(RANDOM(0, 2))
            std::swap(edge[i].first, edge[i].second);
    std::shuffle(edge.begin(), edge.end(), mersenne_twister);

    for(ll i = 0; i < n - 1; i++)
        std::cout << (edge[i].first + 1) << ' ' << (edge[i].second + 1) << ' ' << RANDOM(1, max_c + 1) << '\n';
}

void print_random_path(ll n, ll max_c)
{
    vpll edge(n - 1);
    for(ll i = 0; i < n - 1; i++)
        edge[i] = {i, i + 1};

    for(ll i = 0; i < n - 1; i++)
        if(RANDOM(0, 2))
            std::swap(edge[i].first, edge[i].second);
    std::shuffle(edge.begin(), edge.end(), mersenne_twister);

    for(ll i = 0; i < n - 1; i++)
        std::cout << (edge[i].first + 1) << ' ' << (edge[i].second + 1) << ' ' << RANDOM(1, max_c + 1) << '\n';
}

ll get_random_element(const sll &set)
{
    auto it = set.begin();
    ll size = set.size();
    ll i = RANDOM(0, size);
    std::advance(it, i);
    return *it;
}
