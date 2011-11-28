/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef MAINMENU_STATE_HXX
#define MAINMENU_STATE_HXX

#include <SFML/Graphics.hpp>

#include "gamecore.hxx"
#include "state.hxx"
#include "maingamestate.hxx"
#include "creditsstate.hxx"

class MainMenuState : public State
{
    private:
        // Items to be displayed
        std::vector<sf::Text> displayItems;
        // Currently highlighted item
        unsigned short int current;

    public:
        MainMenuState(GameCore* game);
        //~MainMenuState();

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

