#ifndef H_CLASS_PLAYER
#define H_CLASS_PLAYER

#include "bullet.hpp"
#include "playerBody.hpp"
#include "frame.hpp"
#include "stats.hpp"

#define BULLET_NBR_MAX 100

class Player
{
    public :

        Player();
        ~Player();

        void Display(sf::RenderWindow &app);

        void MoveRight(class Level &level, float timeElapsed);
        void MoveLeft(class Level &level, float timeElapsed);

        void ChangeMapReplacement(class Level &level, sf::Vector2f pos);

        sf::Vector2f GetPosExtremeBody(int direction);

        void Jump();

        void MoveArm(const sf::Input &input, class Level &level, float timeElapsed);
        void FallGravity(class Level &level, float timeElapsed);

        void SelectBullet();
        void Amplify();
        void Shoot();
        void MoveBullets(class Level &level, float timeElapsed);

        void DeleteAllBullets();

        void AnimeJump(class Level &level, float timeElapsed);

        void Anime(class Level &level, const sf::Input &input, float timeElapsed);

        bool UsePower(const unsigned int action); // return whether we can act
        bool CanUsePower(const unsigned int action); // return whether we can act

    private :

        struct Speed
        {
            float run, jump, moveArm, shoot, fall;
        };

    private :

        PlayerBody m_body;

        class Bullet * m_bullet[BULLET_NBR_MAX];
        //class Inventory m_inventory;
        //class Skills * m_skills;

        class Stats m_stats;

        class Speed m_speed;

        class Frame m_frame;
};

#endif

