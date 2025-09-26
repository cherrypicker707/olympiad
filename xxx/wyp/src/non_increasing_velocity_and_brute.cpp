// Solution for the Subproblems I, II and III
// 65/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef long double ld;
typedef std::vector<ld> vld;

ll n;
ld d_car, v_car;
vld x, d, v;

void non_increasing_velocity();
void brute();
bool are_values_equal(ld left, ld right);

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    ll num, den;
    std::cin >> n >> d_car >> num >> den;
    v_car = (ld)num / (ld)den;

    x = vld(n);
    d = vld(n);
    v = vld(n);
    for(ll i = 0; i < n; i++)
    {
        std::cin >> x[i] >> d[i] >> num >> den;
        v[i] = (ld)num / (ld)den;
    }

    if(n <= 1000)
    {
        brute();
        return 0;
    }

    non_increasing_velocity();
    return 0;
}

void non_increasing_velocity()
{
    ll result = 1;
    for(ll i = 1; i < n; i++)
    {
        ld time = (x[i] - d[i]) / (v_car - v[i]);
        ld distance = (x[i] + v[i] * time) - d[i] - (x[i - 1] + v[i - 1] * time);
        result += (distance > d_car || are_values_equal(distance, d_car));
    }
    std::cout << result << '\n';
}

void brute()
{
    ld x_car = 0;
    ll result = 0;
    ll overtaken = 0;

    while(overtaken < n)
    {
        ld next_collision_time = (x[overtaken] - d[overtaken] - x_car) / (v_car - v[overtaken]);
        for(ll i = 0; i < n - 1; i++)
        {
            if(v[i] < v[i + 1] || are_values_equal(v[i], v[i + 1]))
                continue;

            ld collision_time = (x[i + 1] - d[i + 1] - x[i]) / (v[i] - v[i + 1]);
            next_collision_time = std::min(next_collision_time, collision_time);
        }

        std::cerr << next_collision_time << '\n';

        x_car += v_car * next_collision_time;
        for(ll i = 0; i < n; i++)
            x[i] += v[i] * next_collision_time;

        if(are_values_equal(x_car, x[overtaken] - d[overtaken]))
        {
            ld distance = (overtaken == 0 ? HUGE_VALL : x[overtaken] - d[overtaken] - x[overtaken - 1]);

            if(distance > d_car || are_values_equal(distance, d_car))
                result++;

            overtaken++;
        }

        for(ll i = 0; i < n - 1; i++)
            if(x[i] > x[i + 1] - d[i + 1] || are_values_equal(x[i], x[i + 1] - d[i + 1])) // !!!
                if(v[i] > v[i + 1] || are_values_equal(v[i], v[i + 1]))
                    v[i] = v[i + 1];
    }

    std::cout << result << '\n';
}

bool are_values_equal(ld left, ld right)
{
    const ld epsilon = 1e-5;
    if(std::abs(left - right) < epsilon)
        return true;
    return false;
}
