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
        b2Body* body;
        b2Fixture* bodyFixture;
        b2Fixture* footboxFixture;



        bool dynamic;
        char floors;

        sf::Shape renderBody;
        sf::Shape renderFootbox;

    public:
        Player();
        ~Player();

        static bool Initiate();
        static void Cleanup();

        bool Create(float x, float y, float width, float height, bool dynamic, b2World* world);
        void Destroy(b2World* world);

        void Process();
        void Render(float timeLapse, sf::RenderWindow* window);

        void Pause();
        void Resume();

        void Impulse(float x, float y);

        bool GetGrounded();
        // if true, increase the number of floors, if false, decrease.
        void ChangeFloors(bool increment);
};

#endif
