/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CORE_HXX
#define CORE_HXX

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Core
{
    private:
        float mass;
        const float PI;
        b2Body* body;
        b2Fixture* fixture;

        sf::Shape renderShape;

    public:
        Core();
        ~Core();

        bool Create(float x, float y, float radius, float mass, b2World* world);
        static Core* CreateCore(float x, float y, float radius, float mass, b2World* world);

        void Cleanup();
        void Process();
        void Render(float scaleFactor, sf::RenderWindow* window);

        void Pause();
        void Resume();

        b2Vec2 GetPosition();
        float GetMass();
};

#endif
