#include <SFML/Graphics.hpp>

#include "constantes.hpp"
#include "map.hpp"
#include "interface.hpp"
#include "ressourcesManager.hpp"

//TODO remettre la rotation a z�ro lorsqu'on change de bloc (la selection)
//TODO g�rer les identifiants ?
//TODO g�rer les positions de d�part du joueur, des enemis
//TODO g�rer les effets de d�pendance type interrupteurs
//Utilit� des IDs ?
//BUG lorsqu'on ajoute un bloc au word apr�s avoir charg�

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

