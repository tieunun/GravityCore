/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef MAINGAME_STATE_HXX
#define MAINGAME_STATE_HXX

#include <vector>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "gamecore.hxx"
#include "state.hxx"
#include "player.hxx"
#include "core.hxx"
#include "contactlistener.hxx"
#include "pausemenustate.hxx"

class MainGameState : public State
{
    private:
        const float PI;
        b2World* world;
        ContactListener* contactListener;
        float32 timeStep;
        int32 velocityIterations;
        int32 positionIterations;

        sf::View* playerView;
        sf::View* minimapView;

        Player* player;
        std::vector<Core*> cores;

        b2Vec2 gravity;
        bool doSleep;
        float scaleFactor;
        float minimapScaleFactor;

    public:
        MainGameState(GameCore* game);

        void Initiate();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(sf::Event* event);
        void Process(float frameTime);
        void Render(sf::RenderWindow* window);
};

#endif

