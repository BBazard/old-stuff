#include <iostream>
#include <SFML/Graphics.hpp>

#include "frame.hpp"

Frame::Frame(unsigned int numberOfFrames) : m_currentFrame(0)
{
    m_maxFrame = numberOfFrames;
}

void Frame::ActivateAnime()
{
    m_currentFrame = 1;
    m_timer.Reset();
}

void Frame::DesactivateAnime()
{
    m_currentFrame = 0;
}

bool Frame::AnimeIsOngoing()
{
    if(m_currentFrame == m_maxFrame)
        DesactivateAnime();

    if(m_currentFrame != 0)
    {
        m_currentFrame++;
        return true;
    }

    return false;
}

int Frame::GetCurrentFrame()
{
    return m_currentFrame;
}

int Frame::GetMaxFrame()
{
    return m_maxFrame;
}
