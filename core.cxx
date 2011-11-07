/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CORE_CXX
#define CORE_CXX

#include "core.hxx"
#include "state.hxx"
#include "splashstate.hxx"
#include "mainmenustate.hxx"

Core::Core(std::string title)
{
    WINDOWWIDTH = 800;
    WINDOWHEIGHT = 600;
    TITLE = title;
}

Core::~Core()
{

}

int Core::Run()
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

bool Core::Initiate()
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

void Core::Cleanup()
{
    delete event;
    delete window;

    while (!states.empty())
    {
        PopState();
    }
}

void Core::HandleEvents()
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

void Core::Process()
{
    states.back()->Process(window->GetFrameTime() / 1000.0f);
}

void Core::Render()
{
    window->Clear();

    states.back()->Render(window);

    // Update window
    window->Display();
}

void Core::PushState(State* state)
{
    if (!states.empty())
    {
        states.back()->Pause();
    }
    states.push_back(state);
    states.back()->Initiate();
}

void Core::PopState()
{
    states.back()->Cleanup();
    delete states.back();
    states.pop_back();
    if (!states.empty())
    {
        states.back()->Resume();
    }
}

int Core::GetWidth()
{
    return (WINDOWWIDTH);
}

int Core::GetHeight()
{
    return (WINDOWHEIGHT);
}

#endif
