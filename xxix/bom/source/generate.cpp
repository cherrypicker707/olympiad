// Random Test Data Generator

#include <bits/stdc++.h>

#define MAP_SIZE 25
#define BRICK

typedef bool bool_t;
typedef std::vector<bool_t> vecbool_t;
typedef std::vector<vecbool_t> vecvecbool_t;

typedef char char_t;
typedef std::vector<char_t> vecchar_t;
typedef std::vector<vecchar_t> vecvecchar_t;

typedef int long long int_t;
typedef std::vector<int_t> vecint_t;
typedef std::vector<vecint_t> vecvecint_t;

typedef std::pair<int_t, int_t> pairint_t;
typedef std::queue<pairint_t> quepairint_t;

int32_t main(int32_t argument_count, char_t **argument)
{
    assert(argument_count >= 2);

    int_t seed = atoi(argument[1]);
    pairint_t initial_field, final_field;

    std::cout << MAP_SIZE << '\n';

    std::mt19937_64 mersenne_twister(seed);
#define RANDOM(X, Y) std::uniform_int_distribution<int_t>(X, Y)(mersenne_twister);

    initial_field.first = RANDOM(0, MAP_SIZE - 1);
    initial_field.second = RANDOM(0, MAP_SIZE - 1);
    do
    {
        final_field.first = RANDOM(0, MAP_SIZE - 1);
        final_field.second = RANDOM(0, MAP_SIZE - 1);
    } while (final_field == initial_field);

    for (int_t row = 0; row < MAP_SIZE; row++)
    {
        for (int_t column = 0; column < MAP_SIZE; column++)
        {
            if (row == initial_field.first && column == initial_field.second)
            {
                std::cout << 'P';
                continue;
            }

            if (row == final_field.first && column == final_field.second)
            {
                std::cout << 'K';
                continue;
            }

            int_t empty_field = RANDOM(0, 1);
            if (empty_field)
            {
                std::cout << '.';
                continue;
            }

#ifdef BRICK
            int_t brick = RANDOM(0, 2);
            if (brick)
            {
                std::cout << '#';
                continue;
            }
#endif

            std::cout << 'X';
        }

        std::cout << '\n';
    }
#undef RANDOM
}
