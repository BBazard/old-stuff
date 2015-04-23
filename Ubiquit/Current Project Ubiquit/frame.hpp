#ifndef H_CLASS_FRAME
#define H_CLASS_FRAME

class Frame
{
    public :

        Frame(unsigned int numberOfFrames = 1);

        void ActivateAnime();

        void DesactivateAnime();

        bool AnimeIsOngoing();

        int GetCurrentFrame();

        int GetMaxFrame();

    private :

        unsigned int m_currentFrame;
        unsigned int m_maxFrame;
        sf::Clock m_timer;
};

#endif



