#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "constantes.hpp"
#include "levelEditor.hpp"

LevelEditor::LevelEditor() :
    m_app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Level Editor"),
    m_input(m_app.GetInput()),
    m_ressourcesManager(new RessourcesManager),
    m_interface(*m_ressourcesManager), m_mapModel(), m_world(),
    m_currentRotation(0), m_currentMap(-1), m_editMode(EDIT)
{
    m_app.SetFramerateLimit(60);

        for(int i = 0 ; i < TILE_NUMBER_MAP ; i++)
            m_ressourcesManager->GetSprite(m_tileMap[i], i, MAP);

        for(int i = 0 ; i < TILE_NUMBER_WORLD ; i++)
            m_ressourcesManager->GetSprite(m_tileWorld[i], i, WORLD);

    m_modeSelection = WORLD;
    m_editMode = EDIT;

    AssignTileSet();

    m_map.clear();

    m_indexCurrentMap.x = -1;   // For error
    m_indexCurrentMap.y = -1;

    m_indexInitialMapPosPlayer.x = 0;
    m_indexInitialMapPosPlayer.y = 0;
}

LevelEditor::~LevelEditor()
{
    delete m_ressourcesManager;
}

void LevelEditor::Display()
{
    m_app.Clear(sf::Color(255, 255, 200));

        if(m_modeSelection == MAP)
        {
            m_map[m_currentMap].Display(m_tileMap, m_app);
            m_interface.DisplayEnviron(m_tileMap, m_app, m_currentRotation);
        }

        if(m_modeSelection == WORLD)
        {
            m_world.Display(m_tileWorld, m_app);
            m_interface.DisplayEnviron(m_tileWorld, m_app, m_currentRotation);
        }

    m_app.Display();
}

void LevelEditor::AssignTileSet()
{
    if(m_modeSelection == MAP)
    {
        m_interface.AssignTileSetMap();
    }

    else if(m_modeSelection == WORLD)
    {
        m_interface.AssignTileSetWorld();
    }
}

bool LevelEditor::IsOpened()
{
    return m_app.IsOpened();
}

void LevelEditor::ManageEvent()
{
    while (m_app.GetEvent(m_event))
        ManageNoRealTimeEvent();

    ManageRealTimeEvent();
}

void LevelEditor::Rotate()
{
    m_currentRotation += 90;

    if(m_currentRotation >= 360)
        m_currentRotation = 0;
}

void LevelEditor::ChangeModeSelection()
{
    if(m_modeSelection == MAP)
        m_modeSelection = WORLD;

    else
        m_modeSelection = MAP;

}
void LevelEditor::ChangeEditMode()
{
    if(m_editMode == SELECTION_MAP)
        m_editMode = EDIT;

    else if(m_editMode == SELECTION_INITIAL_MAP)
        m_editMode = SELECTION_MAP;

    else
        m_editMode = SELECTION_MAP;

    std::cout << "Change Edit Mode" << std::endl;
}

