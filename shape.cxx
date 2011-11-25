/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef SHAPE_CXX
#define SHAPE_CXX

#include "shape.hxx"

Shape::Shape() : PI(3.1415926535)
{
}

Shape::~Shape()
{
}

bool Shape::Initiate()
{
    return (true);
}

void Shape::Cleanup()
{
}

bool Shape::CreateAsCircle(float x, float y, float radius, bool dynamic, b2World* world)
{
    this->dynamic = dynamic;
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->position.Set(x, y);

    b2CircleShape* shape = new b2CircleShape();
    shape->m_radius = radius;

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;

    fixtureDef->density = 1.0f;
    fixtureDef->friction = 1.0f;
    fixtureDef->restitution = 0.4f;

    if (dynamic)
    {
        bodyDef->type = b2_dynamicBody;
    } else
    {
        bodyDef->type = b2_staticBody;
    }
    body = world->CreateBody(bodyDef);
    fixture = body->CreateFixture(fixtureDef);

    renderShape = sf::Shape::Circle(0.0f, 0.0f, radius, sf::Color::Red, 2.0f, sf::Color::Red);
    renderShape.EnableOutline(false);

    delete (bodyDef);
    delete (fixtureDef);
    delete (shape);
    return (true);
}

bool Shape::CreateAsRectangle(float x, float y, float halfWidth, float halfHeight, float angle, bool dynamic, b2World* world)
{
    this->dynamic = dynamic;
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->position.Set(x, y);
    // Set the dynamic / static type accordingly
    bodyDef->type = (dynamic ? b2_dynamicBody : b2_staticBody);
    bodyDef->angle = angle;

    b2PolygonShape* shape = new b2PolygonShape();
    shape->SetAsBox(halfWidth, halfHeight);

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;

    fixtureDef->density = 1.0f;
    fixtureDef->friction = 0.3f;
    fixtureDef->userData = (void*)masslessFixture;

    body = world->CreateBody(bodyDef);
    fixture = body->CreateFixture(fixtureDef);

    renderShape = sf::Shape::Rectangle(0, 0, 2.0f * halfWidth, 2.0f * halfHeight, sf::Color::Red, 2.0, sf::Color::Red);
    renderShape.SetOrigin(halfWidth, halfHeight);
    renderShape.EnableOutline(false);

    delete (bodyDef);
    delete (fixtureDef);
    delete (shape);
    return (true);
}

Shape* Shape::CreateCircle(float x, float y, float radius, bool dynamic, b2World* world)
{
    Shape* output = new Shape();
    output->CreateAsCircle(x, y, radius, dynamic, world);
    return (output);
}

Shape* Shape::CreateRectangle(float x, float y, float halfWidth, float halfHeight, float angle, bool dynamic, b2World* world)
{
    Shape* output = new Shape();
    output->CreateAsRectangle(x, y, halfWidth, halfHeight, angle, dynamic, world);
    return (output);
}

void Shape::Destroy(b2World* world)
{
    world->DestroyBody(body);
}

void Shape::Process()
{
}

void Shape::Render(float scaleFactor, sf::RenderWindow* window)
{
    renderShape.SetScale(scaleFactor, scaleFactor);
    renderShape.SetOutlineThickness(2 / scaleFactor);
    renderShape.SetPosition(body->GetPosition().x * scaleFactor, body->GetPosition().y * scaleFactor);
    renderShape.SetRotation(body->GetAngle() * 180.0f / PI);
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
