#include <iostream>
#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "level.hpp"

PlayerBody::PlayerBody(int X, int Y) : m_direction(RIGHT)
{
    if(!m_charset.LoadFromFile("datas/playerCharset.bmp"))
        std::cout << "Cannot open the file : \"datas/playerCharset.bmp\"" << std::endl;

    m_charset.SetSmooth(false);
    m_charset.CreateMaskFromColor(sf::Color(0, 250, 250));

    m_head.SetImage(m_charset);
    m_belly.SetImage(m_charset);
    m_foot.SetImage(m_charset);
    m_arm.SetImage(m_charset);
    m_shield.SetImage(m_charset);

    m_head.SetSubRect(sf::IntRect(9, 0, 40, 20));
    m_belly.SetSubRect(sf::IntRect(0, 21, 40, 88));
    m_foot.SetSubRect(sf::IntRect(7, 89, 33, 102));
    m_arm.SetSubRect(sf::IntRect(41, 0, 91, 11));
    m_shield.SetSubRect(sf::IntRect(41, 12, 91, 112));

    m_arm.SetCenter(3, 5);
    m_shield.SetCenter(25, 50);

    SetPos(X, Y);
}

void PlayerBody::Move(float X, float Y)
{
    m_head.Move(X, Y);
    m_belly.Move(X, Y);
    m_foot.Move(X, Y);
    m_arm.Move(X, Y);
    m_shield.Move(X, Y);
}

void PlayerBody::Display(sf::RenderWindow &app)
{
    app.Draw(m_head);
    app.Draw(m_belly);
    app.Draw(m_foot);
    app.Draw(m_arm);

    if(0)
        app.Draw(m_shield);
}

float PlayerBody::GetArmRotation()
{
    return m_arm.GetRotation();
}

sf::Vector2f PlayerBody::GetInitialPosBullet()
{
    return m_arm.GetPosition();
}

int PlayerBody::RotateArmClockwise(const sf::Input &input)
{
    float X = input.GetMouseX() - m_arm.GetPosition().x;
    float Y = input.GetMouseY() - m_arm.GetPosition().y;

    float angle = atan2(X, Y)*180/M_PI-90;

    float difference = angle-m_arm.GetRotation();;

        while(difference < 0)
            difference+= 360;

    return difference;
}

void PlayerBody::RotateArm(const sf::Input &input, float speed)
{
    float SPEED = speed;  // the less SPEED is the more the animation is smooth

    int difference = RotateArmClockwise(input);

        if(difference < SPEED && difference > -SPEED);

        else if(difference > 180)
            m_arm.Rotate(-SPEED);

        else
            m_arm.Rotate(SPEED);
}

bool PlayerBody::BodyCollideLeft(class Level &level, float anticipation)
{
    float X = m_head.GetPosition().x-anticipation;
    float Y = m_head.GetPosition().y;

        if(!((level.TileCrossable(X, Y)) &&
           (level.TileCrossable(X, Y+m_head.GetSize().y-1))))
                return true;

    X = m_belly.GetPosition().x-anticipation-1;
    Y = m_belly.GetPosition().y;

        if(!((level.TileCrossable(X, Y)) &&
           (level.TileCrossable(X, Y+m_belly.GetSize().y-1)) &&
           (level.TileCrossable(X, Y+(m_belly.GetSize().y/2)))))
                return true;

    X = m_foot.GetPosition().x-anticipation;
    Y = m_foot.GetPosition().y;

        if(!((level.TileCrossable(X, Y)) &&
           (level.TileCrossable(X, Y+m_foot.GetSize().y-1))))
                return true;

    return false;
}

bool PlayerBody::BodyCollideRight(class Level &level, float anticipation)
{
    float X = m_head.GetPosition().x+m_head.GetSize().x+anticipation;
    float Y = m_head.GetPosition().y;

        if(!((level.TileCrossable(X, Y)) &&
           (level.TileCrossable(X, Y+m_head.GetSize().y-1))))
                return true;

    X = m_belly.GetPosition().x+m_belly.GetSize().x+anticipation;
    Y = m_belly.GetPosition().y;

        if(!((level.TileCrossable(X, Y)) &&
           (level.TileCrossable(X, Y+m_belly.GetSize().y-1)) &&
           (level.TileCrossable(X, Y+(m_belly.GetSize().y/2)))))
                return true;

    X = m_foot.GetPosition().x+m_foot.GetSize().x-1+anticipation;
    Y = m_foot.GetPosition().y;

        if(!((level.TileCrossable(X, Y)) &&
           (level.TileCrossable(X, Y+m_foot.GetSize().y-1))))
                return true;

    return false;
}

