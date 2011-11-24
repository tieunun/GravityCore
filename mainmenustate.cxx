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

void MainMenuState::Initiate()
{
    current = 0;

    std::vector<std::string> menuItems;

    menuItems.push_back("Start Game");
    menuItems.push_back("Options");
    menuItems.push_back("Credits");
    menuItems.push_back("Exit");

    for (unsigned int i = 0; i < menuItems.size(); i++)
    {
        displayItems.push_back(sf::Text());
        displayItems.back().SetString(menuItems[i]);
        displayItems.back().SetPosition(50, i * 50);
    }
}

void MainMenuState::Cleanup()
{
}

void MainMenuState::Pause()
{
}

void MainMenuState::Resume()
{
}

void MainMenuState::HandleEvents(sf::Event* event, sf::RenderWindow* window)
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

void MainMenuState::Process(float frameTime)
{
    for (unsigned int i = 0; i < displayItems.size(); i++)
    {
        // Hilight current item as green, and all others as white
        if (i == current)
        {
            displayItems[i].SetColor(sf::Color::Green);
        } else
        {
            displayItems[i].SetColor(sf::Color::White);
        }
    }
}

void MainMenuState::Render(sf::RenderWindow* window)
{
    for (unsigned int i = 0; i < displayItems.size(); i++)
    {
        window->Draw(displayItems[i]);
    }
}

void MainMenuState::NextItem()
{
    if (current < (displayItems.size() - 1))
    {
        current++;
    } else
    {
        current = 0;
    }
}

void MainMenuState::PreviousItem()
{
    if (current > 0)
    {
        current--;
    } else
    {
        current = (displayItems.size() - 1);
    }
}

void MainMenuState::SelectCurrent()
{
    switch (current)
    {
        case 0:
            game->PushState(new MainGameState(game));
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            game->PopState();
            break;
        default:
            break;
    }
}

#endif

