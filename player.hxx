/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef PLAYER_HXX
#define PLAYER_HXX

#include <Box2D/Box2D.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <iostream>

#include "fixturetype.cxx"
#include "shape.hxx"

class Player
{
    private:
        // Duh, the constant Pi
        const float PI;
        // The Box2D world constraints.
        //+If these are unclear, review the Box2D documentation.
        enum MovementStatus
        {
            right = 0,
            left,
            none
        } movementStatus;

        enum
        {
            CUBE,
            MAN,
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

        GLfloat scaleMatrix[16];
        GLfloat rotationMatrix[16];

        bool jumping;
        bool exited;
        bool dead;

        b2Body* body;
        b2Fixture* bodyFixture;
        b2Fixture* footboxFixture;

        // The number of floors contacted by the footbox, used to determine jumping.
        std::vector<Shape*> floors;
        // The force of gravity, recalculated and reapplied each frame.
        b2Vec2 gravitationalForce;

        float halfWidth;
        float halfHeight;

    public:
        Player();
        ~Player();

        // Used to initiate and cleanup the class, namely load and then dispose of any external
        //+files, such as textures
        static bool Initiate();
        static void Cleanup();

        // Initialize the player.  Do not use more than once for the same instance without first destroying.
        bool Create(float x, float y, float halfWidth, float halfHeight, float mass, b2World* world);
        // Destroy the object from the world.  Can be dangerous.
        void Destroy(b2World* world);

        void Process();
        void Render();

        void Pause();
        void Resume();

        // Transformations relative to player's angle
        void ApplyRelativeImpulse(float x, float y);
        void ApplyRelativeForce(float x, float y);
        void ApplyRelativeHorizontalMotion(float vel);
        // Set the player's current velocity equal to 0, halting all motion temporarily.
        void StopVelocity();

        void MoveLeft();
        void MoveRight();
        void StopMoving();
        void Jump();
        void Land();
        void Exit();
        void Die();

        bool IsGrounded();
        bool IsExited();
        bool IsDead();
        // if true, increase the number of floors, if false, decrease.
        void AddFloor(Shape* floor);
        void RemoveFloor(Shape* floor);
        void ClearGravitation();
        void AddGravitation(b2Vec2 distance, float mass);
        float GetAngle();
        float GetGravityAngle();
        b2Vec2 GetPosition();
        float GetMass();
        float GetHalfWidth();
        float GetHalfHeight();
};

#endif
