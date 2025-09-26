// Solution for All Subproblems
// 100/100 points

#include <bits/stdc++.h>

typedef long long ll;
typedef std::vector<ll> vll;
typedef std::set<ll> sll;
typedef long double ld;
typedef std::vector<ld> vld;

struct Vehicle
{
    ll i;
    ld x, d, v;
};
typedef std::list<Vehicle> lVehicle;
typedef std::list<Vehicle>::iterator lVehiclei;

struct Event
{
    bool collision;
    ld time;
    ll vehicle_i;
    lVehiclei vehicle;
};
typedef std::priority_queue<Event> pqEvent;

const ld epsilon = 1e-5;

ll n;
ld d_car, v_car;
vld x, d, v;

void priority_queue();
bool ltoe(ld left, ld right);
bool lt(ld left, ld right);
bool operator<(const Event &left, const Event &right);

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

    priority_queue();
}

void priority_queue()
{
    Vehicle car = {-1, 0.0, d_car, v_car};
    lVehicle truck;
    for(ll i = 0; i < n; i++)
        truck.push_back({i, x[i], d[i], v[i]});

    sll erased_trucks, overtaken_trucks;

    ld time = -1.0;

    pqEvent queue;
    for(auto curr = truck.begin(); curr != truck.end(); curr = std::next(curr))
    {
        queue.push({false, (curr->x - curr->d - car.x) / (car.v - curr->v), curr->i, curr});

        if(curr == truck.begin())
            continue;

        auto prev = std::prev(curr);
        if(ltoe(prev->v, curr->v))
            continue;

        queue.push({true, (curr->x - curr->d - prev->x) / (prev->v - curr->v), curr->i, curr});
    }

    ll result = 0;

    while(!queue.empty())
    {
        Event next_event = queue.top();
        queue.pop();

        if(erased_trucks.count(next_event.vehicle_i))
            continue;

        if(lt(next_event.time, time))
            continue;

        auto curr = next_event.vehicle;

        if(next_event.collision)
        {
            // std::cerr << "Event: " << next_event.collision << ' ' << next_event.time << '\n';

            auto prev = std::prev(curr);

            prev->x = curr->x;
            prev->d = prev->d + curr->d;
            prev->v = curr->v;

            erased_trucks.insert(curr->i);
            truck.erase(curr);

            if(prev != truck.begin())
            {
                auto prev_2 = std::prev(prev);
                if(!ltoe(prev_2->v, prev->v))
                    queue.push({true, (prev->x - prev->d - prev_2->x) / (prev_2->v - prev->v), prev->i, prev});
            }
            queue.push({false, (prev->x - prev->d - car.x) / (car.v - prev->v), prev->i, prev});

            time = next_event.time;
            continue;
        }

        if(overtaken_trucks.count(curr->i))
            continue;

        // std::cerr << "Event: " << next_event.collision << ' ' << next_event.time << '\n';

        if(curr == truck.begin())
        {
            result++;
            overtaken_trucks.insert(curr->i);
            time = next_event.time;
            continue;
        }

        auto prev = std::prev(curr);

        ld distance = (curr->x + curr->v * next_event.time) - curr->d - (prev->x + prev->v * next_event.time);
        if(ltoe(car.d, distance))
            result++;

        overtaken_trucks.insert(next_event.vehicle->i);

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

bool operator<(const Event &left, const Event &right)
{
    return left.time > right.time;
}
