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

    floors = 0;

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

    renderBody = sf::Shape::Rectangle(0.0f, 0.0f, halfWidth * 2.0f, halfHeight * 2.0f, sf::Color(0, 0, 255, 100), 2.0f, sf::Color::Red);
    renderBody.SetOrigin(halfWidth, halfHeight);
    renderBody.EnableOutline(false);
    renderBody.EnableFill(true);

    renderFootbox = sf::Shape::Rectangle(0.0f, 0.0, halfWidth * 2.0f, (halfHeight / 10.0f) * 2.0f, sf::Color(0, 255, 0, 100), 2.0f, sf::Color::Green);
    renderFootbox.SetOrigin(halfWidth, (halfHeight / 10.0f));
    renderFootbox.EnableOutline(false);
    renderFootbox.EnableFill(true);

    standR.LoadFromFile("img/player/standr.png");
    runR.LoadFromFile("img/player/runr.png");
    jumpR.LoadFromFile("img/player/jumpr.png");

    sprite.SetTexture(standR);
    sprite.SetOrigin(32, 32);
    subRect.Height = 64;
    subRect.Width = 64;

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
    }
}

void Player::Process()
{
    // Apply gravity
    body->ApplyForceToCenter(gravitationalForce);
    // Set the body's angle, relative to local gravitation
    if (!IsGrounded())
    {
        body->SetTransform(body->GetWorldCenter(), atan2(-gravitationalForce.x, gravitationalForce.y));
    }

    switch (movementStatus)
    {
        case left:
            sprite.FlipX(true);
            if (!jumping)
            {
                ApplyRelativeHorizontalMotion(-5);
                sprite.SetTexture(runR);
                if (spriteTimer.GetElapsedTime() > 700)
                {
                     spriteTimer.Reset();
                }
                subRect.Left = (spriteTimer.GetElapsedTime() / 100) * 64;
            }
            break;
        case right:
            sprite.FlipX(false);
            if (!jumping)
            {
                ApplyRelativeHorizontalMotion(5);
                sprite.SetTexture(runR);
                if (spriteTimer.GetElapsedTime() > 700)
                {
                     spriteTimer.Reset();
                }
                subRect.Left = (spriteTimer.GetElapsedTime() / 100) * 64;
            }
            break;
        case none:
            if (!jumping)
            {
                subRect.Left = 0;
                sprite.SetTexture(standR);
            }
            break;
        default:
            break;
    }

    if (jumping)
    {
        sprite.SetTexture(jumpR);
        if (spriteTimer.GetElapsedTime() < 600)
        {
            subRect.Left = (spriteTimer.GetElapsedTime() / 100) * 64;
        } else
        {
            subRect.Left = 5 * 64;
        }
    }
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

    sprite.SetSubRect(subRect);
    sprite.SetScale(scaleFactor / subRect.Width * 1.8, scaleFactor / subRect.Height * 1.8);
    sprite.SetPosition(
        body->GetWorldPoint(((b2PolygonShape*)bodyFixture->GetShape())->m_centroid).x * scaleFactor,
        body->GetWorldPoint(((b2PolygonShape*)bodyFixture->GetShape())->m_centroid).y * scaleFactor);
    sprite.SetRotation(body->GetAngle() * 180.0f / 3.1415926535);

    //window->Draw(renderBody);
    //window->Draw(renderFootbox);
    window->Draw(sprite);
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
    spriteTimer.Reset();
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
    return ((bool)floors);
}

bool Player::IsExited()
{
    return (exited);
}

bool Player::IsDead()
{
    return (dead);
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
    if (floors <= 0)
    {
        floors = 0;
        jumping = true;
    } else
    {
        jumping = false;
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
