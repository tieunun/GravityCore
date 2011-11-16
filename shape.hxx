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
        b2Body* body;
        b2Fixture* fixture;

        bool dynamic;

        sf::Shape renderShape;

    public:
        Shape();
        ~Shape();

        bool CreateAsCircle(float x, float y, float radius, bool dynamic, b2World* world);
        bool CreateAsRectangle(float x, float y, float halfWidth, float halfHeight, bool dynamic, b2World* world);
        static Shape* CreateCircle(float x, float y, float radius, bool dynamic, b2World* world);
        static Shape* CreateRectangle(float x, float y, float halfWidth, float halfHeight, bool dynamic, b2World* world);

        void Cleanup();
        void Process();
        void Render(float scaleFactor, sf::RenderWindow* window);

        void Pause();
        void Resume();

        void Impulse(float x, float y);
};

#endif
