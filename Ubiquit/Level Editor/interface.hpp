#ifndef CLASS_INTERFACE
#define CLASS_INTERFACE

class Interface
{
    public :

        Interface(class RessourcesManager &ressourcesManager);

        void SelectSprite(int X, int nbr);

        void DisplayEnviron(sf::Sprite* tile, sf::RenderWindow &app, float currentRotation);

        void AssignTileSetMap();
        void AssignTileSetWorld();

        int GetSelection();

        sf::Vector2i GetOffset(sf::Sprite* tile);//

    private :


    private :

        sf::Sprite m_selectSprite;

        sf::Sprite m_tileToolBox;

        int m_currentSprite;

        int m_modeSelection;
};


#endif




