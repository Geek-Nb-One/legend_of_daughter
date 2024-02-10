#include "map.hpp"
#include "constant.hpp"

#include <iostream>
#include <fstream>

Map::Map(SDL_Renderer *renderer) : spriteSheet{SpriteSheet(renderer, "graphics/zeo254-completed-commission.png", 128, 128, 16, 16)}
{
    std::ifstream file("maps/forest.txt");


    std::string str;
    for (int y = 0; y < 54; y++){
        for (int x = 0; x <96;x++){
            file >> str;
            int index = std::stoi(str);
            spriteIndex[x][y] = index;
        }
    }

}

void Map::render(SDL_Renderer *renderer, const SDL_Rect& view)
{
    int indexX = view.x / 16;
    int indexY = view.y / 16;

    int offsetX = -view.x % 16;
    int offsetY = -view.y % 16;

    int x = 0;

    while (x * 16 + offsetX < view.w)
    {
        int y = 0;
        while (y * 16 + offsetY < view.h)
        {
            int index = spriteIndex[indexX + x][indexY + y];
            spriteSheet.renderCopy(renderer, index % 8, index / 8, x * 16 + offsetX, y * 16 + offsetY);
            y++;
        }
        x++;
    }
}

int Map::getWidth() const
{
    return 96 * 16;
}

int Map::getHeight() const
{
    return 54* 16;
}
