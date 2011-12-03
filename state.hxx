/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef STATE_HXX
#define STATE_HXX

#include "gamecore.hxx"

// The class from which all the state classes are inherited
class State
{
    protected:
        State()
        {
        }

        // Each state inherits the main GameCore object, in order to manage states
        GameCore* game;
    public:

        // To be called on each state's creation
        virtual void Initiate() = 0;
        // To be called on each state's distruction
        virtual void Cleanup() = 0;

        // To be called when a state has another pushed on top of it
        virtual void Pause() = 0;
        // To be called when a state becomes the top of the stack again
        virtual void Resume() = 0;

        // To be called when an event must be handled
        virtual void HandleEvents(sf::Event* event, sf::RenderWindow* window) = 0;
        // To be called in order to run processing maintenance within a frame
        virtual void Process(float frameTime) = 0;
        // To be called in order to render the state
        virtual void Render(sf::RenderWindow* window) = 0;

        // Pushes a new state on top of the stack,
        //+typically called by this->PushState(new [statename](game));
        void PushState(State* state)
        {
            game->PushState(state);
        }

        // Pops a the top state off of the stack,
        //+typically called by this->PushState(new [statename](game));
        //+The calling state usually destroys itself with this
        void PopState()
        {
            game->PopState();
        }

        void PopStates(unsigned int i)
        {
            game->PopStates(i);
        }
};

#endif
