/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CORE_CXX
#define CORE_CXX

#include "core.hxx"

Core::Core() : PI(3.1415926535)
{
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

    renderShape = sf::Shape::Circle(0.0f, 0.0f, radius, sf::Color::Red, 2.0f, sf::Color::Red);
    renderShape.EnableOutline(false);

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

void Core::Render(float scaleFactor, sf::RenderWindow* window)
{
    renderShape.SetScale(scaleFactor, scaleFactor);
    renderShape.SetOutlineThickness(2 / scaleFactor);
    renderShape.SetPosition(body->GetPosition().x * scaleFactor, body->GetPosition().y * scaleFactor);
    window->Draw(renderShape);
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
