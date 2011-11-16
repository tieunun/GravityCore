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

        std::vector<State*> states;

        sf::RenderWindow* window;
        sf::Event* event;

    public:
        GameCore(std::string);
        ~GameCore();

        int Run();
        bool Initiate();
        void Cleanup();
        void HandleEvents();
        void Process();
        void Render();

        void PushState(State* state);
        void PopState();

        int GetWidth();
        int GetHeight();
};

#endif
