/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef SHAPE_HXX
#define SHAPE_HXX

#include <Box2D/Box2D.h>
#include <GL/gl.h>

#include "fixturetype.cxx"

// A shape is simulated with the Box2D world, but has no gravitation
class Shape
{
    private:
        const float PI;
        // The Box2D world constraints.
        //+If these are unclear, review the Box2D documentation.

        float halfWidth;
        float halfHeight;
        float radius;
        bool circle;

        b2Body* body;
        b2Fixture* fixture;

        // Indicates whether the body is dynamic (true) or static (false)
        bool dynamic;

    public:
        // The constructor and destructor do nothing
        Shape();
        ~Shape();

        static bool Initiate();
        static void Cleanup();

        // Create this instance as the desired shape.  Should be called imediately after construction.
        //+Trouble happens if called more than once.
        bool CreateAsCircle(float x, float y, float radius, bool dynamic, b2World* world);
        bool CreateAsRectangle(float x, float y, float halfWidth, float halfHeight, float angle, bool dynamic, b2World* world);
        bool CreateAsExit(float x, float y, float radius, b2World* world);
        // Create and return pointer to desired instance.  Call as desired, but only should be used
        //+with a container such as a std::vector or std::list.
        static Shape* CreateCircle(float x, float y, float radius, bool dynamic, b2World* world);
        static Shape* CreateRectangle(float x, float y, float halfWidth, float halfHeight, float angle, bool dynamic, b2World* world);
        static Shape* CreateExit(float x, float y, float radius, b2World* world);
        // Destroy the obect from the world
        void Destroy(b2World* world);

        void Process();
        void Render();

        void Pause();
        void Resume();

        void Impulse(float x, float y);

        b2Vec2 GetPosition();
        float GetHalfWidth();
        float GetHalfHeight();
        float GetAngle();
        float GetRadius();
        bool IsDynamic();
};

#endif
