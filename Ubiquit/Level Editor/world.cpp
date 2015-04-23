#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

#include "constantes.hpp"
#include "world.hpp"
#include "ressourcesManager.hpp"

World::World()
{
    EraseAll();
}

void World::Display(sf::Sprite* tile, sf::RenderWindow &app)
{
     for(int j = 0 ; j < LEVEL_HEIGHT ; j++)
        for(int i = 0 ; i < LEVEL_WIDTH ; i++)
        {
            int X = i%LEVEL_WIDTH;
            int Y = j%LEVEL_HEIGHT;

            tile[m_world[i][j].tile].SetRotation(m_world[i][j].rotate);
            tile[m_world[i][j].tile].SetPosition(X*TILE_WIDTH+GetOffset(tile[m_world[i][j].tile]).x, Y*TILE_HEIGHT+GetOffset(tile[m_world[i][j].tile]).y);
            app.Draw(tile[m_world[i][j].tile]);
        }
}

void World::EraseAll()
{
    for(int j = 0 ; j < LEVEL_HEIGHT ; j++)
    {
        for(int i = 0 ; i < LEVEL_WIDTH ; i++)
        {
            m_world[i][j].tile = QUADRILLAGE_WORLD;
            m_world[i][j].rotate = 0;
        }
    }
}

bool World::Erase(int X, int Y)
{
    if(m_world[X/TILE_WIDTH][Y/TILE_HEIGHT].tile != QUADRILLAGE_WORLD)
    {
        m_world[X/TILE_WIDTH][Y/TILE_HEIGHT].tile = QUADRILLAGE_WORLD;
        return true;
    }

    return false;
}

bool World::SetSquare(int tile, int X, int Y, int angle)
{
    if(m_world[X/TILE_WIDTH][Y/TILE_HEIGHT].tile == QUADRILLAGE_WORLD)
    {
        m_world[X/TILE_WIDTH][Y/TILE_HEIGHT].tile = tile;
        m_world[X/TILE_WIDTH][Y/TILE_HEIGHT].rotate = angle;
        return true;
    }

    else
    {
        m_world[X/TILE_WIDTH][Y/TILE_HEIGHT].tile = tile;
        m_world[X/TILE_WIDTH][Y/TILE_HEIGHT].rotate = angle;
        return false;
    }
}

bool World::SquareIsEmpty(int X, int Y)
{
    X /= TILE_WIDTH;
    Y /= TILE_HEIGHT;
        return SquareIsEmptyIndex(X, Y);
}

bool World::SquareIsEmptyIndex(int X, int Y)
{
    if(m_world[X][Y].tile == QUADRILLAGE_WORLD)
        return true;

    return false;
}

