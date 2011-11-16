/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef PLAYER_CXX
#define PLAYER_CXX

#include "player.hxx"

Player::Player()
{
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

bool Player::Create(float x, float y, float halfWidth, float halfHeight, bool dynamic, b2World* world)
{
    floors = 0;

    this->dynamic = dynamic;
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->position.Set(x, y);
    b2PolygonShape* bodyShape = new b2PolygonShape();
    bodyShape->SetAsBox(halfWidth, halfHeight);

    b2PolygonShape* footboxShape = new b2PolygonShape();
    footboxShape->SetAsBox(halfWidth, (halfHeight / 10.0f), b2Vec2(0, halfHeight), 0);

    b2FixtureDef* bodyFixtureDef = new b2FixtureDef();
    bodyFixtureDef->shape = bodyShape;

    bodyFixtureDef->density = 1.0f;
    bodyFixtureDef->friction = 5.0f;
    bodyFixtureDef->restitution = 0.025f;

    b2FixtureDef* footboxFixtureDef = new b2FixtureDef();
    footboxFixtureDef->shape = footboxShape;
    footboxFixtureDef->isSensor = true;

    footboxFixtureDef->density = 0.0f;
    footboxFixtureDef->friction = 0.0f;
    footboxFixtureDef->restitution = 0.0f;

    if (dynamic)
    {
        bodyDef->type = b2_dynamicBody;
        body = world->CreateBody(bodyDef);
        body->SetFixedRotation(true);
        body->SetUserData((void*)this);
        bodyFixture = body->CreateFixture(bodyFixtureDef);
        bodyFixture->SetUserData((void*)playerBody);
        footboxFixture = body->CreateFixture(footboxFixtureDef);
        footboxFixture->SetUserData((void*)footboxSensor);
    } else
    {
        bodyDef->type = b2_staticBody;
        body = world->CreateBody(bodyDef);
        bodyFixture = body->CreateFixture(bodyShape, 0.0f);
    }

    renderBody = sf::Shape::Rectangle(0.0f, 0.0f, halfWidth * 2.0f, halfHeight * 2.0f, sf::Color(255, 0, 0, 100), 2.0f, sf::Color::Red);
    renderBody.SetOrigin(halfWidth, halfHeight);
    renderBody.EnableOutline(false);

    renderFootbox = sf::Shape::Rectangle(0.0f, 0.0, halfWidth * 2.0f, (halfHeight / 10.0f) * 2.0f, sf::Color(0, 255, 0, 255), 2.0f, sf::Color(0, 255, 0, 255));
    renderFootbox.SetOrigin(halfWidth, (halfHeight / 10.0f));
    renderFootbox.EnableOutline(true);
    renderFootbox.EnableFill(false);

    delete bodyDef;
    delete bodyFixtureDef;
    delete footboxFixtureDef;
    delete bodyShape;
    delete footboxShape;
    return (true);
}

void Player::Destroy(b2World* world)
{
    world->DestroyBody(body);
}

void Player::Process()
{

}

void Player::Render(float scaleFactor, sf::RenderWindow* window)
{
    renderBody.SetScale(scaleFactor, scaleFactor);
    renderBody.SetOutlineThickness(2 / scaleFactor);
    renderBody.SetPosition(
        body->GetWorldPoint(((b2PolygonShape*)bodyFixture->GetShape())->m_centroid).x * scaleFactor,
        body->GetWorldPoint(((b2PolygonShape*)bodyFixture->GetShape())->m_centroid).y * scaleFactor);
    renderBody.SetRotation(body->GetAngle() * 180.0f / 3.1415926535);

    renderFootbox.SetScale(scaleFactor, scaleFactor);
    renderFootbox.SetOutlineThickness(2 / scaleFactor);
    // Gets the shape of the fixture, casts it to b2PolygonShape*, and recieves the
    //+m_centroid member, then translates it to the world's point, and scales it
    renderFootbox.SetPosition(
        body->GetWorldPoint(((b2PolygonShape*)footboxFixture->GetShape())->m_centroid).x * scaleFactor,
        body->GetWorldPoint(((b2PolygonShape*)footboxFixture->GetShape())->m_centroid).y * scaleFactor);
    renderFootbox.SetRotation(body->GetAngle() * 180.0f / 3.1415926535);
    window->Draw(renderBody);
    window->Draw(renderFootbox);
}

void Player::Pause()
{
}

void Player::Resume()
{

}

void Player::Impulse(float x, float y)
{
    body->SetLinearVelocity(b2Vec2(x, y) + body->GetLinearVelocity());
}

bool Player::GetGrounded()
{
    return ((bool)floors);
}

void Player::ChangeFloors(bool increment)
{
    if (increment)
    {
        floors++;
    } else
    {
        floors--;
    }
    if (floors < 0)
    {
        floors = 0;
    }
}
#endif