bool PlayerBody::BodyCollideDown(class Level &level, float anticipation)
{
    float X = m_foot.GetPosition().x;
    float Y = m_foot.GetPosition().y+m_foot.GetSize().y+anticipation;

        if((level.TileCrossable(X, Y)) &&
           (level.TileCrossable(X+m_foot.GetSize().x-1, Y)))
                return false;

    return true;
}

bool PlayerBody::BodyCollideUp(class Level &level, float anticipation)
{
    float X = m_head.GetPosition().x;
    float Y = m_head.GetPosition().y-anticipation-1;

        if((level.TileCrossable(X, Y)) &&
           (level.TileCrossable(X+m_head.GetSize().x-1, Y)))
                return false;

    return true;
}

void PlayerBody::SetDirection(int direction)
{
    if(direction == RIGHT && m_direction != RIGHT)
    {
        m_head.FlipX(false);
        m_shield.FlipX(false);
        m_direction = RIGHT;
        m_shield.SetPosition(m_arm.GetPosition().x+60, m_arm.GetPosition().y);
        m_head.SetPosition(m_head.GetPosition().x+9, m_head.GetPosition().y);
    }

    else if(direction == LEFT && m_direction != LEFT)
    {
        m_head.FlipX(true);
        m_shield.FlipX(true);
        m_direction = LEFT;
        m_shield.SetPosition(m_arm.GetPosition().x-60, m_arm.GetPosition().y);
        m_head.SetPosition(m_head.GetPosition().x-9, m_head.GetPosition().y);
    }

    else if (direction != RIGHT && direction != LEFT)
        std::cout << "Erreur le corps du joueur a une direction qui n'est ni la droite, ni la gauche ! " << std::endl;

}

void PlayerBody::SetPos(float X, float Y)
{
    sf::Vector2f m_pos(X, Y);

    if(m_direction == RIGHT)
        m_head.SetPosition(m_pos.x-11, m_pos.y-m_head.GetSize().y-10);

    if(m_direction == LEFT)
        m_head.SetPosition(m_pos.x-19, m_pos.y-m_head.GetSize().y-10);

    m_belly.SetPosition(m_pos.x-20,m_pos.y-10);
    m_foot.SetPosition(m_pos.x-13, m_pos.y+57);
    m_arm.SetPosition(m_pos.x, m_pos.y);

        if(m_direction == RIGHT)
        {
            m_shield.FlipX(false);
            m_shield.SetPosition(m_pos.x+60, m_pos.y);
        }

        if(m_direction == LEFT)
        {
            m_shield.FlipX(true);
            m_shield.SetPosition(m_pos.x-60, m_pos.y);
        }
}

void PlayerBody::Replace(class Level &level, const sf::Input &input)
{
    float X = m_belly.GetPosition().x;
    float Y = m_belly.GetPosition().y;

        if(!(((level.TileCrossable(X+m_belly.GetSize().x-1, Y)) &&
            level.TileCrossable(X+m_belly.GetSize().x-1, Y+m_belly.GetSize().y)) &&
            level.TileCrossable(X+m_belly.GetSize().x-1, Y+(m_belly.GetSize().y/2))))
            {
                Move(-1, 0);
            }

        if(!(((level.TileCrossable(X, Y)) &&
            level.TileCrossable(X, Y+m_belly.GetSize().y)) &&
            level.TileCrossable(X, Y+(m_belly.GetSize().y/2))))
            {
                Move(+1, 0);
            }

    X = m_foot.GetPosition().x;
    Y = m_foot.GetPosition().y;

        if(!((level.TileCrossable(X+m_foot.GetSize().x-1, Y-1)) &&
            level.TileCrossable(X+m_foot.GetSize().x-1, Y+m_foot.GetSize().y-1)))
            {
                Move(-1, 0);
            }

        if(!((level.TileCrossable(X, Y-1)) &&
            level.TileCrossable(X, Y+(m_foot.GetSize().y-1))))
            {
                Move(+1, 0);
            }

    if(ArmCollide(level, input, 0))
    {
        int SPEED = 1;
        int angle = m_arm.GetRotation();

            if((angle >= 0 && angle <= 90) || (angle >= 180 && angle <= 270))
                m_arm.Rotate(SPEED);

            else if((angle >= 90 && angle <= 180)  || (angle >= 270 && angle <= 360))
                m_arm.Rotate(-SPEED);
    }
}

sf::Vector2f PlayerBody::GetArmPosition()
{
    return m_arm.GetPosition();
}

