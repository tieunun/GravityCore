/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef SPLASH_STATE_HXX
#define SPLASH_STATE_HXX

#include <vector>
#include <SFML/Graphics.hpp>

#include "gamecore.hxx"
#include "state.hxx"
#include "mainmenustate.hxx"

class SplashState : public State
{
    private:
        std::vector<sf::Text> splashItems;
        sf::Clock timer;
        unsigned int current;
        const unsigned int length;

    public:
        SplashState(GameCore* game);

        void Initiate();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(sf::Event* event);
        void Process(float frameTime);
        void Render(sf::RenderWindow* window);
};

#endif
