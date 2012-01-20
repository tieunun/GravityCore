#include "gamecore.hxx"

int main()
{
    // Create the game
    GameCore game("Gravity Core (Built on " + std::string(__DATE__) + ")");
    // Run the game, returning the exit status
    return (game.Run());
}
