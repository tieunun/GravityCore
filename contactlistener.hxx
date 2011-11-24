/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CONTACTLISTENER_HXX
#define CONTACTLISTENER_HXX

#include <Box2D/Box2D.h>

#include "player.hxx"
#include "fixturetype.cxx"

// This, for now, only handles the player's footbox for jumping
class ContactListener : public b2ContactListener
{
    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
};

#endif
