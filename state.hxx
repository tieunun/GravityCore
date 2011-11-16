/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef STATE_HXX
#define STATE_HXX

#include "gamecore.hxx"

class State
{
    protected:
        State()
        {
        }

        GameCore* game;
    public:

        virtual void Initiate() = 0;
        virtual void Cleanup() = 0;

        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual void HandleEvents(sf::Event* event) = 0;
        virtual void Process(float frameTime) = 0;
        virtual void Render(sf::RenderWindow* window) = 0;

        void PushState(State* state)
        {
            game->PushState(state);
        }

        void PopState()
        {
            game->PopState();
        }
};

#endif
