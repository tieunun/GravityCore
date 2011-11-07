/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CIRCLE_HXX
#define CIRCLE_HXX

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Circle
{
    private:
        b2BodyDef* bodyDef;
        b2Body* body;
        b2CircleShape* shape;
        b2FixtureDef* fixtureDef;

        bool dynamic;

        sf::Shape renderShape;

    public:
        Circle();
        ~Circle();

        bool Initiate(float x, float y, float radius, bool dynamic, b2World* world);
        void Cleanup();
        void Process(float scaleFactor);
        void Render(sf::RenderWindow* window);

        void Pause();
        void Resume();

        void Impulse(float x, float y);
};

#endif
