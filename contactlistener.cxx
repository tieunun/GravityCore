/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CONTACTLISTENER_CXX
#define CONTACTLISTENER_CXX

#include "contactlistener.hxx"

void ContactListener::BeginContact(b2Contact* contact)
{
    // If fixture A exists and is a footboxSensor
    if (contact->GetFixtureA()->GetBody()->GetUserData() &&
        contact->GetFixtureA()->GetUserData() == (void*)footboxSensor)
    {
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->ChangeFloors(true);
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->Land();
    // If fixture B exists and is a footboxSensor
    } else if (contact->GetFixtureB()->GetBody()->GetUserData() &&
                contact->GetFixtureB()->GetUserData() == (void*)footboxSensor)
    {
        ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->ChangeFloors(true);
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->Land();
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
