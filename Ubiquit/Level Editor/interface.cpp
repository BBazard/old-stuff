#include <iostream>
#include <SFML/Graphics.hpp>

#include "constantes.hpp"
#include "interface.hpp"
#include "map.hpp"
#include "ressourcesManager.hpp"

Interface::Interface(class RessourcesManager &ressourcesManager)
{
    ressourcesManager.GetSprite(m_selectSprite, SELECTION);
    ressourcesManager.GetSprite(m_tileToolBox, TILE_TOOL_BOX);

    m_tileToolBox.SetPosition(TILE_WIDTH, LEVEL_HEIGHT*TILE_HEIGHT+TILE_HEIGHT/2-5);

    m_currentSprite = BLOC;

    m_modeSelection = WORLD;
}

void Interface::AssignTileSetMap()
{
    m_modeSelection = MAP;
}

void Interface::AssignTileSetWorld()
{
    m_modeSelection = WORLD;
}

void Interface::DisplayEnviron(sf::Sprite* tile, sf::RenderWindow &app, float currentRotation)
{
    app.Draw(m_tileToolBox);
    tile[m_currentSprite].SetRotation(currentRotation);
    tile[m_currentSprite].SetPosition(TILE_WIDTH+1+GetOffset(tile).x, LEVEL_HEIGHT*TILE_HEIGHT+TILE_HEIGHT/2+7+GetOffset(tile).y);
    app.Draw(tile[m_currentSprite]);
}

void Interface::SelectSprite(int X, int nbr)
{
    if(X > m_tileToolBox.GetPosition().x && X < m_tileToolBox.GetPosition().x+m_tileToolBox.GetSize().x)
    {
        m_currentSprite += nbr;

        if((m_modeSelection == MAP) && (m_currentSprite == TILE_NUMBER_MAP))
            m_currentSprite = BLOC;

        if((m_modeSelection == WORLD) && (m_currentSprite == TILE_NUMBER_WORLD))
            m_currentSprite = ONE;

        if((m_modeSelection == MAP) && (m_currentSprite == QUADRILLAGE_MAP))
            m_currentSprite = TILE_NUMBER_MAP-1;

        if((m_modeSelection == WORLD) && (m_currentSprite == QUADRILLAGE_WORLD))
            m_currentSprite = TILE_NUMBER_WORLD-1;
    }
}

int Interface::GetSelection()
{
    return m_currentSprite;
}

sf::Vector2i Interface::GetOffset(sf::Sprite* tile)
{
    sf::Vector2i offset;

    float angle = tile[m_currentSprite].GetRotation();

    if(angle == 90)
    {
        offset.x = 0;
        offset.y = 40;
    }

    else if(angle == 180)
    {
        offset.x = 40;
        offset.y = 40;
    }

    else if(angle == 270)
    {
        offset.x = 40;
        offset.y = 0;
    }

    else if(angle == 0)
    {
        offset.x = 0;
        offset.y = 0;
    }

    return offset;
}



