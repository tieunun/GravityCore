/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef GAMECORE_HXX
#define GAMECORE_HXX

#include <vector>
#include <SFML/Graphics.hpp>

class State;

class GameCore
{
    private:
        int WINDOWWIDTH;
        int WINDOWHEIGHT;
        std::string TITLE;

        // The container of states, used in this case as a stack.
        //+This is only implemented as a vector for specialized rendering ability.
        std::vector<State*> states;

        // The window which handles all input and output
        sf::RenderWindow* window;
        sf::Event* event;

    public:
        GameCore(std::string);
        ~GameCore();

        // The game loop, called from int main() in main.cxx
        int Run();

        // Nearly all of these simply call the corrisponding function of the state on top of the stack
        bool Initiate();
        void Cleanup();
        void HandleEvents();
        void Process();
        void Render();

        // Pushes a new state on top of the stack,
        //+Only called from within a state
        void PushState(State* state);
        // Pops a the top state off of the stack,
        //+Only called from within a state
        void PopState();

        // Returns the second state from the top of the stack.
        //+Do not try to use in the members of a hidden state that will be accessed through this method
        //+(do not try to access past the second state from the top)
        // Also, do not use in the first state on the stack, or the game will crash
        State* GetHiddenState();

        int GetWidth();
        int GetHeight();
};

#endif
