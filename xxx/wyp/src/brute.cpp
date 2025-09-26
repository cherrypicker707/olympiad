// Solution for the Subproblem III
// 35/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef long double ld;
typedef std::vector<ld> vld;

struct Vehicle
{
    ld x, d, v;
};
typedef std::list<Vehicle> lVehicle;
typedef std::list<Vehicle>::iterator lVehiclei;

struct Event
{
    bool collision;
    ld time;
    lVehiclei vehicle;
};

const ld epsilon = 1e-5;

ll n;
ld d_car, v_car;
vld x, d, v;

void brute();
bool ltoe(ld left, ld right);
bool lt(ld left, ld right);

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

    brute();
}

void brute()
{
    Vehicle car = {0.0, d_car, v_car};

    lVehicle truck;
    for(ll i = 0; i < n; i++)
        truck.push_back({x[i], d[i], v[i]});

    ld time = -1.0;
    auto overtaken = truck.begin();

    ll result = 0;

    while(overtaken != truck.end())
    {
        Event next_event = {false, (overtaken->x - overtaken->d - car.x) / (car.v - overtaken->v), overtaken};
        for(auto curr = std::next(truck.begin()); curr != truck.end(); curr = std::next(curr))
        {
            auto prev = std::prev(curr);
            if(ltoe(prev->v, curr->v))
                continue;

            Event collision = {true, (curr->x - curr->d - prev->x) / (prev->v - curr->v), curr};
            if(lt(collision.time, time) || ltoe(next_event.time, collision.time))
                continue;

            next_event = collision;
        }

        // std::cerr << "Event: " << next_event.collision << ' ' << next_event.time << '\n';

        if(next_event.collision)
        {
            auto curr = next_event.vehicle;
            auto prev = std::prev(curr);

            prev->x = curr->x;
            prev->d = prev->d + curr->d;
            prev->v = curr->v;

            if(overtaken == curr)
                overtaken = std::next(overtaken);
            truck.erase(curr);

            time = next_event.time;
            continue;
        }

        if(next_event.vehicle == truck.begin())
        {
            result++;
            overtaken = std::next(overtaken);
            time = next_event.time;
            continue;
        }

        auto curr = next_event.vehicle;
        auto prev = std::prev(curr);

        ld distance = (curr->x + curr->v * next_event.time) - curr->d - (prev->x + prev->v * next_event.time);
        if(ltoe(car.d, distance))
            result++;

        overtaken = std::next(overtaken);

        time = next_event.time;
    }

    std::cout << result << '\n';
}

bool ltoe(ld left, ld right)
{
    return (left - right) < epsilon;
}

bool lt(ld left, ld right)
{
    return (left - right) < -epsilon;
}
