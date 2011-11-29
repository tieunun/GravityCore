/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef PLAYER_HXX
#define PLAYER_HXX

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "fixturetype.cxx"

class Player
{
    private:
        // Duh, the constant Pi
        const float PI;
        // The Box2D world constraints.
        //+If these are unclear, review the Box2D documentation.
        enum MovementStatus
        {
            runningRight = 0,
            runningLeft,
            standingRight,
            standingLeft,
            jumpingRight,
            jumpingLeft,
        } movementStatus;

        b2Body* body;
        b2Fixture* bodyFixture;
        b2Fixture* footboxFixture;

        // The number of floors contacted by the footbox, used to determine jumping.
        char floors;
        // The force of gravity, recalculated and reapplied each frame.
        b2Vec2 gravitationalForce;

        // The SFML constraints for rendering
        sf::Shape renderBody;
        sf::Shape renderFootbox;

        sf::Sprite sprite;
        sf::Texture standR;
        sf::Texture runR;
        sf::Texture jumpR;
        sf::IntRect subRect;

        sf::Clock spriteTimer;

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
        void Render(float timeLapse, sf::RenderWindow* window);

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

        bool IsGrounded();
        // if true, increase the number of floors, if false, decrease.
        void ChangeFloors(bool increment);
        void ClearGravitation();
        void AddGravitation(b2Vec2 distance, float mass);
        float GetAngle();
        b2Vec2 GetPosition();
        float GetMass();
};

#endif
