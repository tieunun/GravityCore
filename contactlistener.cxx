/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CONTACTLISTENER_CXX
#define CONTACTLISTENER_CXX

#include "contactlistener.hxx"

void ContactListener::BeginContact(b2Contact* contact)
{

    // If fixture A exists and is a footboxSensor and if fixture B exists and is a shape
    if ((contact->GetFixtureA()->GetUserData() &&
         contact->GetFixtureA()->GetUserData() == (void*)footboxSensor) &&
        (contact->GetFixtureB()->GetUserData() &&
         contact->GetFixtureB()->GetUserData() == (void*)masslessFixture))
    {
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->AddFloor((Shape*)contact->GetFixtureB()->GetBody()->GetUserData());
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->Land();

    // If fixture B exists and is a footboxSensor and if fixture A exists and is a shape
    } else if ((contact->GetFixtureB()->GetUserData() &&
                 contact->GetFixtureB()->GetUserData() == (void*)footboxSensor) &&
                (contact->GetFixtureA()->GetUserData() &&
                 contact->GetFixtureA()->GetUserData() == (void*)masslessFixture))
    {
        ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->AddFloor((Shape*)contact->GetFixtureA()->GetBody()->GetUserData());
        ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->Land();
    }

    // If fixture A exists and is a playerFixture and if fixture B exists and is an exit sensor
    if ((contact->GetFixtureA()->GetUserData() &&
         contact->GetFixtureA()->GetUserData() == (void*)playerFixture) &&
        (contact->GetFixtureB()->GetUserData() &&
         contact->GetFixtureB()->GetUserData() == (void*)exitSensor))
    {
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->Exit();
    // If fixture B exists and is a playerFixture and if fixture A exists and is an exit sensor
    } else if ((contact->GetFixtureB()->GetUserData() &&
                 contact->GetFixtureB()->GetUserData() == (void*)playerFixture) &&
                (contact->GetFixtureA()->GetUserData() &&
                 contact->GetFixtureA()->GetUserData() == (void*)exitSensor))
    {
        ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->Exit();
    }

    // If fixture A exists and is a playerFixture and if fixture B exists and is a core
    if ((contact->GetFixtureA()->GetUserData() &&
         contact->GetFixtureA()->GetUserData() == (void*)playerFixture) &&
        (contact->GetFixtureB()->GetUserData() &&
         contact->GetFixtureB()->GetUserData() == (void*)massiveFixture))
    {
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->Die();
    // If fixture B exists and is a playerFixture and if fixture A exists and is a core
    } else if ((contact->GetFixtureB()->GetUserData() &&
                 contact->GetFixtureB()->GetUserData() == (void*)playerFixture) &&
                (contact->GetFixtureA()->GetUserData() &&
                 contact->GetFixtureA()->GetUserData() == (void*)massiveFixture))
    {
        ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->Die();
    }
}


void ContactListener::EndContact(b2Contact* contact)
{
    // If fixture A exists and is a footboxSensor and if fixture B exists and is a shape
    if ((contact->GetFixtureA()->GetUserData() &&
         contact->GetFixtureA()->GetUserData() == (void*)footboxSensor) &&
        (contact->GetFixtureB()->GetUserData() &&
         contact->GetFixtureB()->GetUserData() == (void*)masslessFixture))
    {
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->RemoveFloor((Shape*)contact->GetFixtureB()->GetBody()->GetUserData());

    // If fixture B exists and is a footboxSensor and if fixture A exists and is a shape
    } else if ((contact->GetFixtureB()->GetUserData() &&
                 contact->GetFixtureB()->GetUserData() == (void*)footboxSensor) &&
                (contact->GetFixtureA()->GetUserData() &&
                 contact->GetFixtureA()->GetUserData() == (void*)masslessFixture))
    {
        ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->RemoveFloor((Shape*)contact->GetFixtureA()->GetBody()->GetUserData());
    }
}

#endif
