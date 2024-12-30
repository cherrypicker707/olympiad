#include <bits/stdc++.h>

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

int_t map_size;
vecvecchar_t map;

bool_t field_is_valid(pairint_t &field);
void detonate_bomb(pairint_t &bombing_field);

int32_t main()
{
    int_t supposed_distance;
    pairint_t initial_field, final_field, bombing_field, current_field;
    std::string line, path;

    std::cin >> map_size;
    map.resize(map_size, vecchar_t(map_size));

    for (int_t row = 0; row < map_size; row++)
    {
        for (int_t column = 0; column < map_size; column++)
        {
            std::cin >> map[row][column];

            if (map[row][column] == 'P')
                initial_field = {row, column};
            if (map[row][column] == 'K')
                final_field = {row, column};
        }
    }

    std::cin >> line;
    if (line == "NIE")
        return 0;
    supposed_distance = std::stoi(line);

    std::cin >> bombing_field.first >> bombing_field.second;
    bombing_field.first--;
    bombing_field.second--;

    std::cin >> path;

    if (!field_is_valid(bombing_field))
        return 1;
    detonate_bomb(bombing_field);

    if (supposed_distance != path.size())
        return 2;

    current_field = initial_field;
    for (char direction : path)
    {
        if (!field_is_valid(current_field) || map[current_field.first][current_field.second] == '#')
            return 3;

        switch (direction)
        {
        case 'L':
            current_field.second--;
            break;
        case 'P':
            current_field.second++;
            break;
        case 'G':
            current_field.first--;
            break;
        case 'D':
            current_field.first++;
            break;
        }
    }

    if (current_field != final_field)
        return 4;

    return 0;
}

bool_t field_is_valid(pairint_t &field)
{
    if (field.first < 0)
        return false;
    if (field.first >= map_size)
        return false;
    if (field.second < 0)
        return false;
    if (field.second >= map_size)
        return false;
    if (map[field.first][field.second] == 'X')
        return false;

    return true;
}

void detonate_bomb(pairint_t &bombing_field)
{
    pairint_t current_field;

    current_field = bombing_field;
    while (field_is_valid(current_field))
    {
        if (map[current_field.first][current_field.second] == '#')
            map[current_field.first][current_field.second] = '.';
        current_field.second--;
    }

    current_field = bombing_field;
    while (field_is_valid(current_field))
    {
        if (map[current_field.first][current_field.second] == '#')
            map[current_field.first][current_field.second] = '.';
        current_field.second++;
    }

    current_field = bombing_field;
    while (field_is_valid(current_field))
    {
        if (map[current_field.first][current_field.second] == '#')
            map[current_field.first][current_field.second] = '.';
        current_field.first--;
    }

    current_field = bombing_field;
    while (field_is_valid(current_field))
    {
        if (map[current_field.first][current_field.second] == '#')
            map[current_field.first][current_field.second] = '.';
        current_field.first++;
    }
}
