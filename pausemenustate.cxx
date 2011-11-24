/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef MAINMENU_STATE_CXX
#define MAINMENU_STATE_CXX

#include "pausemenustate.hxx"

PauseMenuState::PauseMenuState(GameCore* game)
{
    this->game = game;
}

void PauseMenuState::Initiate()
{
    current = 0;

    std::vector<std::string> menuItems;

    menuItems.push_back("Back to Game");
    menuItems.push_back("Quit to Title");

    for (unsigned short int i = 0; i < menuItems.size(); i++)
    {
        displayItems.push_back(sf::Text());
        displayItems.back().SetString(menuItems[i]);
        displayItems.back().SetPosition(50, i * 50);
    }
}

void PauseMenuState::Cleanup()
{
}

void PauseMenuState::Pause()
{
}

void PauseMenuState::Resume()
{
}

void PauseMenuState::HandleEvents(sf::Event* event, sf::RenderWindow* window)
{
    switch (event->Type)
    {
        case sf::Event::KeyPressed:
            switch (event->Key.Code)
            {
                case sf::Keyboard::Up:
                    PreviousItem();
                    break;
                case sf::Keyboard::Down:
                    NextItem();
                    break;
                case sf::Keyboard::Return:
                    SelectCurrent();
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void PauseMenuState::Process(float frameTime)
{
    for (unsigned short int i = 0; i < displayItems.size(); i++)
    {
        //Hilight the current item as green, and all others as white
        if (i == current)
        {
            displayItems[i].SetColor(sf::Color::Green);
        } else
        {
            displayItems[i].SetColor(sf::Color::White);
        }
    }
}

void PauseMenuState::Render(sf::RenderWindow* window)
{
    for (unsigned short int i = 0; i < displayItems.size(); i++)
    {
        window->Draw(displayItems[i]);
    }
}

void PauseMenuState::NextItem()
{
    if (current < (displayItems.size() - 1))
    {
        current++;
    } else
    {
        current = 0;
    }
}

void PauseMenuState::PreviousItem()
{
    if (current > 0)
    {
        current--;
    } else
    {
        current = (displayItems.size() - 1);
    }
}

void PauseMenuState::SelectCurrent()
{
    switch (current)
    {
        case 0:
            game->PopState();
            break;
        case 1:
            game->PopState();
            game->PopState();
            break;
        default:
            break;
    }
}

#endif

