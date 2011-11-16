/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef GAMECORE_CXX
#define GAMECORE_CXX

#include "gamecore.hxx"
// These are only not in the header to avoid conflicts with the State class
#include "splashstate.hxx"
#include "mainmenustate.hxx"

GameCore::GameCore(std::string title)
{
    WINDOWWIDTH = 800;
    WINDOWHEIGHT = 600;
    TITLE = title;
}

GameCore::~GameCore()
{

}

int GameCore::Run()
{
    // --Setup--
    if (!Initiate())
    {
        return (EXIT_FAILURE);
    }

	// --Game Loop--
    while (window->IsOpened())
    {
        // --Event Loop--
        HandleEvents();

        // Prevents any attempt to access an empty state stack.  Close if stack is empty.
        if (!states.empty())
        {
            // --Data Processing--
            Process();

            // --Rendering--
            Render();
        }
    }

    // --Cleanup--
    Cleanup();

    return (EXIT_SUCCESS);
}

bool GameCore::Initiate()
{
    window = new sf::RenderWindow();
    event = new sf::Event();

    // Create the window and set default settings
    window->Create(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), TITLE);
    window->EnableKeyRepeat(false);
    window->EnableVerticalSync(true);

    // Initializes state stack with a main menu
    PushState(new SplashState(this));

    return (true);
}

void GameCore::Cleanup()
{
    delete event;
    delete window;

    while (!states.empty())
    {
        PopState();
    }
}

void GameCore::HandleEvents()
{
    while (window->PollEvent(*event))
    {
        states.back()->HandleEvents(event);

        // closes the window on an empty state stack or window close event
        if (states.empty() || (event->Type == sf::Event::Closed))
        {
            window->Close();
        }
    }
}

void GameCore::Process()
{
    states.back()->Process(window->GetFrameTime() / 1000.0f);
}

void GameCore::Render()
{
    window->Clear();

    states.back()->Render(window);

    // Update window
    window->Display();
}

void GameCore::PushState(State* state)
{
    if (!states.empty())
    {
        states.back()->Pause();
    }
    states.push_back(state);
    states.back()->Initiate();
}

void GameCore::PopState()
{
    states.back()->Cleanup();
    delete states.back();
    states.pop_back();
    if (!states.empty())
    {
        states.back()->Resume();
    }
}

int GameCore::GetWidth()
{
    return (WINDOWWIDTH);
}

int GameCore::GetHeight()
{
    return (WINDOWHEIGHT);
}

#endif
