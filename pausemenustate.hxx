/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef PAUSEMENU_STATE_HXX
#define PAUSEMENU_STATE_HXX

#include <vector>
#include <SFML/Graphics.hpp>

#include "gamecore.hxx"
#include "state.hxx"

class PauseMenuState : public State
{
    private:
        // Items to be displayed
        std::vector<sf::Text> displayItems;
        // Currently highlighted item
        unsigned short int current;

        // The box that the pause menu sits on, to differentiate from gameplay
        sf::Shape* menuBox;

    public:
        PauseMenuState(GameCore* game);

        void Initiate();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(sf::Event* event, sf::RenderWindow* window);
        void Process(float frameTime);
        void Render(sf::RenderWindow* window);

        void NextItem();
        void PreviousItem();
        void SelectCurrent();
};

#endif
