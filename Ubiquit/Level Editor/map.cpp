#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

#include "constantes.hpp"
#include "map.hpp"
#include "ressourcesManager.hpp"

Map::Map()
{
    EraseAll();
}

void Map::Display(sf::Sprite* tile, sf::RenderWindow &app)
{
     for(int j = 0 ; j < LEVEL_HEIGHT ; j++)
        for(int i = 0 ; i < LEVEL_WIDTH ; i++)
        {
            int X = i%LEVEL_WIDTH;
            int Y = j%LEVEL_HEIGHT;

            tile[m_map[i][j].tile].SetRotation(m_map[i][j].rotate);
            tile[m_map[i][j].tile].SetPosition(X*TILE_WIDTH+GetOffset(tile[m_map[i][j].tile]).x, Y*TILE_HEIGHT+GetOffset(tile[m_map[i][j].tile]).y);
            app.Draw(tile[m_map[i][j].tile]);
        }
}

void Map::SetSquare(int tile, int X, int Y, float angle)
{
    m_map[X/TILE_WIDTH][Y/TILE_HEIGHT].tile = tile;
    m_map[X/TILE_WIDTH][Y/TILE_HEIGHT].rotate = angle;
}

void Map::Save()
{
    std::string const nomFichier("Datas/mainMap.txt");
    std::ofstream file(nomFichier.c_str());

    if(!file)
    {
        std::cerr << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

    else
    {
        PrintInFile(file);
    }
}

void Map::PrintInFile(std::ofstream &file)
{
    for(int j = 0 ; j < LEVEL_HEIGHT ; j++)
    {
        for(int i = 0 ; i < LEVEL_WIDTH ; i++)
        {
            file << m_map[i][j].tile;
            file << " ";
            file << m_map[i][j].rotate;

                if(i != LEVEL_WIDTH-1)
                    file << " ";
        }

        if(j != LEVEL_HEIGHT-1)
            file <<  std::endl;
    }
}

void Map::Load()
{
    std::string const nomFichier("Datas/mainMap.txt");
    std::ifstream file(nomFichier.c_str());

    if(!file)
    {
        std::cerr << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

    else
    {
        ReadInFile(file);
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


void Map::EraseAll()
{
    for(int j = 0 ; j < LEVEL_HEIGHT ; j++)
    {
        for(int i = 0 ; i < LEVEL_WIDTH ; i++)
        {
            m_map[i][j].tile = QUADRILLAGE_MAP;
            m_map[i][j].rotate = 0;
        }
    }
}

void Map::Erase(int X, int Y)
{
    m_map[X/TILE_WIDTH][Y/TILE_HEIGHT].tile = QUADRILLAGE_MAP;
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

/*void Map::SetID(int X, int Y)
{
    m_ID = (X/TILE_WIDTH)+(Y/TILE_HEIGHT)*LEVEL_WIDTH;
}*/
