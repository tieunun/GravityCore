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
        // The individual items to be splashed, in order
        std::vector<sf::Text> splashItems;
        // The timer that manages splash length
        sf::Clock timer;
        // The current item being splashed
        unsigned int current;
        // The time, in miliseconds, for each item to be splashed
        const unsigned int length;

    public:
        SplashState(GameCore* game);

        void Initiate();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(sf::Event* event, sf::RenderWindow* window);
        void Process(float frameTime);
        void Render(sf::RenderWindow* window);
};

#endif
