/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef PLAYER_HXX
#define PLAYER_HXX

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "fixturetype.cxx"

class Player
{
    private:
        const float PI;
        b2Body* body;
        b2Fixture* bodyFixture;
        b2Fixture* footboxFixture;

        // The number of floors contacted by the footbox, used to determine jumping.
        char floors;
        b2Vec2 gravitationalForce;

        sf::Shape renderBody;
        sf::Shape renderFootbox;

    public:
        Player();
        ~Player();

        static bool Initiate();
        static void Cleanup();

        bool Create(float x, float y, float halfWidth, float halfHeight, float mass, b2World* world);
        void Destroy(b2World* world);

        void Process();
        void Render(float timeLapse, sf::RenderWindow* window);

        void Pause();
        void Resume();

        void Impulse(float x, float y);

        bool IsGrounded();
        // if true, increase the number of floors, if false, decrease.
        void ChangeFloors(bool increment);

        void ClearGravitation();
        void AddGravitation(b2Vec2 distance, float mass);
};

#endif
