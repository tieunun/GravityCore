/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef PLAYER_CXX
#define PLAYER_CXX

#include "player.hxx"

Player::Player() : PI(3.1415926535)
{
    body = NULL;
    bodyFixture = NULL;
    footboxFixture = NULL;
}

Player::~Player()
{
}

bool Player::Initiate()
{
    return (true);
}

void Player::Cleanup()
{
}

bool Player::Create(float x, float y, float halfWidth, float halfHeight, float mass, b2World* world)
{
    this->halfWidth = halfWidth;
    this->halfHeight = halfHeight;

    movementStatus = none;
    jumping = true;
    exited = false;
    dead = false;

    gravitationalForce.x = 0;
    gravitationalForce.y = 0;

    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->position.Set(x, y);
    // Used to prevent a player from spiraling out to space
    bodyDef->linearDamping = 0.1f;
    bodyDef->type = b2_dynamicBody;
    bodyDef->userData = (void*)this;
    b2PolygonShape* bodyShape = new b2PolygonShape();
    bodyShape->SetAsBox(halfWidth, halfHeight);

    b2PolygonShape* footboxShape = new b2PolygonShape();
    footboxShape->SetAsBox(halfWidth, (halfHeight / 10.0f), b2Vec2(0, halfHeight), 0);

    b2FixtureDef* bodyFixtureDef = new b2FixtureDef();
    bodyFixtureDef->shape = bodyShape;

    bodyFixtureDef->density = mass / (halfWidth * halfHeight * 4.0f);
    bodyFixtureDef->friction = 5.0f;
    bodyFixtureDef->restitution = 0.05f;
    bodyFixtureDef->userData = (void*)playerFixture;

    b2FixtureDef* footboxFixtureDef = new b2FixtureDef();
    footboxFixtureDef->shape = footboxShape;
    footboxFixtureDef->isSensor = true;

    footboxFixtureDef->density = 0.0f;
    footboxFixtureDef->friction = 0.0f;
    footboxFixtureDef->restitution = 0.0f;
    footboxFixtureDef->userData = (void*)footboxSensor;

    body = world->CreateBody(bodyDef);
    body->SetFixedRotation(true);
    bodyFixture = body->CreateFixture(bodyFixtureDef);
    footboxFixture = body->CreateFixture(footboxFixtureDef);

    delete bodyDef;
    delete bodyFixtureDef;
    delete footboxFixtureDef;
    delete bodyShape;
    delete footboxShape;
    return (true);
}

void Player::Destroy(b2World* world)
{
    if (body)
    {
        world->DestroyBody(body);
        body = NULL;
        bodyFixture = NULL;
        footboxFixture = NULL;
        floors.clear();
    }
}

void Player::Process()
{
    // Apply gravity
    body->ApplyForceToCenter(gravitationalForce);
    // Set the body's angle, relative to local gravitation
    if (IsGrounded())
    {

    } else
    {
        body->SetTransform(body->GetWorldCenter(), atan2(-gravitationalForce.x, gravitationalForce.y));
    }

    switch (movementStatus)
    {
        case left:
            if (!jumping)
            {
                ApplyRelativeHorizontalMotion(-5);
            }
            break;
        case right:
            if (!jumping)
            {
                ApplyRelativeHorizontalMotion(5);
            }
            break;
        case none:
            break;
        default:
            break;
    }

    if (jumping)
    {
    }
}

void Player::Render()
{
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(body->GetPosition().x, body->GetPosition().y, 0.0f);
    glRotatef(body->GetAngle() * 180.0f / PI, 0.0f, 0.0f, 1.0f);
    glScalef(halfWidth, halfHeight, 1.0f);

    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
    glEnd();

    glPopMatrix();
}

void Player::Pause()
{
}

void Player::Resume()
{

}

void Player::ApplyRelativeImpulse(float x, float y)
{
    // Create an impluse, relative to the body's current angle
    body->SetLinearVelocity(body->GetWorldVector(b2Vec2(x, y)) + body->GetLinearVelocity());
}

void Player::ApplyRelativeForce(float x, float y)
{
    // Create an impluse, relative to the body's current angle
    body->ApplyForceToCenter(body->GetWorldVector(b2Vec2(x, y)));
}

void Player::ApplyRelativeHorizontalMotion(float vel)
{
    // Create an impluse, relative to the body's current angle
    body->SetLinearVelocity(body->GetWorldVector(b2Vec2((vel + body->GetLocalVector(body->GetLinearVelocity()).x) / 2.0f, 0)));
}

void Player::StopVelocity()
{
    body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
}

void Player::MoveLeft()
{
    movementStatus = left;
}

void Player::MoveRight()
{
    movementStatus = right;
}

void Player::StopMoving()
{
    movementStatus = none;
}

void Player::Jump()
{
    ApplyRelativeImpulse(0, -10);
    jumping = true;
}

void Player::Land()
{
    jumping = false;
}

void Player::Exit()
{
    exited = true;
}

void Player::Die()
{
    dead = true;
}

bool Player::IsGrounded()
{
    return ((bool)floors.size());
}

bool Player::IsExited()
{
    return (exited);
}

bool Player::IsDead()
{
    return (dead);
}

void Player::AddFloor(Shape* floor)
{
    floors.push_back(floor);
}

void Player::RemoveFloor(Shape* floor)
{
    for (unsigned int i = 0; i < floors.size(); i++)
    {
        if (floor == floors[i])
        {
            floors.erase(floors.begin() + i);
            break;
        }
    }

    if (floors.size() <= 0)
    {
        jumping = true;
    }
}

void Player::ClearGravitation()
{
    gravitationalForce.SetZero();
}

void Player::AddGravitation(b2Vec2 distance, float mass)
{
    gravitationalForce += (mass * body->GetMass()) / (distance.LengthSquared() * distance.LengthSquared()) * distance;
}

float Player::GetAngle()
{
    return (body->GetAngle());
}

float Player::GetGravityAngle()
{
    return (atan2(-gravitationalForce.x, gravitationalForce.y));
}

b2Vec2 Player::GetPosition()
{
    return (body->GetWorldCenter());
}

float Player::GetMass()
{
    return (body->GetMass());
}

float Player::GetHalfWidth()
{
    return (halfWidth);
}

float Player::GetHalfHeight()
{
    return (halfHeight);
}
#endif
