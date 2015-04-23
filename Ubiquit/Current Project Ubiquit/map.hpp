#ifndef CLASS_MAP
#define CLASS_MAP

struct LinkMap
{
    //unsigned int ID;
    unsigned int effet;
};

struct TileMap
{
   // unsigned int ID;

    unsigned int tile;
    float rotate;

   // std::vector<LinkMap> link;
};

class Map
{
    public :

        Map();

        void Display(sf::Sprite* tile, sf::RenderWindow &app);

        void ReadInFile(std::ifstream &file);

        bool TileCrossable(int X, int Y);

    private :

        sf::Vector2i GetOffset(sf::Sprite tileSet);

        // void GiveIdentifiant();
        //void SetID(int X, int Y);

    private :

       // int m_ID;
        TileMap m_map[LEVEL_WIDTH][LEVEL_HEIGHT];
};


#endif


