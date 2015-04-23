#ifndef H_CLASS_BULLET
#define H_CLASS_BULLET

#include "constante.hpp"

class Bullet
{
    public :

        Bullet(int whichBullet = BULLET1);

        void Display(sf::RenderWindow &app);

        void CreateBullet(sf::Vector2f initialPosBullet, float currentRotation);

        void ActiveBullet(float currentRotation);

        void Move(int speed);

        bool IsOut();

        bool Collide(class Level &level);

    private :

        sf::Image m_charset;

        sf::Sprite m_body;

        sf::Vector2<float> m_direction;

        bool m_isLaunched;
};

#endif



