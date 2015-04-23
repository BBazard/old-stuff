#ifndef CLASS_WORLD
#define CLASS_WORLD

struct LinkWorld
{
    //unsigned int ID;
    bool isLinked;
};

struct TileWorld
{
    unsigned int ID; // utilité ?

    unsigned int tile;

    int rotate;   // Lors de la sauvegarde, enregistrer ce paramètre pour afficher la map en jeu mais changer aussi

    LinkWorld link[4];
};

class World
{
    public :

        World();

        void Display(sf::Sprite* tile, sf::RenderWindow &app);

        void EraseAll();

        bool Erase(int X, int Y);   // return true if the number of square change

        bool SetSquare(int tile, int X, int Y, int angle);        // return true if the number of square change

        void Load();
        void PrintInFile(std::ofstream &file);

        void ReadInFile(std::ifstream &file);

        void InitializeIDs();

        bool SquareIsEmptyIndex(int indexX, int indexY);

        int GetIDFromIndex(int X, int Y);

        int GetNumberOfSquare();

    private :

        bool LinkUp(TileWorld &tile);
        bool LinkDown(TileWorld &tile);
        bool LinkLeft(TileWorld &tile);
        bool LinkRight(TileWorld &tile);

        sf::Vector2i GetOffset(sf::Sprite sprite);


        // void GiveIdentifiant();

    private :

        TileWorld m_world[LEVEL_WIDTH][LEVEL_HEIGHT]; // std::vector ?
};



#endif
