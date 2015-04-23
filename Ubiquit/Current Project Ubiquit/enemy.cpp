#include <iostream>
#include <SFML/Graphics.hpp>

#include "enemy.hpp"
#include "imageManager.hpp"

Enemy::Enemy(ImageManager *imageManager, int whichEnemy, int X, int Y) : m_type(whichEnemy)
{
    imageManager->GetSpriteEnemy(m_body, m_type);

    if(m_type == ENEMY1)
    {
        m_maskCollide.Top = 0;
        m_maskCollide.Bottom = 0;
        m_maskCollide.Left = 0;
        m_maskCollide.Right = 0;

        m_life.current = 200;
        m_life.max = 200;

        m_body.SetPosition(X, Y);
    }

    else
        std::cerr << "Erreur : création d'un ennemi avec m_type = " << m_type << std::endl;
}

void Enemy::Display(sf::RenderWindow &app)
{
    app.Draw(m_body);
}

void Enemy::Anime()
{
    m_body.Move(1,0);
}
