#include <SFML/Graphics.hpp>

#include "constantes.hpp"
#include "map.hpp"
#include "interface.hpp"
#include "ressourcesManager.hpp"

//TODO remettre la rotation a zéro lorsqu'on change de bloc (la selection)
//TODO gérer les identifiants ?
//TODO gérer les positions de départ du joueur, des enemis
//TODO gérer les effets de dépendance type interrupteurs
//Utilité des IDs ?
//BUG lorsqu'on ajoute un bloc au word après avoir chargé

int main()
{
    LevelEditor levelEditor;

    levelEditor.Load();

    while (levelEditor.IsOpened())
    {
        levelEditor.ManageEvent();
        levelEditor.Display();
    }

    levelEditor.Save();

    return EXIT_SUCCESS;
}

