#ifndef CLASS_LEVEL
#define CLASS_LEVEL

#define TILE_WIDTH 40
#define TILE_HEIGHT 40

#define TILE_NUMBER 6

#include "constante.hpp"
#include "world.hpp"
#include "map.hpp"
#include "imageManager.hpp"

struct Tile
{
    //unsigned int ID;

    unsigned int tile;

    unsigned int rotate;
};

class Level
{
    public :

        Level(ImageManager *imageManager);

        void DisplayTiles(sf::RenderWindow &app);

        bool TileCrossable(int X, int Y);
        bool TileCrossable(sf::Vector2f pos);

        void ChangeMap(int direction);

        int ChangeMapDirection(int X, int Y);
        int ChangeMapDirection(sf::Vector2f pos);

        void Load();

    private :

        sf::Vector2i GetOffset(sf::Sprite sprite);

       // void GiveIdentifiant();

        sf::Sprite m_tileMap[TILE_NUMBER_MAP];
        sf::Sprite m_tileWorld[TILE_NUMBER_WORLD];

        World m_world;
        Map m_mapModel;
        std::vector <Map> m_map;

        int m_currentMap;
        sf::Vector2f m_indexCurrentMap;
};


#endif

