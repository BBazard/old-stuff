#include <iostream>
#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "horde.hpp"
#include "level.hpp"

void InitializeCursor(sf::Image &imageCursor, sf::Sprite &cursor)
{
    if(!imageCursor.LoadFromFile("datas/cursor.bmp"))
        std::cout << "Cannot open the file : \"datas/cursor.bmp\"" << std::endl;

    imageCursor.SetSmooth(false);
    imageCursor.CreateMaskFromColor(sf::Color(0, 250, 250));

    cursor.SetImage(imageCursor);

    cursor.SetCenter(cursor.GetSize().x/2, cursor.GetSize().y/2);
}

void ManageEvents(sf::RenderWindow &app, sf::Event &event, const sf::Input &input, class Player &player, sf::Sprite &cursor, class Level &level)
{
    ManageNoRealTimeEvents(app, event, input, player, cursor);
    ManageRealTimeEvents(input, player, level, app);
}

void ManageNoRealTimeEvents(sf::RenderWindow &app, sf::Event &event, const sf::Input &input, class Player &player, sf::Sprite &cursor)
{
    static bool keySpaceDown = false;   // TO DELETE

    while (app.GetEvent(event))
    {
        if (event.Type == sf::Event::Closed)
        {
            app.Close();
        }

        if(event.Type == sf::Event::MouseMoved)
        {
            cursor.SetPosition(input.GetMouseX(), input.GetMouseY());
        }

        if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Space))
        {
            if(!keySpaceDown)
            {
                player.SelectBullet();
                keySpaceDown = true;
            }
        }

        if ((event.Type == sf::Event::KeyReleased) && (event.Key.Code == sf::Key::Space))
        {
            player.Shoot();
            keySpaceDown = false;
        }

        if ((event.Type == sf::Event::KeyReleased) && (event.Key.Code == sf::Key::Up))
        {
            player.Jump();
        }
    }
}

void ManageRealTimeEvents(const sf::Input &input, class Player &player, class Level &level, sf::RenderWindow &app)
{
    player.MoveArm(input, level, app.GetFrameTime());

        if(input.IsKeyDown(sf::Key::Left) && !input.IsKeyDown(sf::Key::Right))
        {
           player.MoveLeft(level, app.GetFrameTime());
        }

        if(input.IsKeyDown(sf::Key::Right) && !input.IsKeyDown(sf::Key::Left))
        {
            player.MoveRight(level, app.GetFrameTime());
        }

        if(input.IsKeyDown(sf::Key::Space))
        {
            player.Amplify();
        }

    for(int direction = 0 ; direction < 4 ; direction++)
    {
        if(level.ChangeMapDirection(player.GetPosExtremeBody(direction).x, player.GetPosExtremeBody(direction).y) == direction)
        {
            level.ChangeMap(direction);
            player.ChangeMapReplacement(level, player.GetPosExtremeBody(direction));
            player.DeleteAllBullets();

            break;  // positions changes so UP and DOWN cancel each others
        }
    }
}

void Display(sf::RenderWindow &app, class Player &player, sf::Sprite cursor, class Level &level, class Horde &horde)
{
    app.Clear(sf::Color(50, 150, 50));

    level.DisplayTiles(app);

    player.Display(app);

    horde.Display(app);

    app.Draw(cursor);

    app.Display();
}


