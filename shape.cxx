/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef SHAPE_CXX
#define SHAPE_CXX

#include "shape.hxx"

Shape::Shape() : PI(3.1415926535)
{
    body = NULL;
    fixture = NULL;
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
    circle = true;
    this->radius = radius;
    this->dynamic = dynamic;
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->position.Set(x, y);
    bodyDef->userData = (void*)this;

    b2CircleShape* shape = new b2CircleShape();
    shape->m_radius = radius;

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;

    fixtureDef->density = 1.0f;
    fixtureDef->friction = 1.0f;
    fixtureDef->restitution = 0.4f;
    fixtureDef->userData = (void*)masslessFixture;

    if (dynamic)
    {
        bodyDef->type = b2_dynamicBody;
    } else
    {
        bodyDef->type = b2_staticBody;
    }
    body = world->CreateBody(bodyDef);
    fixture = body->CreateFixture(fixtureDef);


    delete (bodyDef);
    delete (fixtureDef);
    delete (shape);
    return (true);
}

bool Shape::CreateAsRectangle(float x, float y, float halfWidth, float halfHeight, float angle, bool dynamic, b2World* world)
{
    circle = false;
    this->halfWidth = halfWidth;
    this->halfHeight = halfHeight;
    this->dynamic = dynamic;
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->position.Set(x, y);
    // Set the dynamic / static type accordingly
    bodyDef->type = (dynamic ? b2_dynamicBody : b2_staticBody);
    bodyDef->angle = angle;
    bodyDef->userData = (void*)this;

    b2PolygonShape* shape = new b2PolygonShape();
    shape->SetAsBox(halfWidth, halfHeight);

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;

    fixtureDef->density = 1.0f;
    fixtureDef->friction = 0.3f;
    fixtureDef->userData = (void*)masslessFixture;

    body = world->CreateBody(bodyDef);
    fixture = body->CreateFixture(fixtureDef);

    delete (bodyDef);
    delete (fixtureDef);
    delete (shape);
    return (true);
}

bool Shape::CreateAsExit(float x, float y, float radius, b2World* world)
{
    circle = true;
    this->radius = radius;
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->position.Set(x, y);
    bodyDef->userData = (void*)this;
    bodyDef->type = b2_staticBody;

    b2CircleShape* shape = new b2CircleShape();
    shape->m_radius = radius;

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;

    fixtureDef->density = 1.0f;
    fixtureDef->friction = 1.0f;
    fixtureDef->restitution = 0.4f;
    fixtureDef->isSensor = true;
    fixtureDef->userData = (void*)exitSensor;

    body = world->CreateBody(bodyDef);
    fixture = body->CreateFixture(fixtureDef);

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

Shape* Shape::CreateExit(float x, float y, float radius, b2World* world)
{
    Shape* output = new Shape();
    output->CreateAsExit(x, y, radius, world);
    return (output);
}

void Shape::Destroy(b2World* world)
{
    if (body)
    {
        world->DestroyBody(body);
        body = NULL;
        fixture = NULL;
    }
}

void Shape::Process()
{
}

void Shape::Render()
{
    glPushMatrix();
    glTranslatef(body->GetPosition().x, body->GetPosition().y, 0.0f);
    glRotatef(body->GetAngle() * 180.0f / PI, 0.0f, 0.0f, 1.0f);
    if (circle)
    {
        glColor3f(0.0f, 0.0f, 1.0f);
        glScalef(radius, radius, radius);
    } else
    {
        glColor3f(0.0f, 1.0f, 0.0f);
        glScalef(halfWidth, halfHeight, 1.0f);
    }

    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
    glEnd();

    glPopMatrix();
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

b2Vec2 Shape::GetPosition()
{
    return (body->GetPosition());
}

float Shape::GetHalfWidth()
{
    return (halfWidth);
}

float Shape::GetHalfHeight()
{
    return (halfHeight);
}

float Shape::GetAngle()
{
    return (body->GetAngle());
}

float Shape::GetRadius()
{
    return (radius);
}

bool Shape::IsDynamic()
{
    return (dynamic);
}

#endif
