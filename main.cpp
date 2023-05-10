#include <iostream>
#include <Windows.h>
#include <time.h>
#include <list>
#include <vector>

static const int X = 20, Y = 20; 
char map[X][Y];

class cell
{
public:
    static const char body = '0';
    static const char fruit = '&';
    int x, y;
    cell(int x, int y) : x(x), y(y)
    {
        map[x][y] = body;
    }
    void clear()
    {
        map[x][y] = ' ';
    }
};

enum direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void print()
{
    for(int i = 0; i < Y * 2 + 2; i++)
        std::cout << '#';
    std::cout << '\n';

    for(auto &y: map)
    {
        std::cout << "#";
        for(auto &item: y)
            std::cout << item << item;
        std::cout << "#\n";
    }

    for(int i = 0; i < Y * 2 + 2; i++)
        std::cout << '#';
    std::cout << '\n';
}

bool step(direction dir, std::list<cell> &list, int &score)
{
    int x = list.front().x;
    int y = list.front().y;
    bool is_fruit = 0;

    switch (dir)
    {
    case UP:
        if(x == 0 || (map[x - 1][y] == cell::body))
            return 0;
        is_fruit = map[x - 1][y] == cell::fruit;
        list.push_front(cell(x - 1, y));
        break;
    case DOWN:
        if(x == X - 1 || (map[x + 1][y] == cell::body))
            return 0;
        is_fruit = map[x + 1][y] == cell::fruit;
        list.push_front(cell(x + 1, y));
        break;
    case RIGHT:
        if(y == Y - 1 || (map[x][y + 1] == cell::body))
            return 0;
        is_fruit = map[x][y + 1] == cell::fruit;
        list.push_front(cell(x, y + 1));
        break;
    case LEFT:
        if(y == 0 || (map[x][y - 1] == cell::body))
            return 0;
        is_fruit = map[x][y - 1] == cell::fruit;
        list.push_front(cell(x, y - 1));
        break;
    }
    if(is_fruit)
    {
        score++;
        std::vector<char*> free_space;
        for(auto &i: map)
            for(auto &item: i)
                if(item == ' ')
                    free_space.push_back(&item);
        *free_space.at(std::rand() % free_space.size()) = cell::fruit;
    }
    else
    {
        list.back().clear();
        list.pop_back();
    }
    return 1;
}

int main()
{
    for(auto &y: map)
        for(auto &item: y)
            item = ' ';
    std::list<cell> cells;

    for(int i = 0; i < 4; i++)
        cells.push_front(cell(4, i));

    map[7][7] = cell::fruit;

    direction dir = RIGHT;
    int score = 0;
    for(bool playing = true; playing; playing = step(dir, cells, score))
    {
        print();
        if(GetKeyState(VK_UP) & 0x8000 && dir != DOWN)
            dir = UP;
        else if(GetKeyState(VK_DOWN) & 0x8000 && dir != UP)
            dir = DOWN;
        else if(GetKeyState(VK_RIGHT) & 0x8000 && dir != LEFT)
            dir = RIGHT;
        else if(GetKeyState(VK_LEFT) & 0x8000 && dir != RIGHT)
            dir = LEFT;
        Sleep(100);
        system("cls");
    }

    std::cout << "\n\nyou lose!!!\nyoure score: " << score << '\n';

    return 0;
}
