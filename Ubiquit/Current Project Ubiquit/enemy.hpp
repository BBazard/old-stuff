#ifndef CLASS_ENEMY
#define CLASS_ENEMY

#include <iostream>
#include <SFML/Graphics.hpp>

#include "imageManager.hpp"
#include "stats.hpp"

class Enemy
{
    public :

        Enemy(ImageManager *imageManager, int whichEnemy, int X, int Y);

        void Display(sf::RenderWindow &app);

        void Anime();

    private :

        sf::Sprite m_body;
        sf::IntRect m_maskCollide;
        StatsBar m_life;
        int m_type;
};


#endif
