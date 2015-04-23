#include <iostream>
#include <SFML/Graphics.hpp>

#include "level.hpp"
#include "player.hpp"
#include "horde.hpp"

using namespace sf;

// TODO faire un charset des enemy
// TODO faire hériter les classe de NonCopyable ?
// TODO pour le manager de ressources ne charger les image que lorsque c'est nécessaire : utilité ?
// TODO gérer les glissement (réduire le masque de collisions)
// TODO mettre le cursor dans la classe environ/interface ?
// TODO gerer les cas ou les level sont mal fait, ex : on peut aller à gauche mais il n'y a pas de map
// TODO mettre les images des classes stats et playerBody dans le ImageManager
// BUG les balles n'arrive pas totalement au milieu du curseur
// BUG colision balle selon la taille
// BUG le player tombe lorsque l'on bouge la fenetre, ou redimensionne

int main()
{
    RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Ubiquit : Virtually Ubiquitous");

    app.SetFramerateLimit(50);

    app.ShowMouseCursor(false);

    Image imageCursor;
    Sprite cursor;
        InitializeCursor(imageCursor, cursor);

    ImageManager *imageManager;
    imageManager = new ImageManager;

    Level level(imageManager);
    Player player;

    Horde horde(imageManager);

    while(app.IsOpened())
    {
        Event event;

        ManageEvents(app, event, app.GetInput(), player, cursor, level);

        player.Anime(level, app.GetInput(), app.GetFrameTime());

        horde.Anime();

        Display(app, player, cursor, level, horde);
    }

    delete imageManager;

    return EXIT_SUCCESS;
}



