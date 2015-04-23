#ifndef H_CLASS_PLAYER_BODY
#define H_CLASS_PLAYER_BODY

class PlayerBody
{
    public :

        PlayerBody(int X, int Y);

        void Move(float X, float Y);

        void Replace(class Level &level, const sf::Input &input);

        void Display(sf::RenderWindow &app);

        float GetArmRotation();

        sf::Vector2f GetArmPosition();

        sf::Vector2f GetInitialPosBullet();

        void RotateArm(const sf::Input &input, float speed);

        bool BodyCollideLeft(class Level &level, float anticipation);
        bool BodyCollideRight(class Level &level, float anticipation);
        bool BodyCollideDown(class Level &level, float anticipation);
        bool BodyCollideUp(class Level &level, float anticipation);

        bool ArmCollide(class Level &level, const sf::Input &input, float anticipation);

        void SetDirection(int direction);

        sf::Vector2f GetPosExtreme(int direction);

    private :

        int RotateArmClockwise(const sf::Input &input); // return angle between arm and mouse

        sf::Vector2f GetArmTipVertexPosition(sf::Vector2f base);

        void SetPos(float X, float Y);

        sf::Image m_charset;

        sf::Sprite m_head;
        sf::Sprite m_belly;
        sf::Sprite m_foot;
        sf::Sprite m_arm;
        sf::Sprite m_shield;

        int m_direction;
};

#endif


