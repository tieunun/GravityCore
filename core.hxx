/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CORE_HXX
#define CORE_HXX

#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>

class State;

class Core
{
    private:
        int WINDOWWIDTH;
        int WINDOWHEIGHT;
        std::string TITLE;

        std::vector<State*> states;

        sf::RenderWindow* window;
        sf::Event* event;

    public:
        Core(std::string);
        ~Core();

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
