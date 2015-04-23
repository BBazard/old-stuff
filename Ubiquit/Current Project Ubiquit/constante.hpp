#ifndef H_CONST
#define H_CONST

#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define M_PI 3.14159

#define TILE_WIDTH 40
#define TILE_HEIGHT 40

#define TILE_NUMBER_MAP 6
#define TILE_NUMBER_WORLD 6

#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 13

#define UP_OFFSET 50  // offsets around the main screen
#define DOWN_OFFSET 30
#define LEFT_OFFSET 0
#define RIGHT_OFFSET 0

    enum{UP, DOWN, LEFT, RIGHT};    // for the whole game

    enum{QUADRILLAGE_MAP, BLOC, OBSTACLE, OBSTACLE2, INTERRUPTEUR_GAUCHE, INTERRUPTEUR_DROITE, NOTHING_MAP}; //For MAP
    enum{QUADRILLAGE_WORLD, ONE, TWO, THREE, TWO2, FOUR, NOTHING_WORLD}; //For WORLD

    enum{MAP, WORLD};    // For RessourcesManager

    // pour les enum suivant, crée une struct avec un const int comme enum et un pointeur sur le type désiré

    enum{LIFE, POWER, XP, GOLD};  //for Stats

    enum{BULLET1, BULLET2, BULLET3};    // For Bullet

    enum{ENEMY1};    // For Enemies

class PowerPrice
{
    public :

        const static unsigned int
        shoot = 100,
        regeneration = 1;
};

void InitializeCursor(sf::Image &imageCursor, sf::Sprite &cursor);

void ManageEvents(sf::RenderWindow &app, sf::Event &event, const sf::Input &input, class Player &player, sf::Sprite &cursor, class Level &level);

void ManageRealTimeEvents(const sf::Input &input, class Player &player, class Level &level, sf::RenderWindow &app);
void ManageNoRealTimeEvents(sf::RenderWindow &app, sf::Event &event, const sf::Input &input, class Player &player, sf::Sprite &cursor);

void Display(sf::RenderWindow &app, class Player &player, sf::Sprite cursor, class Level &level, class Horde &horde);

#endif
