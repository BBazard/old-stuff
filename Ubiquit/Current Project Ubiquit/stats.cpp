#include "stats.hpp"
#include "constante.hpp"

Stats::Stats() : m_gold(0), m_xpEarned(0), m_xpRemaining(0)
{
    Initialize(m_life, "datas/LifeBar.bmp");
    Initialize(m_power, "datas/PowerBar.bmp");
    Initialize(m_xp, "datas/XpBar.bmp");

    m_life.stats.max = 1000;
    m_power.stats.max = 2000;
    m_xp.stats.max = 1000;

    m_life.stats.current = 600;
    m_power.stats.current = 2000;
    m_xp.stats.current = 0;
}

void Stats::Initialize(BarStruct &bar, std::string nameOfFile)
{
    if(!bar.image.LoadFromFile(nameOfFile))
        std::cerr << "Cannot open the file : " << nameOfFile << " !" << std::endl;

    else
    {
        bar.image.SetSmooth(false);

        int widthBar = bar.image.GetWidth();
        int heightBar = bar.image.GetHeight()/2;

        bar.sprite.empty.SetImage(bar.image);
        bar.sprite.full.SetImage(bar.image);

        bar.sprite.empty.SetSubRect(sf::IntRect(0, 0, widthBar, heightBar));
        bar.sprite.full.SetSubRect(sf::IntRect(0, heightBar, widthBar, heightBar*2));
    }
}

void Stats::DisplayStatsBars(sf::RenderWindow &app)
{
    RawBar(m_power);
    RawBar(m_life);

    DisplayStatsBar(m_power, app, 0, 575);
    DisplayStatsBar(m_life, app, 500, 575);
    DisplayStatsBar(m_xp, app, 500, 585);
}

void Stats::DisplayStatsBar(BarStruct &bar, sf::RenderWindow &app, int X, int Y)
{
    bar.sprite.empty.SetPosition(X, Y);
    bar.sprite.full.SetPosition(X, Y);

    app.Draw(bar.sprite.empty);
    app.Draw(bar.sprite.full);
}

void Stats::RawBar(BarStruct &bar)
{
    int widthBar = bar.image.GetWidth();
    int heightBar = bar.image.GetHeight()/2;

    bar.sprite.full.SetSubRect(sf::IntRect(0, heightBar, (widthBar*bar.stats.current/bar.stats.max), heightBar*2));
}

void Stats::RegeneratePower()
{
    if(m_power.stats.current+PowerPrice::regeneration <= m_power.stats.max)
        m_power.stats.current += PowerPrice::regeneration;

    if(m_power.stats.current > m_power.stats.max)
        m_power.stats.current = m_power.stats.max;
}

bool Stats::Use(int what, const unsigned int action)
{
    bool canUse = CanUse(what, action);

        if(what == LIFE)
            UseIfPossible(&m_life.stats.current, action);

        if(what == POWER)
            UseIfPossible(&m_power.stats.current, action);

        if(what == XP)
            UseIfPossible(&m_xp.stats.current, action);

        if(what == GOLD)
            UseIfPossible(& m_gold, action);

    return canUse;
}

void Stats::UseIfPossible(unsigned int *attribute, const unsigned int action)
{
    if(*attribute >= action)
        *attribute -= action;
}

bool Stats::CanUse(int what, const unsigned int action)
{
    if(what == LIFE)
        return(m_life.stats.current >= action);

    if(what == POWER)
        return(m_power.stats.current >= action);

    if(what == XP)
        return(m_xp.stats.current >= action);

    if(what == GOLD)
        return(m_gold >= action);

    std::cerr << "Error in Stats::CanUse : what = " << what << std::endl;
    return false;
}

