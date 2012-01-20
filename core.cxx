/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CORE_CXX
#define CORE_CXX

#include "core.hxx"

Core::Core() : PI(3.1415926535)
{
    body = NULL;
    fixture = NULL;
}

Core::~Core()
{
}

bool Core::Initiate()
{
    return (true);
}

void Core::Cleanup()
{

}

bool Core::Create(float x, float y, float radius, float mass, b2World* world)
{
    this->mass = mass;
    this->radius = radius;
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->position.Set(x, y);
    bodyDef->type = b2_staticBody;
    bodyDef->userData = (void*)this;

    b2CircleShape* shape = new b2CircleShape();
    shape->m_radius = radius;

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;
    fixtureDef->density = mass / (radius * radius * PI);
    fixtureDef->friction = 0.1f;
    fixtureDef->restitution = 0.0f;
    fixtureDef->userData = (void*)massiveFixture;

    body = world->CreateBody(bodyDef);
    fixture = body->CreateFixture(fixtureDef);

    delete (bodyDef);
    delete (fixtureDef);
    delete (shape);
    return (true);
}

Core* Core::CreateCore(float x, float y, float radius, float mass, b2World* world)
{
    Core* output = new Core();
    output->Create(x, y, radius, mass, world);
    return (output);
}

void Core::Destroy(b2World* world)
{
    if (body)
    {
        world->DestroyBody(body);
        body = NULL;
        fixture = NULL;
    }
}

void Core::Process()
{
}

void Core::Render()
{
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(body->GetPosition().x, body->GetPosition().y, 0.0f);
    glScalef(radius, radius, radius);

    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
    glEnd();

    glPopMatrix();
}

void Core::Pause()
{
}

void Core::Resume()
{

}

b2Vec2 Core::GetPosition()
{
    return (body->GetWorldCenter());
}

float Core::GetMass()
{
    return (mass);
}

float Core::GetRadius()
{
    return (radius);
}

#endif
