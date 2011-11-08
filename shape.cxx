/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef SHAPE_CXX
#define SHAPE_CXX

#include "shape.hxx"

Shape::Shape()
{
}

Shape::~Shape()
{
}

bool Shape::InitiateAsCircle(float x, float y, float radius, bool dynamic, b2World* world)
{
    this->dynamic = dynamic;
    bodyDef = new b2BodyDef;
    bodyDef->position.Set(x, y);

    shape = new b2CircleShape();
    ((b2CircleShape*)shape)->m_radius = radius;

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

    renderShape = sf::Shape::Circle(0.0f, 0.0f, radius, sf::Color(255, 0, 0, 100), 2.0f, sf::Color::Red);
    renderShape.EnableOutline(false);
    return (true);
}

bool Shape::InitiateAsRectangle(float x, float y, float halfWidth, float halfHeight, bool dynamic, b2World* world)
{
    this->dynamic = dynamic;
    bodyDef = new b2BodyDef;
    bodyDef->position.Set(x, y);

    shape = new b2PolygonShape();
    ((b2PolygonShape*)shape)->SetAsBox(halfWidth, halfHeight);

    fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;

    fixtureDef->density = 1.0f;
    fixtureDef->friction = 0.3f;

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

    renderShape = sf::Shape::Rectangle(0, 0, 2.0f * halfWidth, 2.0f * halfHeight, sf::Color(0, 255, 0, 100), 2.0, sf::Color::Green);
    renderShape.SetOrigin(halfWidth, halfHeight);
    renderShape.EnableOutline(false);
    return (true);
}

void Shape::Cleanup()
{

}

void Shape::Process(float scaleFactor)
{
    renderShape.SetScale(scaleFactor, scaleFactor);
    renderShape.SetOutlineThickness(2 / scaleFactor);
    renderShape.SetPosition(body->GetPosition().x * scaleFactor, body->GetPosition().y * scaleFactor);
}

void Shape::Render(sf::RenderWindow* window)
{
    window->Draw(renderShape);
}

void Shape::Pause()
{
}

void Shape::Resume()
{

}

void Shape::Impulse(float x, float y)
{
    body->SetLinearVelocity(b2Vec2(x, y) + body->GetLinearVelocity());
}

#endif
