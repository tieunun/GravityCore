/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CONTACTLISTENER_CXX
#define CONTACTLISTENER_CXX

#include "contactlistener.hxx"

void ContactListener::BeginContact(b2Contact* contact)
{
    // If fixture A exists and is a footboxSensor
    if (contact->GetFixtureA()->GetUserData() &&
        contact->GetFixtureA()->GetUserData() == (void*)footboxSensor)
    {
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->ChangeFloors(true);
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->Land();
    // If fixture B exists and is a footboxSensor
    } else if (contact->GetFixtureB()->GetUserData() &&
                contact->GetFixtureB()->GetUserData() == (void*)footboxSensor)
    {
        ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->ChangeFloors(true);
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->Land();
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
    // If fixture A exists and is a footboxSensor
    if (contact->GetFixtureA()->GetBody()->GetUserData() &&
        contact->GetFixtureA()->GetUserData() == (void*)(footboxSensor))
    {
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->ChangeFloors(false);
    // If fixture B exists and is a footboxSensor
    } else if (contact->GetFixtureB()->GetBody()->GetUserData() &&
                contact->GetFixtureB()->GetUserData() == (void*)(footboxSensor))
    {
        ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->ChangeFloors(false);
    }
}

#endif
