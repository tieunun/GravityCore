/*
 *  Lead Coder:     Taylor C. Richberger
 */
/*
#ifndef CREDITS_STATE_HXX
#define CREDITS_STATE_HXX

#include <vector>
#include <SFML/Graphics.hpp>

#include "gamecore.hxx"
#include "state.hxx"

class CreditsState : public State
{
    private:
        // The individual items to be splashed, in order
        std::vector<sf::Text> creditsItems;
        // The current item being splashed
        unsigned int current;

    public:
        CreditsState(GameCore* game);

        void Initiate();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(sf::Event* event, sf::RenderWindow* window);
        void Process(float frameTime);
        void Render(sf::RenderWindow* window);
};

#endif
*/
