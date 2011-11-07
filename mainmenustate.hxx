/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef MAINMENU_STATE_HXX
#define MAINMENU_STATE_HXX

#include "core.hxx"
#include "state.hxx"

class MainMenuState : public State
{
    private:
        std::vector<sf::Text> displayItems;
        int current;

    public:
        MainMenuState(Core* game);
        //~MainMenuState();

        void Initiate();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(sf::Event* event);
        void Process(float frameTime);
        void Render(sf::RenderWindow* window);

        void NextItem();
        void PreviousItem();
        void SelectCurrent();
};

#endif

