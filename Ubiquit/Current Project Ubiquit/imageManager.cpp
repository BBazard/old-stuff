#include "imageManager.hpp"

ImageManager::ImageManager()
{
    AbstractLoadFromFile(m_tilsetMap, "Datas/tilesetMap.bmp");
    AbstractLoadFromFile(m_tilsetWorld, "Datas/tilesetWorld.bmp");

    AbstractLoadFromFile(m_enemy1, "Datas/zombie.bmp");
}

void ImageManager::GetSpriteTiles(sf::Sprite &sprite, int tile, int modeSelection)
{
    if(modeSelection == MAP)
    {
        sprite.SetImage(m_tilsetMap);
        sprite.SetSubRect(sf::IntRect(TILE_WIDTH*tile, 0, TILE_WIDTH*(tile+1), TILE_HEIGHT));
    }

    else if(modeSelection == WORLD)
    {
        sprite.SetImage(m_tilsetWorld);
        sprite.SetSubRect(sf::IntRect(TILE_WIDTH*tile, 0, TILE_WIDTH*(tile+1), TILE_HEIGHT));
    }

    else
        std::cerr << "erreur fonction ImageManager.GetSpriteTiles appelée avec modeSelection != MAP et modeSelection !=  WORLD" << std::endl;
}

void ImageManager::GetSpriteEnemy(sf::Sprite &sprite, int whichEnemy)
{
    if(whichEnemy == ENEMY1)
    {
        sprite.SetImage(m_enemy1);
        sprite.SetSubRect(sf::IntRect(1, 1, sprite.GetSize().x-1, sprite.GetSize().y-1));//To do avec le charset
    }

    else
        std::cerr << "erreur fonction ImageManager.GetSpriteEnemy appelée avec whichEnemy = " << whichEnemy << std::endl;
}

void ImageManager::AbstractLoadFromFile(sf::Image &image, std::string name, bool transparency, sf::Color color)
{
    if (!image.LoadFromFile(name))
        std::cerr << "Impossible d'ouvrir le fichier " << name << " !" << std::endl;

    if(transparency)
    {
        image.SetSmooth(false);
        image.CreateMaskFromColor(color);
    }
}