void LevelEditor::Save()
{
    std::string const nomFichier("Datas/mainLevel.txt");
    std::ofstream file(nomFichier.c_str());

    if(!file)
    {
        std::cerr << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

    else
    {
        m_world.PrintInFile(file);

            for(unsigned int i = 0 ; i < m_map.size() ; i++)
            {
                file << std::endl;
                file << std::endl;
                m_map[i].PrintInFile(file);
            }

        file << std::endl;
        file << std::endl;

        file << m_indexInitialMapPosPlayer.x << " " << m_indexInitialMapPosPlayer.y;

        file << std::endl;
        file << std::endl;
        file << m_map.size();
    }
}

void LevelEditor::Load()
{
    std::string const nomFichier("Datas/mainLevel.txt");
    std::ifstream file(nomFichier.c_str());

    if(!file)
    {
        std::cerr << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

    else
    {
        m_world.ReadInFile(file);

        //m_world.InitializeIDs();

            for(int i = 0 ; i < m_world.GetNumberOfSquare() ; i++)
                m_map.push_back(m_mapModel);

            for(unsigned int i = 0 ; i < m_map.size() ; i++)
                m_map[i].ReadInFile(file);

        file >> m_indexInitialMapPosPlayer.x;
        file >> m_indexInitialMapPosPlayer.y;
    }
}

void LevelEditor::ManageNoRealTimeEvent()
{
    if (m_event.Type == sf::Event::Closed)
        m_app.Close();

    if (m_event.Type == sf::Event::MouseButtonPressed)
    {
        if(m_input.GetMouseY() > LEVEL_HEIGHT*TILE_HEIGHT)
        {
            if(m_event.MouseButton.Button == sf::Mouse::Left)
                m_interface.SelectSprite(m_input.GetMouseX(), +1);

            if(m_event.MouseButton.Button == sf::Mouse::Right)
                m_interface.SelectSprite(m_input.GetMouseX(), -1);
        }
    }

    if(m_event.Type == sf::Event::KeyReleased)
    {
        if(m_modeSelection == MAP)
        {
            if(m_event.Key.Code == sf::Key::S)
                m_map[m_currentMap].Save();

            if(m_event.Key.Code == sf::Key::L)
                m_map[m_currentMap].Load();

            if(m_event.Key.Code == sf::Key::E)
                m_map[m_currentMap].EraseAll();

            if(m_event.Key.Code == sf::Key::Up ||
               m_event.Key.Code == sf::Key::Down ||
               m_event.Key.Code == sf::Key::Left ||
               m_event.Key.Code == sf::Key::Right)
            {
                 if(m_event.Key.Code == sf::Key::Up)
                 {
                    if(!m_world.SquareIsEmptyIndex(m_indexCurrentMap.x, m_indexCurrentMap.y-1))
                    {
                        m_indexCurrentMap.y--;
                        m_currentMap = m_world.GetIDFromIndex(m_indexCurrentMap.x, m_indexCurrentMap.y);
                    }
                 }

                else if(m_event.Key.Code == sf::Key::Down)
                {
                    if(!m_world.SquareIsEmptyIndex(m_indexCurrentMap.x, m_indexCurrentMap.y+1))
                    {
                        m_indexCurrentMap.y++;
                        m_currentMap = m_world.GetIDFromIndex(m_indexCurrentMap.x, m_indexCurrentMap.y);
                    }
                }

                else if(m_event.Key.Code == sf::Key::Left)
                {
                    if(!m_world.SquareIsEmptyIndex(m_indexCurrentMap.x-1, m_indexCurrentMap.y))
                    {
                        m_indexCurrentMap.x--;
                        m_currentMap = m_world.GetIDFromIndex(m_indexCurrentMap.x, m_indexCurrentMap.y);
                    }
                }

                else if(m_event.Key.Code == sf::Key::Right)
                {
                    if(!m_world.SquareIsEmptyIndex(m_indexCurrentMap.x+1, m_indexCurrentMap.y))
                    {
                        m_indexCurrentMap.x++;
                        m_currentMap = m_world.GetIDFromIndex(m_indexCurrentMap.x, m_indexCurrentMap.y);
                    }
                }
            }
        }

        if(m_modeSelection == WORLD)
        {
            if(m_event.Key.Code == sf::Key::S)
                m_world.Save();

            if(m_event.Key.Code == sf::Key::L)
            {
                m_world.Load();

                m_map.clear();

                    for(int i = 0 ; i < m_world.GetNumberOfSquare() ; i++)
                        m_map.push_back(m_mapModel);
            }

            if(m_event.Key.Code == sf::Key::E)
            {
                m_world.EraseAll();
                m_map.clear();
            }

            if(m_event.Key.Code == sf::Key::A)
                ChangeEditMode();

            if(m_event.Key.Code == sf::Key::B)
                m_editMode = SELECTION_INITIAL_MAP;
        }

        if(m_event.Key.Code == sf::Key::R)
            Rotate();

        if(m_event.Key.Code == sf::Key::C)
            ChangeModeSelection();
    }
}

void LevelEditor::ManageRealTimeEvent()
{
    if(m_editMode == EDIT)
    {
        if(m_input.IsMouseButtonDown(sf::Mouse::Left))
        {
            if(m_input.GetMouseY() <= LEVEL_HEIGHT*TILE_HEIGHT)
            {
                if(m_modeSelection == MAP)
                    m_map[m_currentMap].SetSquare(m_interface.GetSelection(), m_input.GetMouseX(), m_input.GetMouseY(), m_currentRotation);

                if(m_modeSelection == WORLD)
                {
                    if(m_world.SetSquare(m_interface.GetSelection(), m_input.GetMouseX(), m_input.GetMouseY(), m_currentRotation))
                        m_map.push_back(m_mapModel);
                }
            }
        }

        if(m_input.IsMouseButtonDown(sf::Mouse::Right))
        {
            if(m_input.GetMouseY() <= LEVEL_HEIGHT*TILE_HEIGHT)
            {
                if(m_modeSelection == MAP)
                    m_map[m_currentMap].Erase(m_input.GetMouseX(), m_input.GetMouseY());

                if(m_modeSelection == WORLD)
                {
                    if(m_world.Erase(m_input.GetMouseX(), m_input.GetMouseY()))
                        m_map.pop_back();
                }
            }
        }
    }

    if(m_editMode == SELECTION_MAP)
    {
        if(m_input.IsMouseButtonDown(sf::Mouse::Left))
        {
            if(m_input.GetMouseY() <= LEVEL_HEIGHT*TILE_HEIGHT)
            {
                if(!m_world.SquareIsEmpty(m_input.GetMouseX(), m_input.GetMouseY()))
                {
                    ChangeModeSelection();
                    ChangeEditMode();
                    //m_world.InitializeIDs();
                    m_indexCurrentMap.x = m_input.GetMouseX()/TILE_WIDTH;
                    m_indexCurrentMap.y = m_input.GetMouseY()/TILE_HEIGHT;
                    std::cout << m_currentMap;
                    m_currentMap = m_world.GetIDFromIndex(m_indexCurrentMap.x, m_indexCurrentMap.y);

                    std::cout << m_currentMap;
                }
            }
        }
    }

    if(m_editMode == SELECTION_INITIAL_MAP)
    {
        if(m_input.IsMouseButtonDown(sf::Mouse::Left))
        {
            if(m_input.GetMouseY() <= LEVEL_HEIGHT*TILE_HEIGHT)
            {
                if(!m_world.SquareIsEmpty(m_input.GetMouseX(), m_input.GetMouseY()))
                {
                    ChangeEditMode();
                    m_indexInitialMapPosPlayer.x = m_input.GetMouseX()/TILE_WIDTH;
                    m_indexInitialMapPosPlayer.y = m_input.GetMouseY()/TILE_HEIGHT;
                }
            }
        }
    }
}

