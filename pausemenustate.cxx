/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef PAUSEMENU_STATE_CXX
#define PAUSEMENU_STATE_CXX

#include "pausemenustate.hxx"

PauseMenuState::PauseMenuState(GameCore* game)
{
    this->game = game;
}

PauseMenuState::~PauseMenuState()
{
}

void PauseMenuState::Create()
{
    current = 0;

    menuItems.push_back("Back to Game");
    //menuItems.push_back("Options");
    //menuItems.push_back("Credits");
    menuItems.push_back("Exit to Title");
}

void PauseMenuState::Destroy()
{

}

void PauseMenuState::Pause()
{
    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_LIGHTING_BIT | GL_ENABLE_BIT | GL_VIEWPORT_BIT);
}

void PauseMenuState::Resume()
{
    glPopAttrib();
}

void PauseMenuState::HandleEvents(GLFWEvent* event)
{
    switch (event->type)
    {
        case GLFWEvent::KEY:
            if (event->state == GLFW_PRESS)
            {
                switch (event->key)
                {
                    case GLFW_KEY_UP:
                        PreviousItem();
                        break;
                    case GLFW_KEY_DOWN:
                        NextItem();
                        break;
                    case GLFW_KEY_ENTER:
                        SelectCurrent();
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
}

void PauseMenuState::Process(float frameTime)
{
}

void PauseMenuState::Render()
{
    for (i = 0; i < menuItems.size(); i++)
    {
        static unsigned int horizPixels;
        horizPixels = 20;
        if (current == i)
        {
            glColor3f(1.0f, 1.0f, 1.0f);
        } else
        {
            glColor3f(0.3f, 0.3f, 0.3f);
        }
        for (j = 0; j < menuItems[i].length(); j++)
        {
            DrawString(menuItems[i], 20, 200 + (32 * i), 32);
        }
    }
}

void PauseMenuState::SelectCurrent()
{
    switch (current)
    {
        // Start Game
        case 0:
            PopState();
            break;
        // Exit
        case 1:
            PopStates(2);
            break;
        default:
            break;
    }
}

#endif
