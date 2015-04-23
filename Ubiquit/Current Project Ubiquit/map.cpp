#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

#include "constante.hpp"
#include "map.hpp"
#include "imageManager.hpp"

Map::Map()
{}

void Map::Display(sf::Sprite* tile, sf::RenderWindow &app)
{
     for(int j = 0 ; j < LEVEL_HEIGHT ; j++)
        for(int i = 0 ; i < LEVEL_WIDTH ; i++)
        {
            int X = i%LEVEL_WIDTH;
            int Y = j%LEVEL_HEIGHT;

            if(m_map[i][j].tile != NOTHING_MAP)
            {
                tile[m_map[i][j].tile].SetRotation(m_map[i][j].rotate);
                tile[m_map[i][j].tile].SetPosition(X*TILE_WIDTH+GetOffset(tile[m_map[i][j].tile]).x+LEFT_OFFSET, Y*TILE_HEIGHT+GetOffset(tile[m_map[i][j].tile]).y+UP_OFFSET);
                app.Draw(tile[m_map[i][j].tile]);
            }
        }
}

void Map::ReadInFile(std::ifstream &file)
{
    for(int j = 0 ; j < LEVEL_HEIGHT ; j++)
    {
        for(int i = 0 ; i < LEVEL_WIDTH ; i++)
        {
            file >> m_map[i][j].tile;
            file >> m_map[i][j].rotate;
        }
    }
}

sf::Vector2i Map::GetOffset(sf::Sprite sprite)
{
    sf::Vector2i offset;

    float angle = sprite.GetRotation();

    if(angle == 90)
    {
        offset.x = 0;
        offset.y = TILE_HEIGHT;
    }

    else if(angle == 180)
    {
        offset.x = TILE_WIDTH;
        offset.y = TILE_HEIGHT;
    }

    else if(angle == 270)
    {
        offset.x = TILE_WIDTH;
        offset.y = 0;
    }

    else if(angle == 0)
    {
        offset.x = 0;
        offset.y = 0;
    }

    return offset;
}
/*
void Map::SetID(int X, int Y)
{
    m_ID = (X/TILE_WIDTH)+(Y/TILE_HEIGHT)*LEVEL_WIDTH;
}
*/
bool Map::TileCrossable(int X, int Y)
{
    if(m_map[X/TILE_WIDTH][Y/TILE_HEIGHT].tile == BLOC)
        return false;

    if(m_map[X/TILE_WIDTH][Y/TILE_HEIGHT].tile == QUADRILLAGE_MAP)
        return true;

    return false;
}

