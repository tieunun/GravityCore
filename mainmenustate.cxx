/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef MAINMENU_STATE_CXX
#define MAINMENU_STATE_CXX

#include "mainmenustate.hxx"

MainMenuState::MainMenuState(GameCore* game)
{
    this->game = game;
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::Create()
{
    game->SetWaitEvents();
    glDisable(GL_LIGHTING);

    current = 0;

    menuItems.push_back("Start game");
    //menuItems.push_back("Options");
    //menuItems.push_back("Credits");
    menuItems.push_back("Exit");
}

void MainMenuState::Destroy()
{
}

void MainMenuState::Pause()
{
    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_LIGHTING_BIT | GL_ENABLE_BIT);
}

void MainMenuState::Resume()
{
    glPopAttrib();
    game->SetWaitEvents();
}

void MainMenuState::HandleEvents(GLFWEvent* event)
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
        case GLFWEvent::RESIZE:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glViewport(0, 0, event->width, event->height);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            break;
        default:
            break;
    }
}

void MainMenuState::Process(float frameTime)
{
}

void MainMenuState::Render()
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

void MainMenuState::SelectCurrent()
{
    switch (current)
    {
        // Start Game
        case 0:
            SendResizeEvent();
            PushState(new MainGameState(game));
            break;
        // Exit
        case 1:
            PopState();
            break;
        default:
            break;
    }
}

#endif
