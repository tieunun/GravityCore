/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CIRCLE_CXX
#define CIRCLE_CXX

#include "circle.hxx"

Circle::Circle()
{
}

Circle::~Circle()
{
}

bool Circle::Initiate(float x, float y, float radius, bool dynamic, b2World* world)
{
    this->dynamic = dynamic;
    bodyDef = new b2BodyDef;
    bodyDef->position.Set(x, y);

    shape = new b2CircleShape();
    shape->m_radius = radius;

    fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;

    fixtureDef->density = 1.0f;
    fixtureDef->friction = 1.0f;
    fixtureDef->restitution = 0.4f;

    if (dynamic)
    {
        bodyDef->type = b2_dynamicBody;
        body = world->CreateBody(bodyDef);
        body->CreateFixture(fixtureDef);
    } else
    {
        bodyDef->type = b2_staticBody;
        body = world->CreateBody(bodyDef);
        body->CreateFixture(shape, 0.0f);
    }

    renderShape = sf::Shape::Circle(0.0f, 0.0f, 1, sf::Color(255, 0, 0, 100), 2.0f, sf::Color::Red);
    renderShape.EnableOutline(false);
    return (true);
}

void Circle::Cleanup()
{

}

void Circle::Process(float scaleFactor)
{
    renderShape.SetScale(scaleFactor * shape->m_radius, scaleFactor * shape->m_radius);
    renderShape.SetOutlineThickness(2 / scaleFactor / shape->m_radius);
    renderShape.SetPosition(body->GetPosition().x * scaleFactor, body->GetPosition().y * scaleFactor);
}

void Circle::Render(sf::RenderWindow* window)
{
    window->Draw(renderShape);
}

void Circle::Pause()
{
}

void Circle::Resume()
{

}

void Circle::Impulse(float x, float y)
{
    body->SetLinearVelocity(b2Vec2(x, y) + body->GetLinearVelocity());
}
#endif
