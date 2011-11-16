/*
 *  Lead Coder:     Taylor C. Richberger
 *
 *  Latest updates: Got state stack and core game loop fully functional, as well as a
 *                  rudimentary main menu.  Added rudimentary pause menu.
 *
 *  To Do:          Develop game, lol
 */

#include "gamecore.hxx"

int main()
{
    GameCore game("Gravity Core (Built on " + std::string(__DATE__) + ")");
    return (game.Run());
}
