#ifndef CLASS_RESSOURCES_MANAGER
#define CLASS_RESSOURCES_MANAGER

#include <iostream>
#include <string>
#include "levelEditor.hpp"
#include "constantes.hpp"

class RessourcesManager
{
    public :

        RessourcesManager()
        {
            AbstractLoadFromFile(m_tilsetMap, "Datas/tilesetMap.bmp");
            AbstractLoadFromFile(m_tilsetWorld, "Datas/tilesetWorld.bmp");
            AbstractLoadFromFile(m_imageSelect, "Datas/select.bmp");
            AbstractLoadFromFile(m_tileToolBox, "Datas/tileToolBox.bmp");
        }

        void GetSprite(sf::Sprite &sprite, int tile, int modeSelection)
        {
            if(modeSelection == MAP)
            {
                sprite.SetImage(m_tilsetMap);
                sprite.SetSubRect(sf::IntRect(TILE_WIDTH*tile, 0, TILE_WIDTH*(tile+1), TILE_HEIGHT));
            }

            else if(modeSelection == WORLD)
            {
                sprite.SetImage(m_tilsetWorld);
                sprite.SetSubRect(sf::IntRect(TILE_WIDTH*tile, 0, TILE_WIDTH*(tile+1), TILE_HEIGHT));
            }

            else
                std::cerr << "erreur fonction RessourcesManager.GetSprite appelée avec modeSelection != MAP et modeSelection !=  WORLD" << std::endl;
        }

        void GetSprite(sf::Sprite &sprite, int tile)
        {
            if(tile == SELECTION)
                sprite.SetImage(m_imageSelect);

            else if(tile == TILE_TOOL_BOX)
                sprite.SetImage(m_tileToolBox);

            else
                std::cerr << "erreur fonction RessourcesManager.GetSprite appelée avec tile != SELECTION et tile !=  TILE_TOOL_BOX" << std::endl;
        }

    private :

        void AbstractLoadFromFile(sf::Image &image, std::string name, bool transparency = true, sf::Color color = sf::Color(0, 250, 250))
        {
            if (!image.LoadFromFile(name))
                std::cerr << "Impossible d'ouvrir le fichier " << name << " !" << std::endl;

            if(transparency)
            {
                image.SetSmooth(false);
                image.CreateMaskFromColor(color);
            }
        }

    private :

        sf::Image m_imageSelect;

        sf::Image m_tilsetMap;
        sf::Image m_tilsetWorld;

        sf::Image m_tileToolBox;
};


#endif





