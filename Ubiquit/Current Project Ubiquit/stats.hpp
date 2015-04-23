#ifndef H_CLASS_STATS
#define H_CLASS_STATS

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

struct SpriteBar
{
    sf::Sprite empty;
    sf::Sprite full;
};

struct StatsBar
{
    unsigned int current;
    unsigned int max;
};

struct BarStruct
{
    sf::Image image;
    StatsBar stats;
    SpriteBar sprite;
};

class Stats
{
    public :

        Stats();
        void DisplayStatsBars(sf::RenderWindow &app);

        void RegeneratePower();

        bool Use(int what, const unsigned int action);
        bool CanUse(int what, const unsigned int action);

    private :

        void UseIfPossible(unsigned int *attribute, const unsigned int action);


        void Initialize(BarStruct &bar, std::string nameOfFile);
        void DisplayStatsBar(BarStruct &bar, sf::RenderWindow &app, int X, int Y);
        void RawBar(BarStruct &bar); // tronque la barre, donne un effet de barre non rempli

    private :

        BarStruct m_life, m_power, m_xp;
        unsigned int m_gold;
        unsigned int m_xpEarned, m_xpRemaining;
};

#endif



