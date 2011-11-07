/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CONTACTLISTENER_CXX
#define CONTACTLISTENER_CXX

#include "contactlistener.hxx"
#include "player.hxx"

void ContactListener::BeginContact(b2Contact* contact)
{
    if (contact->GetFixtureA()->GetBody()->GetUserData() &&
        contact->GetFixtureA()->GetUserData() == (void*)((int)2))
    {
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->ChangeFloors(true);
    } else if (contact->GetFixtureB()->GetBody()->GetUserData() &&
                contact->GetFixtureB()->GetUserData() == (void*)((int)2))
    {
        ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->ChangeFloors(true);
    }
}


void ContactListener::EndContact(b2Contact* contact)
{
    if (contact->GetFixtureA()->GetBody()->GetUserData() &&
        contact->GetFixtureA()->GetUserData() == (void*)((int)2))
    {
        ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->ChangeFloors(false);
    } else if (contact->GetFixtureB()->GetBody()->GetUserData() &&
                contact->GetFixtureB()->GetUserData() == (void*)((int)2))
    {
        ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->ChangeFloors(false);
    }
}

#endif
