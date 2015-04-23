#include <iostream>
#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "level.hpp"

Player::Player() : m_body(500, 200), m_stats(), m_frame(30)
{
    for(int i = 0 ; i < BULLET_NBR_MAX ; i++)
        m_bullet[i] = NULL;

    m_speed.run = 400;
    m_speed.jump = 500;
    m_speed.moveArm = 150;
    m_speed.shoot = 400;
    m_speed.fall = 350;
    /*
    m_speed.run = 100;
    m_speed.jump = 250;
    m_speed.moveArm = 100;
    m_speed.shoot = 300;
    m_speed.fall = 200;
    */
}

Player::~Player()
{
    DeleteAllBullets();
}

void Player::Display(sf::RenderWindow &app)
{
    m_body.Display(app);

    for(int i = 0 ; i < BULLET_NBR_MAX ; i++)
        if(m_bullet[i] != NULL)
            m_bullet[i]->Display(app);

    m_stats.DisplayStatsBars(app);
}

void Player::MoveArm(const sf::Input &input, class Level &level, float timeElapsed)
{
    float SPEED = m_speed.moveArm*timeElapsed;

        if(!m_body.ArmCollide(level, input, 0))
        {
            m_body.RotateArm(input, SPEED);

                while(m_body.ArmCollide(level, input, 0))
                    m_body.RotateArm(input, -0.1);
        }
}

void Player::MoveRight(class Level &level, float timeElapsed)
{
    m_body.SetDirection(RIGHT);

    float SPEED = m_speed.run*timeElapsed;

//////////////////////// If no collide => move ////////////////////////

        if(!m_body.BodyCollideRight(level, SPEED))
           m_body.Move(+SPEED, 0);

/////////////////////////// Pixel Perfect ///////////////////////////

        else while(!m_body.BodyCollideRight(level, 0))
           m_body.Move(+1, 0);

////////////////////////////////////////////////////////////////////
}

void Player::MoveLeft(class Level &level, float timeElapsed)
{
    m_body.SetDirection(LEFT);

    float SPEED = m_speed.run*timeElapsed;

//////////////////////// If no collide => move ////////////////////////

        if(!m_body.BodyCollideLeft(level, SPEED))
           m_body.Move(-SPEED, 0);

/////////////////////////// Pixel Perfect ///////////////////////////

        else while(!m_body.BodyCollideLeft(level, 0))
           m_body.Move(-1, 0);

////////////////////////////////////////////////////////////////////
}

void Player::Shoot()
{
    for(int i = 0 ; i < BULLET_NBR_MAX ; i++)
        if(m_bullet[i] != NULL)
            m_bullet[i]->ActiveBullet(m_body.GetArmRotation());
}

void Player::SelectBullet()
{
    for(int i = 0 ; i < BULLET_NBR_MAX ; i++)
        if(m_bullet[i] == NULL)
        {
            if(UsePower(PowerPrice::shoot))
            {
                m_bullet[i] = new Bullet();
                m_bullet[i]->CreateBullet(m_body.GetInitialPosBullet(), m_body.GetArmRotation());
                i = BULLET_NBR_MAX;
            }
        }
}

void Player::Amplify()
{
    for(int i = 0 ; i < BULLET_NBR_MAX ; i++)
        if(m_bullet[i] != NULL)
            m_bullet[i]->CreateBullet(m_body.GetInitialPosBullet(), m_body.GetArmRotation());
}

void Player::MoveBullets(class Level &level, float timeElapsed)
{
    for(int i = 0 ; i < BULLET_NBR_MAX ; i++)
        if(m_bullet[i] != NULL)
        {
            if(!m_bullet[i]->Collide(level))
                m_bullet[i]->Move(m_speed.shoot*timeElapsed);

            else
            {
                delete m_bullet[i];
                m_bullet[i] = NULL;
            }
        }
}

void Player::DeleteAllBullets()
{
    for(int i = 0 ; i < BULLET_NBR_MAX ; i++)
    {
        if(m_bullet[i] != NULL)
        {
            delete m_bullet[i];
            m_bullet[i] = NULL;
        }
    }
}

void Player::FallGravity(class Level &level, float timeElapsed)
{
    float GRAVITY = m_speed.fall*timeElapsed;

//////////////////////// If no collide => move ////////////////////////

        if(!m_body.BodyCollideDown(level, GRAVITY))
            m_body.Move(0, +GRAVITY);

/////////////////////////// Pixel Perfect ///////////////////////////

        else while(!m_body.BodyCollideDown(level, 0))
            m_body.Move(0, +1);

////////////////////////////////////////////////////////////////////
}

void Player::Jump()
{
    m_frame.ActivateAnime();
}

void Player::AnimeJump(class Level &level, float timeElapsed)
{
    float INTENSITY = m_speed.jump*timeElapsed;

    float currentFrame = m_frame.GetCurrentFrame();
    float maxFrame = m_frame.GetMaxFrame();

    if(m_frame.AnimeIsOngoing())
    {
        if(!m_body.BodyCollideUp(level, INTENSITY))
        {
            INTENSITY = m_speed.jump*timeElapsed*((maxFrame-currentFrame)*2/maxFrame);

            m_body.Move(0, -INTENSITY);
        }

        else    // if collide
        {
            m_frame.DesactivateAnime();

                while (!m_body.BodyCollideUp(level, 0)) //adjust
                    m_body.Move(0, -1);
        }
    }
}

void Player::Anime(class Level &level, const sf::Input &input, float timeElapsed)
{
    MoveBullets(level, timeElapsed);
    AnimeJump(level, timeElapsed);
    FallGravity(level, timeElapsed);

        for(int i = 0 ;  i < 3 ; i++)
            m_body.Replace(level, input);

    m_stats.RegeneratePower();
}

bool Player::UsePower(const unsigned int action)
{
    return m_stats.Use(POWER, action);
}

bool Player::CanUsePower(const unsigned int action)
{
    return m_stats.CanUse(POWER, action);
}

void Player::ChangeMapReplacement(class Level &level, sf::Vector2f pos)
{
    int direction = level.ChangeMapDirection(pos.x, pos.y);

    int BODY_HEIGHT = GetPosExtremeBody(DOWN).y-GetPosExtremeBody(UP).y;

    if(direction == UP)
        m_body.Move(0, +WINDOW_HEIGHT - GetPosExtremeBody(UP).y - DOWN_OFFSET - BODY_HEIGHT);

    if(direction == DOWN)
        m_body.Move(0, +UP_OFFSET - GetPosExtremeBody(DOWN).y + BODY_HEIGHT);

    if(direction == LEFT)
    {
        m_body.Move(+WINDOW_WIDTH - RIGHT_OFFSET, 0);
    }

    if(direction == RIGHT)
    {
        m_body.Move(-WINDOW_WIDTH + LEFT_OFFSET, 0);
    }
}

sf::Vector2f Player::GetPosExtremeBody(int direction)
{
    return m_body.GetPosExtreme(direction);
}
