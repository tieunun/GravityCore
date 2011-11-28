/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef MAINGAME_STATE_HXX
#define MAINGAME_STATE_HXX

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>

#include "gamecore.hxx"
#include "state.hxx"
#include "player.hxx"
#include "core.hxx"
#include "shape.hxx"
#include "contactlistener.hxx"
#include "pausemenustate.hxx"

class MainGameState : public State
{
    private:
        // Duh, the constant Pi
        const float PI;
        b2World* world;
        // Used for callback, mostly to manage the ability to jump
        ContactListener* contactListener;

        // Used to manage timesteps
        int32 velocityIterations;
        int32 positionIterations;

        // The main view, used for main rendering
        sf::View* playerView;
        // The minimap view, used to render the small map, which keeps orientation constant
        sf::View* minimapView;
        // The box that the minimap sits in
        sf::Shape* minimapBox;
        sf::Music* bgm;

        Player* player;
        std::vector<Core*> cores;
        std::vector<Shape*> shapes;

        // The gravity is constantly (0, 0) here as it is handled manually
        b2Vec2 gravity;
        bool doSleep;
        // These variables only influence rendering
        float scaleFactor;
        float minimapScaleFactor;

    public:
        MainGameState(GameCore* game);

        void Initiate();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(sf::Event* event, sf::RenderWindow* window);
        void Process(float frameTime);
        void Render(sf::RenderWindow* window);
};

#endif

