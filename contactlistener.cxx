/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CONTACTLISTENER_CXX
#define CONTACTLISTENER_CXX

#include "contactlistener.hxx"

void ContactListener::BeginContact(b2Contact* contact)
{
    if (contact->GetFixtureA()->GetBody()->GetUserData() &&
        contact->GetFixtureA()->GetUserData() == (void*)footboxSensor)
    {
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->ChangeFloors(true);
    } else if (contact->GetFixtureB()->GetBody()->GetUserData() &&
                contact->GetFixtureB()->GetUserData() == (void*)footboxSensor)
    {
        ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->ChangeFloors(true);
    }
}


void ContactListener::EndContact(b2Contact* contact)
{
    if (contact->GetFixtureA()->GetBody()->GetUserData() &&
        contact->GetFixtureA()->GetUserData() == (void*)(footboxSensor))
    {
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->ChangeFloors(false);
    } else if (contact->GetFixtureB()->GetBody()->GetUserData() &&
                contact->GetFixtureB()->GetUserData() == (void*)(footboxSensor))
    {
        ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->ChangeFloors(false);
    }
}

#endif
