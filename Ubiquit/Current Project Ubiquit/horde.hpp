#ifndef CLASS_HORDE
#define CLASS_HORDE

#include <iostream>
#include "constante.hpp"
#include "enemy.hpp"

class Horde
{
    public :

        Horde(ImageManager *imageManager);

        void Display(sf::RenderWindow &app);

        void Anime();

    private :

        std::vector <class Enemy> m_horde;
};


#endif





