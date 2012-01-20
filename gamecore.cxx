#ifndef GAMECORE_CXX
#define GAMECORE_CXX

#include "gamecore.hxx"
#include "state.hxx"
#include "fontbase.hxx"
#include "menubase.hxx"
#include "mainmenustate.hxx"
#include "event.cxx"

std::queue<GLFWEvent> GameCore::events;
int GameCore::mouseX;
int GameCore::mouseY;
bool GameCore::exit;

GameCore::GameCore(std::string title)
{
    WINDOWWIDTH = 800;
    WINDOWHEIGHT = 600;
    TITLE = title;
}

GameCore::~GameCore()
{

}

void GLFWCALL GameCore::KeyCallback(int key, int state)
{
    GLFWEvent temp;
    temp.type = GLFWEvent::KEY;
    temp.state = state;
    temp.key = key;
    temp.x = mouseX;
    temp.y = mouseY;
    events.push(temp);
}

void GLFWCALL GameCore::MousePosCallback(int x, int y)
{
    GLFWEvent temp;
    temp.type = GLFWEvent::MOUSE_POS;
    temp.x = x;
    temp.y = y;
    events.push(temp);

    mouseX = x;
    mouseY = y;
}

void GLFWCALL GameCore::MouseButtonCallback(int button, int state)
{
    GLFWEvent temp;
    temp.type = GLFWEvent::BUTTON;
    temp.state = state;
    temp.button = button;
    temp.x = mouseX;
    temp.y = mouseY;
    events.push(temp);
}

void GLFWCALL GameCore::MouseWheelCallback(int position)
{
    GLFWEvent temp;
    temp.type = GLFWEvent::MOUSE_WHEEL;
    temp.direction = position;
    temp.x = mouseX;
    temp.y = mouseY;
    glfwGetWindowSize(&temp.width, &temp.height);
    events.push(temp);
    glfwSetMouseWheel(0);
}

void GLFWCALL GameCore::WindowResizeCallback(int width, int height)
{
    GLFWEvent temp;
    temp.type = GLFWEvent::RESIZE;
    temp.width = width;
    temp.height = height;
    events.push(temp);
}

int GLFWCALL GameCore::WindowCloseCallback()
{
    exit = true;
    return (GL_TRUE);
}

void GameCore::SendResizeEvent()
{
    GLFWEvent temp;
    temp.type = GLFWEvent::RESIZE;
    glfwGetWindowSize(&temp.width, &temp.height);
    events.push(temp);
}

int GameCore::Run()
{
    // --Setup--
    if (!Initiate())
    {
        return (EXIT_FAILURE);
    }

	// --Game Loop--
    while (!exit)
    {
        // --Event Loop--
        HandleEvents();
        if (exit)
        {
            break;
        }
        // --Data Processing--
        Process();

        // --Rendering--
        Render();
    }

    // --Cleanup--
    Cleanup();

    return (EXIT_SUCCESS);
}

bool GameCore::Initiate()
{
    exit = false;

    if (!glfwInit())
    {
        return (false);
    }

    if (!glfwOpenWindow(WINDOWWIDTH, WINDOWHEIGHT, 8, 8, 8, 8, 8, 0, GLFW_WINDOW))
    {
        return (false);
    }

    if (!FontBase::Initiate())
    {
        return (false);
    }

    if (!MenuBase::Initiate())
    {
        return (false);
    }

    glfwSetKeyCallback(KeyCallback);
    glfwSetMousePosCallback(MousePosCallback);
    glfwSetMouseButtonCallback(MouseButtonCallback);
    glfwSetMouseWheelCallback(MouseWheelCallback);
    glfwSetWindowSizeCallback(WindowResizeCallback);
    glfwSetWindowCloseCallback(WindowCloseCallback);
    glfwDisable(GLFW_AUTO_POLL_EVENTS);
    glfwSetWindowTitle("Loading...");
    // This sets the title
    glfwSwapBuffers();

    // VSync
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    glewInit();

    glClearColor(0.0, 0.0, 0.0, 0.0);
    FontBase::Initiate();

    PushState(new MainMenuState(this));

    glfwSetWindowTitle(TITLE.c_str());

    return (true);
}

void GameCore::Cleanup()
{
    //delete display;
    while (!states.empty())
    {
        PopState();
    }
    glfwTerminate();
    FontBase::Cleanup();
}

void GameCore::HandleEvents()
{
    glfwPollEvents();
    while (!events.empty())
    {
        event = &events.front();

        states.back()->HandleEvents(event);

        events.pop();
    }

    if (states.empty())
    {
        exit = true;
    }
}

void GameCore::Process()
{
        states.back()->Process(frametime);
}

void GameCore::Render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    states.back()->Render();
    glfwSwapBuffers();
    frametime = glfwGetTime();
    glfwSetTime(0.0);
}

void GameCore::PushState(State* state)
{
    if (!states.empty())
    {
        states.back()->Pause();
    }
    states.push_back(state);
    states.back()->Create();
}

void GameCore::PopState()
{
    states.back()->Destroy();
    delete states.back();
    states.pop_back();
    if (!states.empty())
    {
        states.back()->Resume();
    }
}

void GameCore::PopStates(unsigned int num)
{
    for (unsigned int i = 0; i < num; i++)
    {
        states.back()->Destroy();
        delete states.back();
        states.pop_back();
        if (!states.empty())
        {
            states.back()->Resume();
        }
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
