/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef MAINGAME_STATE_HXX
#define MAINGAME_STATE_HXX

#include <vector>

#include <Box2D/Box2D.h>

#include "core.hxx"
#include "state.hxx"
#include "circle.hxx"
#include "player.hxx"
#include "rectangle.hxx"
#include "contactlistener.hxx"

class MainGameState : public State
{
    private:
        b2World* world;
        ContactListener* contactListener;
        float32 timeStep;
        int32 velocityIterations;
        int32 positionIterations;

        Player* player;
        Rectangle* ground;
        Rectangle* ground2;
        std::vector<Circle*> circles;

        b2Vec2 gravity;
        bool doSleep;
        float scaleFactor;

    public:
        MainGameState(Core* game);

        void Initiate();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(sf::Event* event);
        void Process(float frameTime);
        void Render(sf::RenderWindow* window);
};

#endif

