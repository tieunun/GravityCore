/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CORE_HXX
#define CORE_HXX

#include <vector>

#include <Box2D/Box2D.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "fixturetype.cxx"

// This is not the game core, but the in-game class for the titular Gravity Cores
class Core
{
    private:
        // Duh, the constant Pi
        const static float PI = 3.1415926535;

        enum
        {
            SPHERE = 0,
            VAOCOUNT
        };
        enum
        {
            Vertices = 0,
            Normals,
            Indices,
            NumVBOs
        };
        static GLuint buffers[VAOCOUNT][NumVBOs];
        static GLuint indexCount[VAOCOUNT];
        static GLuint VAO[VAOCOUNT];

        // the mass of the core, only used for gravitation
        float mass;
        float radius;

        // The Box2D world constraints.
        //+If these are unclear, review the Box2D documentation.
        b2Body* body;
        b2Fixture* fixture;

    public:
        Core();
        ~Core();

        static bool Initiate(float radius, unsigned int stacks, unsigned int slices);
        static void Cleanup();

        // Create this instance as the desired core.
        //+Should be called imediately after construction.
        //+Trouble happens if called more than once for same object.
        bool Create(float x, float y, float radius, float mass, b2World* world);
        // Create and return pointer to desired instance.  Call as desired, but only should be used
        //+with a container, such as a std::vector or std::list.
        static Core* CreateCore(float x, float y, float radius, float mass, b2World* world);
        // Destroy the object from the world.  Can be dangerous.
        void Destroy(b2World* world);

        void Process();
        void Render();

        void Pause();
        void Resume();

        b2Vec2 GetPosition();
        float GetMass();
        float GetRadius();
};

#endif
