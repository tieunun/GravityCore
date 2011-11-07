/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef RECTANGLE_CXX
#define RECTANGLE_CXX

#include "rectangle.hxx"

Rectangle::Rectangle()
{
}

Rectangle::~Rectangle()
{
}

bool Rectangle::Initiate(float x, float y, float halfWidth, float halfHeight, bool dynamic, b2World* world)
{
    this->dynamic = dynamic;
    bodyDef = new b2BodyDef;
    bodyDef->position.Set(x, y);

    shape = new b2PolygonShape();
    shape->SetAsBox(halfWidth, halfHeight);

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

void Rectangle::Cleanup()
{

}

void Rectangle::Process(float scaleFactor)
{
    renderShape.SetScale(scaleFactor, scaleFactor);
    renderShape.SetOutlineThickness(2 / scaleFactor);
    renderShape.SetPosition(body->GetPosition().x * scaleFactor, body->GetPosition().y * scaleFactor);
}

void Rectangle::Render(sf::RenderWindow* window)
{
    window->Draw(renderShape);
}

void Rectangle::Pause()
{
}

void Rectangle::Resume()
{

}

#endif
