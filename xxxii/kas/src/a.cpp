// Simulated Annealing
// Used to obtain proper threshold values.

#include <bits/stdc++.h>
#include "../inc/s.h"

#define INITIAL_TEMPERATURE 25.0f
#define MINIMAL_TEMPERATURE 0.01f
#define COOLING_FACTOR 0.99f
#define MINIMAL_ENERGY 2200
#define STANDARD_DEVIATION 0.25f

std::random_device dev;
std::mt19937_64 rd(dev());
vfloat threshold;

void anneal();
bool check_ann(ll deltaEnergy, float temperature);

int main()
{
    init();
    anneal();

    ll energy = run();
    std::cout << "Final result: " << energy << '\n';
    for(ll i = 0; i < 25; i++)
        std::cout << threshold[i] << ' ';
    std::cout << '\n';

    return 0;
}

void anneal()
{
    threshold.resize(25);
    for(ll i = 0; i < 25; i++)
        std::cin >> threshold[i];

    float temperature = INITIAL_TEMPERATURE;
    ll energy = run();

    std::cout << "Initial energy: " << energy << '\n';

    while(energy < MINIMAL_ENERGY && temperature >= MINIMAL_TEMPERATURE)
    {
        vfloat old_threshold = threshold;
        vfloat new_threshold = threshold;

        for(ll i = 0; i < 25; i++)
            new_threshold[i] += std::normal_distribution<float>(0.0, STANDARD_DEVIATION)(rd);
        threshold = new_threshold;

        ll new_energy = run();

        if(check_ann(new_energy - energy, temperature))
        {
            energy = new_energy;
            std::cout << "New energy: " << new_energy << '\n';
        }
        else
        {
            std::cout << "Not accepted: " << new_energy << '\n';
            threshold = old_threshold;
        }

        temperature *= COOLING_FACTOR;
    }
}

bool check_ann(ll deltaEnergy, float temperature)
{
    if(deltaEnergy > 0.0)
        return true;

    float random_number;

    do
    {
        random_number = std::uniform_real_distribution<double>(0.0, 1.0)(rd);
    }while(random_number == 1.0);

    if(random_number < exp(deltaEnergy / temperature))
       return true;

    return false;
}
