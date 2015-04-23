#include "horde.hpp"

Horde::Horde(ImageManager *imageManager)
{
    m_horde.clear();

    m_horde.push_back(Enemy(imageManager, ENEMY1, 50, 430));
}

void Horde::Display(sf::RenderWindow &app)
{
    for(unsigned int i = 0 ; i < m_horde.size() ; i++)
        m_horde[i].Display(app);
}

void Horde::Anime()
{
    for(unsigned int i = 0 ; i < m_horde.size() ; i++)
        m_horde[i].Anime();
}
