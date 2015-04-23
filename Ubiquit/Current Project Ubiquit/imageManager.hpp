#ifndef CLASS_IMAGES_MANAGER
#define CLASS_IMAGES_MANAGER

#include <iostream>
#include <string>
#include "constante.hpp"

class ImageManager
{
    public :

        ImageManager();

        void GetSpriteTiles(sf::Sprite &sprite, int tile, int modeSelection);

        void GetSpriteEnemy(sf::Sprite &sprite, int whichEnemy);

    private :

        void AbstractLoadFromFile(sf::Image &image, std::string name, bool transparency = true, sf::Color color = sf::Color(0, 250, 250));

    private :

        sf::Image m_tilsetMap;
        sf::Image m_tilsetWorld;

        sf::Image m_enemy1;
};


#endif





