/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef STATE_HXX
#define STATE_HXX

#include "gamecore.hxx"

class State
{
    protected:

        GameCore* game;

    public:
        State()
        {
        }

        virtual ~State()
        {
        }

        virtual void Create() = 0;
        virtual void Destroy() = 0;

        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual void HandleEvents(GLFWEvent* event) = 0;
        virtual void Process(float frameTime) = 0;
        virtual void Render() = 0;

        void PushState(State* state)
        {
            game->PushState(state);
        }

        void PopState()
        {
            game->PopState();
        }

        void PopStates(unsigned int num)
        {
            game->PopStates(num);
        }

        void SendResizeEvent()
        {
            game->SendResizeEvent();
        }
};

#endif