sf::Vector2i World::GetOffset(sf::Sprite sprite)
{
    sf::Vector2i offset;

    int angle = sprite.GetRotation();

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

void World::InitializeIDs()
{
    for(int j = 0 ; j < LEVEL_HEIGHT ; j++)
    {
        for(int i = 0 ; i < LEVEL_WIDTH ; i++)
        {
            if(!SquareIsEmpty(i*TILE_WIDTH, j*TILE_HEIGHT))
                m_world[i][j].ID = GetIDFromCoord(i*TILE_WIDTH, j*TILE_HEIGHT);

            else
                m_world[i][j].ID = -1;

            m_world[i][j].link[UP].isLinked = false;
            m_world[i][j].link[DOWN].isLinked = false;
            m_world[i][j].link[LEFT].isLinked = false;
            m_world[i][j].link[RIGHT].isLinked = false;
        }
    }

    for(int j = 0 ; j < LEVEL_HEIGHT ; j++)
    {
        for(int i = 0 ; i < LEVEL_WIDTH ; i++)
        {
            if(LinkUp(m_world[i][j]))
                m_world[i][j].link[UP].isLinked = true;

            if(LinkDown(m_world[i][j]))
                m_world[i][j].link[DOWN].isLinked = true;

            if(LinkLeft(m_world[i][j]))
                m_world[i][j].link[LEFT].isLinked = true;

            if(LinkRight(m_world[i][j]))
                m_world[i][j].link[RIGHT].isLinked = true;
        }
    }
}

bool World::LinkUp(TileWorld &tile)
{
    if(tile.tile == ONE && tile.rotate == 0)
        return true;

    if(tile.tile == TWO && (tile.rotate == 0 || tile.rotate == 180))
        return true;

    if(tile.tile == THREE && tile.rotate != 180)
        return true;

    if(tile.tile == TWO2 && (tile.rotate != 90 && tile.rotate != 180))
        return true;

    if(tile.tile == FOUR)
        return true;

    return false;
}

bool World::LinkDown(TileWorld &tile)
{
    if(tile.tile == ONE && tile.rotate == 180)
        return true;

    if(tile.tile == TWO && (tile.rotate == 0 || tile.rotate == 180))
        return true;

    if(tile.tile == THREE && tile.rotate != 0)
        return true;

    if(tile.tile == TWO2 && (tile.rotate != 0 && tile.rotate != 270))
        return true;

    if(tile.tile == FOUR)
        return true;

    return false;
}

bool World::LinkLeft(TileWorld &tile)
{
    if(tile.tile == ONE && tile.rotate == 90)
        return true;

    if(tile.tile == TWO && (tile.rotate == 90 || tile.rotate == 270))
        return true;

    if(tile.tile == THREE && tile.rotate != 270)
        return true;

    if(tile.tile == TWO2 && (tile.rotate != 180 && tile.rotate != 270))
        return true;

    if(tile.tile == FOUR)
        return true;

    return false;
}

bool World::LinkRight(TileWorld &tile)
{
    if(tile.tile == ONE && tile.rotate == 270)
        return true;

    if(tile.tile == TWO && (tile.rotate == 90 || tile.rotate == 270))
        return true;

    if(tile.tile == THREE && tile.rotate != 90)
        return true;

    if(tile.tile == TWO2 && (tile.rotate != 0 && tile.rotate != 90))
        return true;

    if(tile.tile == FOUR)
        return true;

    return false;
}

int World::GetIDFromCoord(int X, int Y)
{
    X /= TILE_WIDTH;
    Y /= TILE_HEIGHT;

    return GetIDFromIndex(X, Y);
}

int World::GetIDFromIndex(int X, int Y)
{
    int count = -1;

    for(int j = 0 ; j <= Y ; j++)
    {
        if(Y != j)
        {
            for(int i = 0 ; i < LEVEL_WIDTH; i++)
            {
                if(!SquareIsEmptyIndex(i, j))
                    count++;
            }
        }

        else
        {
            for(int i = 0 ; i <= X; i++)
            {
                if(!SquareIsEmptyIndex(i, j))
                    count++;
            }
        }
    }

    return count;
}

void World::Save()
{
    std::string const nomFichier("Datas/mainWorld.txt");
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

void World::PrintInFile(std::ofstream &file)
{
    for(int j = 0 ; j < LEVEL_HEIGHT ; j++)
    {
        for(int i = 0 ; i < LEVEL_WIDTH ; i++)
        {
            file << m_world[i][j].tile;
            file << " ";
            file << m_world[i][j].rotate;

                if(i != LEVEL_WIDTH-1)
                    file << " ";
        }

        if(j != LEVEL_HEIGHT-1)
            file <<  std::endl;
    }
}

void World::Load()
{
    std::string const nomFichier("Datas/mainWorld.txt");
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

void World::ReadInFile(std::ifstream &file)
{
    for(int j = 0 ; j < LEVEL_HEIGHT ; j++)
    {
        for(int i = 0 ; i < LEVEL_WIDTH ; i++)
        {
            file >> m_world[i][j].tile;
            file >> m_world[i][j].rotate;
        }
    }
}

int World::GetNumberOfSquare()
{
    int count = 0;
    for(int j = 0 ; j < LEVEL_HEIGHT ; j++)
    {
        for(int i = 0 ; i < LEVEL_WIDTH ; i++)
        {
            if(!SquareIsEmptyIndex(i, j))
                count++;
        }
    }

    return count;
}
