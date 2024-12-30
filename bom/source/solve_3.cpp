// Solution for the Subproblem I and II
// 30/100 points

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
pairint_t initial_field, final_field;

vecvecint_t distance_to_finish;
vecvecchar_t direction_to_finish;

bool_t field_is_valid(pairint_t &field);
void set_distance_and_direction(pairint_t &destination_field, vecvecint_t &distance, vecvecchar_t &direction);
std::string get_path();
void detonate_bomb(pairint_t &bombing_field);

int32_t main()
{
    bool_t bricks = false;
    pairint_t bombing_field;

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
            if (map[row][column] == '#')
                bricks = true;
        }
    }

    bombing_field = initial_field;

    distance_to_finish.resize(map_size, vecint_t(map_size, LLONG_MAX));
    direction_to_finish.resize(map_size, vecchar_t(map_size, '.'));

    if (bricks)
    {
        vecvecchar_t original_map = map;
        int_t shortest_distance = LLONG_MAX;

        for (int_t row = 0; row < map_size; row++)
        {
            for (int_t column = 0; column < map_size; column++)
            {
                pairint_t current_field = {row, column};
                if (!field_is_valid(current_field))
                    continue;

                detonate_bomb(current_field);
                set_distance_and_direction(final_field, distance_to_finish, direction_to_finish);

                int_t current_distance = distance_to_finish[initial_field.first][initial_field.second];

                if (current_distance < shortest_distance)
                {
                    shortest_distance = current_distance;
                    bombing_field = {row, column};
                }

                map = original_map;
            }
        }

        detonate_bomb(bombing_field);
    }

    set_distance_and_direction(final_field, distance_to_finish, direction_to_finish);

    std::string path = get_path();

    if (path == "")
    {
        std::cout << "NIE\n";
        return 0;
    }

    std::cout << path.size() << '\n';
    std::cout << (bombing_field.first + 1) << ' ' << (bombing_field.second + 1) << '\n';
    std::cout << path << '\n';

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

void set_distance_and_direction(pairint_t &destination_field, vecvecint_t &distance, vecvecchar_t &direction)
{
    assert(field_is_valid(destination_field));
    assert(distance.size() == map_size);
    assert(distance[0].size() == map_size);
    assert(direction.size() == map_size);
    assert(direction[0].size() == map_size);

    distance[destination_field.first][destination_field.second] = 0;
    direction[destination_field.first][destination_field.second] = '.';

    vecvecbool_t visited(map_size, vecbool_t(map_size, false));
    quepairint_t to_be_visited;

    to_be_visited.push(destination_field);

    while (!to_be_visited.empty())
    {
        pairint_t current_field = to_be_visited.front();
        to_be_visited.pop();

        if (visited[current_field.first][current_field.second])
            continue;

        visited[current_field.first][current_field.second] = true;

        if (map[current_field.first][current_field.second] == '#')
            continue;

        pairint_t left_field = {current_field.first, current_field.second - 1};
        if (field_is_valid(left_field) && !visited[left_field.first][left_field.second])
        {
            distance[left_field.first][left_field.second] = distance[current_field.first][current_field.second] + 1;
            direction[left_field.first][left_field.second] = 'P';
            to_be_visited.push(left_field);
        }

        pairint_t right_field = {current_field.first, current_field.second + 1};
        if (field_is_valid(right_field) && !visited[right_field.first][right_field.second])
        {
            distance[right_field.first][right_field.second] = distance[current_field.first][current_field.second] + 1;
            direction[right_field.first][right_field.second] = 'L';
            to_be_visited.push(right_field);
        }

        pairint_t top_field = {current_field.first - 1, current_field.second};
        if (field_is_valid(top_field) && !visited[top_field.first][top_field.second])
        {
            distance[top_field.first][top_field.second] = distance[current_field.first][current_field.second] + 1;
            direction[top_field.first][top_field.second] = 'D';
            to_be_visited.push(top_field);
        }

        pairint_t bottom_field = {current_field.first + 1, current_field.second};
        if (field_is_valid(bottom_field) && !visited[bottom_field.first][bottom_field.second])
        {
            distance[bottom_field.first][bottom_field.second] = distance[current_field.first][current_field.second] + 1;
            direction[bottom_field.first][bottom_field.second] = 'G';
            to_be_visited.push(bottom_field);
        }
    }
}

std::string get_path()
{
    int_t distance = distance_to_finish[initial_field.first][initial_field.second];

    if (distance == LLONG_MAX)
        return "";

    std::string path;
    path.reserve(distance);

    pairint_t current_field = initial_field;
    char_t current_direction = direction_to_finish[current_field.first][current_field.second];
    while (current_direction != '.')
    {
        path.push_back(current_direction);

        switch (current_direction)
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

        current_direction = direction_to_finish[current_field.first][current_field.second];
    }

    return path;
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
