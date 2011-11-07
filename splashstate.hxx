/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef SPLASH_STATE_HXX
#define SPLASH_STATE_HXX

#include "core.hxx"
#include "state.hxx"

class SplashState : public State
{
    private:
        std::vector<sf::Text> splashItems;
        sf::Clock timer;
        int current;
        int length;

    public:
        SplashState(Core* game);

        void Initiate();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(sf::Event* event);
        void Process(float frameTime);
        void Render(sf::RenderWindow* window);
};

#endif
