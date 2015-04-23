#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

#include "level.hpp"

Level::Level(ImageManager *imageManager) : m_world(), m_mapModel()
{
       for(int i = 0 ; i < TILE_NUMBER_MAP ; i++)
            imageManager->GetSpriteTiles(m_tileMap[i], i, MAP);

        for(int i = 0 ; i < TILE_NUMBER_WORLD ; i++)
            imageManager->GetSpriteTiles(m_tileWorld[i], i, WORLD);

    m_map.clear();

    Load();

    m_currentMap = m_world.GetIDFromIndex(m_indexCurrentMap.x, m_indexCurrentMap.y);
}

void Level::DisplayTiles(sf::RenderWindow &app)
{
    m_map[m_currentMap].Display(m_tileMap, app);
}

void Level::Load()
{
    std::string const nomFichier("Datas/mainLevel.txt");
    std::ifstream file(nomFichier.c_str());

    if(!file)
    {
        std::cerr << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

    else
    {
        m_world.ReadInFile(file);

        m_world.InitializeIDs();

            for(int i = 0 ; i < m_world.GetNumberOfSquare() ; i++)
                m_map.push_back(m_mapModel);

            for(unsigned int i = 0 ; i < m_map.size() ; i++)
                m_map[i].ReadInFile(file);

        file >> m_indexCurrentMap.x;
        file >> m_indexCurrentMap.y;
    }
}

bool Level::TileCrossable(int X, int Y)
{
    Y -= UP_OFFSET;
    X -= LEFT_OFFSET;

    if(X < 0 || X/TILE_WIDTH >= LEVEL_WIDTH)
        return true;

    if(Y < 0 || Y/TILE_HEIGHT >= LEVEL_HEIGHT)
        return true;

    if(m_map[m_currentMap].TileCrossable(X, Y))
        return true;

    return false;
}

bool Level::TileCrossable(sf::Vector2f pos)
{
    int X, Y;

    X = pos.x;
    Y = pos.y;

        return TileCrossable(X, Y);
}

int Level::ChangeMapDirection(int X, int Y)
{
    if(X < LEFT_OFFSET)
        return LEFT;

    if((X-LEFT_OFFSET)/TILE_WIDTH >= LEVEL_WIDTH)
        return RIGHT;

    if(Y < UP_OFFSET)
        return UP;

    if((Y-UP_OFFSET)/TILE_HEIGHT >= LEVEL_HEIGHT)
        return DOWN;

    return -1;
}

int Level::ChangeMapDirection(sf::Vector2f pos)
{
    int X = pos.x;
    int Y = pos.y;

    return ChangeMapDirection(X, Y);
}

sf::Vector2i Level::GetOffset(sf::Sprite sprite)
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

void Level::ChangeMap(int direction)
{
    if(direction == UP && !m_world.SquareIsEmptyIndex(m_indexCurrentMap.x, m_indexCurrentMap.y-1))
        m_indexCurrentMap.y--;

    else if(direction == DOWN && !m_world.SquareIsEmptyIndex(m_indexCurrentMap.x, m_indexCurrentMap.y+1))
        m_indexCurrentMap.y++;

    else if(direction == RIGHT && !m_world.SquareIsEmptyIndex(m_indexCurrentMap.x+1, m_indexCurrentMap.y))
        m_indexCurrentMap.x++;

    else if(direction == LEFT && !m_world.SquareIsEmptyIndex(m_indexCurrentMap.x-1, m_indexCurrentMap.y))
        m_indexCurrentMap.x--;

    else return;

    m_currentMap = m_world.GetIDFromIndex(m_indexCurrentMap.x, m_indexCurrentMap.y);
}
