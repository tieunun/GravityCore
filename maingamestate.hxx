/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef MAINGAME_STATE_HXX
#define MAINGAME_STATE_HXX

#include <vector>
#include <cmath>
#include <fstream>
#include <Box2D/Box2D.h>

#include "gamecore.hxx"
#include "state.hxx"
#include "player.hxx"
#include "core.hxx"
#include "shape.hxx"
#include "contactlistener.hxx"
#include "pausemenustate.hxx"
#include "event.cxx"

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

        Player* player;
        std::vector<Core*> cores;
        std::vector<Shape*> shapes;
        Shape* exit;

        std::vector<std::string> stages;
        unsigned short int currentStage;

        // The gravity is constantly (0, 0) here as it is handled manually
        b2Vec2 gravity;
        bool doSleep;
        // These variables only influence rendering
        float scaleFactor;
        float minimapScaleFactor;

    public:
        MainGameState(GameCore* game);

        void Create();
        void Destroy();

        void ClearStage();
        void LoadStage(std::string fileName);
        void LoadStage(int stageNumber);
        void LoadNextStage();
        void SaveStage(std::string fileName);

        void Pause();
        void Resume();

        void HandleEvents(GLFWEvent* event);
        void Process(float frameTime);
        void Render();
};

#endif

