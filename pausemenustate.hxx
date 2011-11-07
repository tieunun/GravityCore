/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef PAUSEMENU_STATE_HXX
#define PAUSEMENU_STATE_HXX

#include "core.hxx"
#include "state.hxx"

class PauseMenuState : public State
{
    private:
        std::vector<sf::Text> displayItems;
        int current;

    public:
        PauseMenuState(Core* game);

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
