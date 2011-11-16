/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef SPLASH_STATE_CXX
#define SPLASH_STATE_CXX
#include <iostream>

#include "mainmenustate.hxx"
#include "splashstate.hxx"

SplashState::SplashState(Core* game)  : length(2000)
{
    this->game = game;
}

void SplashState::Initiate()
{
    splashItems.push_back(sf::Text("Ax5 Productions", sf::Font::GetDefaultFont(), 30));
    splashItems.push_back(sf::Text("Programmer:\tTaylor C. Richberger", sf::Font::GetDefaultFont(), 30));

    for (unsigned short int i = 0; i < splashItems.size(); i++)
    {
        splashItems[i].SetPosition(30, game->GetHeight() / 2 - 15);
        splashItems[i].SetColor(sf::Color(255, 255, 255, 0));
    }

    current = 0;

    timer.Reset();
}

void SplashState::Cleanup()
{
}

void SplashState::Pause()
{
}

void SplashState::Resume()
{
}

void SplashState::HandleEvents(sf::Event* event)
{
    switch (event->Type)
    {
        case sf::Event::KeyPressed:
            switch (event->Key.Code)
            {
                case sf::Keyboard::Up:
                    break;
                case sf::Keyboard::Down:
                    break;
                case sf::Keyboard::Left:
                    break;
                case sf::Keyboard::Right:
                    break;
                case sf::Keyboard::Return:
                    current++;
                    timer.Reset();
                    break;
                case sf::Keyboard::Space:
                    break;
                case sf::Keyboard::Escape:
                    game->PopState();
                    game->PushState(new MainMenuState(game));
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void SplashState::Process(float frameTime)
{
    if (timer.GetElapsedTime() > length)
    {
        current++;
        timer.Reset();
    }
    if (current >= splashItems.size())
    {
        game->PopState();
        game->PushState(new MainMenuState(game));
        return;
    }

    if (timer.GetElapsedTime() < (length / 2))
    {
        splashItems[current].SetColor(sf::Color(255, 255, 255, (((float)timer.GetElapsedTime() / (float)(length / 2)) * 255)));
    } else
    {
        splashItems[current].SetColor(sf::Color(255, 255, 255, 255));
        if ((timer.GetElapsedTime() >= (length - 255)) && (timer.GetElapsedTime() <= length))
        {
            splashItems[current].SetColor(sf::Color(255, 255, 255, length - timer.GetElapsedTime()));
        }
    }
}

void SplashState::Render(sf::RenderWindow* window)
{
    window->Draw(splashItems[current]);
}

#endif