bool PlayerBody::ArmCollide(class Level &level, const sf::Input &input, float anticipation)
{
    RotateArm(input, anticipation);
    float angle = m_arm.GetRotation();
    RotateArm(input, -anticipation);

    float horizontalDistance = 0;
    float verticalDistance = 0;

    horizontalDistance = (m_arm.GetCenter().y)*sin(angle*M_PI/180);
    verticalDistance = (m_arm.GetCenter().y)*cos(angle*M_PI/180);

    sf::Vector2f DownBase;

        DownBase.x = m_arm.GetPosition().x + horizontalDistance;
        DownBase.y = m_arm.GetPosition().y + verticalDistance;

    sf::Vector2f DownTip = GetArmTipVertexPosition(DownBase);

///////////////////////////////////////////////////////////////////////////////////////

    horizontalDistance = (m_arm.GetSize().y - m_arm.GetCenter().y)*sin(angle*M_PI/180);
    verticalDistance = (m_arm.GetSize().y - m_arm.GetCenter().y)*cos(angle*M_PI/180);

    sf::Vector2f UpBase;

        UpBase.x = m_arm.GetPosition().x - horizontalDistance;
        UpBase.y = m_arm.GetPosition().y - verticalDistance;

    sf::Vector2f UpTip = GetArmTipVertexPosition(UpBase);

    // y = a * x + b
    // line equation
    const float aDown = (DownBase.y - DownTip.y) / (DownBase.x - DownTip.x);
    const float bDown = DownBase.y - (aDown * DownBase.x);

    const float aUp = (UpBase.y - UpTip.y) / (UpBase.x - UpTip.x);
    const float bUp = UpBase.y - (aUp * UpBase.x);

//////////////////////////////////////////////////////////////////////////////
    float pas = 1;
    float correction = 5;
////////////////////////////////////////////////////////////////////////////

    float Xdown, Ydown;

    Xdown = DownBase.x;
    Ydown = DownBase.y;

    if(aDown < 5 && aDown > -5)   // si le bras n'est pas totalement verticale
    {
        if((DownTip.x-DownBase.x) > 0)
        {
            while((level.TileCrossable(Xdown, Ydown) && (Xdown < DownTip.x-correction)))
            {
                Xdown += pas;
                Ydown = aDown * Xdown + bDown;
            }
        }

        else
        {
            while((level.TileCrossable(Xdown, Ydown) && (Xdown > DownTip.x+correction)))
            {
                Xdown -= pas;
                Ydown = aDown * Xdown + bDown;
            }
        }

        if(!level.TileCrossable(Xdown, Ydown))
            return true;
    }

////////////////////////////////////////////////////////////////////////////////////////

    float Xup, Yup;

    Xup = UpBase.x;
    Yup = UpBase.y;

    if(aUp < 5 && aUp > -5)   // si le bras n'est pas totalement verticale
    {
        if((UpTip.x-UpBase.x) > 0)
        {
            while((level.TileCrossable(Xup, Yup) && (Xup < UpTip.x-correction)))
            {
                Xup += pas;
                Yup = aUp * Xup + bUp;
            }
        }

        else
        {
            while((level.TileCrossable(Xup, Yup) && (Xup > UpTip.x+correction)))
            {
                Xup -= pas;
                Yup = aUp * Xup + bUp;
            }
        }

        if(!level.TileCrossable(Xup, Yup))
                return true;
    }

    return false;
}

sf::Vector2f PlayerBody::GetArmTipVertexPosition(sf::Vector2f base)
{
    float X = base.x;
    float Y = base.y;

    float angle = m_arm.GetRotation();

    float horizontalDistance = m_arm.GetSize().x*cos(angle*M_PI/180);
    float verticalDistance = m_arm.GetSize().x*sin(angle*M_PI/180);

    sf::Vector2f posTip;

        posTip.x = X + horizontalDistance;
        posTip.y = Y - verticalDistance;

    return posTip;
}

sf::Vector2f PlayerBody::GetPosExtreme(int direction)
{
    sf::Vector2f pos;
    pos.x = m_belly.GetPosition().x + m_belly.GetSize().x/2;
    pos.y = m_belly.GetPosition().y + m_belly.GetSize().y/2;

    if(direction == UP)
        pos.y = m_head.GetPosition().y;

    else if(direction == DOWN)
        pos.y = m_foot.GetPosition().y + m_foot.GetSize().y;

    else if(direction == LEFT)
        pos.x = m_belly.GetPosition().x+m_belly.GetSize().x/2;

    else if(direction == RIGHT)
        pos.x = m_belly.GetPosition().x+m_belly.GetSize().x/2;

    else
        std::cerr << "erreur dans playerBody::GetPosBelly, direction = " << direction << std::endl;

    return pos;
}
