/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef RECTANGLE_HXX
#define RECTANGLE_HXX

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Rectangle
{
    private:
        b2BodyDef* bodyDef;
        b2Body* body;
        b2PolygonShape* shape;
        b2FixtureDef* fixtureDef;

        bool dynamic;

        sf::Shape renderShape;

    public:
        Rectangle();
        ~Rectangle();

        bool Initiate(float x, float y, float halfWidth, float halfHeight, bool dynamic, b2World* world);
        void Cleanup();
        void Process(float scaleFactor);
        void Render(sf::RenderWindow* window);

        void Pause();
        void Resume();
};

#endif

