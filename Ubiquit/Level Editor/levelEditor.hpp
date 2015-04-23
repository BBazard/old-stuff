#ifndef CLASS_LEVEL_EDITOR
#define CLASS_LEVEL_EDITOR

#include "ressourcesManager.hpp"
#include "interface.hpp"
#include "map.hpp"
#include "world.hpp"

class LevelEditor
{
    public :

        LevelEditor();
        ~LevelEditor();

        bool IsOpened();

        void ManageEvent();

        void Anime();

        void Display();

        void Save();
        void Load();

    private :

        void ManageNoRealTimeEvent();
        void ManageRealTimeEvent();

        void AssignTileSet();

        void Rotate();

        void ChangeModeSelection();

        void ChangeEditMode();

    private :

        sf::RenderWindow m_app;

        sf::Event m_event;
        const sf::Input& m_input;

        RessourcesManager *m_ressourcesManager;

        Interface m_interface;

        Map m_mapModel;
            std::vector <Map> m_map;

        World m_world;

        sf::Sprite m_tileMap[TILE_NUMBER_MAP];
        sf::Sprite m_tileWorld[TILE_NUMBER_WORLD];

        int m_currentRotation;
        int m_currentMap;
        sf::Vector2i m_indexCurrentMap;
        sf::Vector2i m_indexInitialMapPosPlayer;    // where the player begin

        int m_modeSelection;   // WORLD or MAP
        int m_editMode;   // EDIT or SELECTION_MAP or SELECTION_INITIAL_MAP
};


#endif





