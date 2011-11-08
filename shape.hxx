/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef SHAPE_HXX
#define SHAPE_HXX

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Shape
{
    private:
        b2BodyDef* bodyDef;
        b2Body* body;
        b2Shape* shape;
        b2FixtureDef* fixtureDef;

        bool dynamic;

        sf::Shape renderShape;

    public:
        Shape();
        ~Shape();

        bool InitiateAsCircle(float x, float y, float radius, bool dynamic, b2World* world);
        bool InitiateAsRectangle(float x, float y, float halfWidth, float halfHeight, bool dynamic, b2World* world);
        void Cleanup();
        void Process(float scaleFactor);
        void Render(sf::RenderWindow* window);

        void Pause();
        void Resume();

        void Impulse(float x, float y);
};

#endif
