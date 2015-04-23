#include <iostream>
#include <SFML/Graphics.hpp>

#include "level.hpp"
#include "bullet.hpp"

Bullet::Bullet(int whichBullet)
{
    if(!m_charset.LoadFromFile("datas/bullet.bmp"))
        std::cout << "Cannot open the file : \"datas/playerCharset.bmp\"" << std::endl;

    m_charset.SetSmooth(false);
    m_charset.CreateMaskFromColor(sf::Color(0, 250, 250));

    m_body.SetImage(m_charset);

        if(whichBullet == BULLET1)
            m_body.SetSubRect(sf::IntRect(16, 16, 25, 25));

        if(whichBullet == BULLET2)
            m_body.SetSubRect(sf::IntRect(56, 15, 68, 27));

        if(whichBullet == BULLET3)
            m_body.SetSubRect(sf::IntRect(93, 12, 113, 32));

    m_body.SetCenter(m_body.GetSize().x/2, m_body.GetSize().y/2);

    m_isLaunched = false;

    m_direction.x = 0;
    m_direction.y = 0;
}

void Bullet::Display(sf::RenderWindow &app)
{
    app.Draw(m_body);
}

void Bullet::CreateBullet(sf::Vector2f initialPosBullet, float currentRotation)
{
    if(!m_isLaunched)
    {
        initialPosBullet.x += cos(currentRotation*M_PI/180)*56;// 56 is the size of the arm
        initialPosBullet.y -= sin(currentRotation*M_PI/180)*56;

        m_body.SetPosition(initialPosBullet.x, initialPosBullet.y);
    }
}

void Bullet::ActiveBullet(float currentRotation)
{
    if(!m_isLaunched)
    {
        m_direction.x = cos(currentRotation*M_PI/180);
        m_direction.y = sin(currentRotation*M_PI/180);

        m_isLaunched = true;
    }
}

void Bullet::Move(int speed)
{
    if(m_isLaunched)
    {
        sf::Vector2f pos = m_body.GetPosition();

        float X = pos.x;
        float Y = pos.y;

                X += m_direction.x*speed;
                Y -= m_direction.y*speed ;

        m_body.SetPosition(X, Y);
    }
}

bool Bullet::Collide(class Level &level)
{
    sf::Vector2f pos = m_body.GetPosition();
    sf::Vector2f center = m_body.GetCenter();

    float X = pos.x;
    float Y = pos.y;

        if(m_direction.x > 0)     // direction == RIGHT
            X += (center.x)/2;

        else                      // direction == LEFT
            X -= (center.x)/2;

        if(m_direction.y > 0)     // direction == DOWN
            Y += (center.x)/2;

        else                      // direction == UP
            Y -= (center.x)/2;

        if(!level.TileCrossable(X+(m_direction.x*10), Y))
            return true;

        if(!level.TileCrossable(X, Y-(m_direction.y*10)))
            return true;

        if(IsOut())
            return true;

    return false;
}

bool Bullet::IsOut()
{
    sf::Vector2f pos = m_body.GetPosition();

        if(pos.x - m_body.GetCenter().x < LEFT_OFFSET || pos.x + m_body.GetCenter().x > WINDOW_WIDTH  - RIGHT_OFFSET ||
           pos.y - m_body.GetCenter().y <  UP_OFFSET  || pos.y + m_body.GetCenter().y > WINDOW_HEIGHT - DOWN_OFFSET)
                return true;

    return false;
}


