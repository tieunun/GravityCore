/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CREDITS_STATE_CXX
#define CREDITS_STATE_CXX

#include "creditsstate.hxx"

CreditsState::CreditsState(GameCore* game)
{
    this->game = game;
}

void CreditsState::Initiate()
{
    std::string tempString;
    creditsItems.push_back(sf::Text("Ax5 Productions", sf::Font::GetDefaultFont(), 30));

    tempString =  "Programmer:\tTaylor C. Richberger\n";
    tempString += "Art:\t\t OpenGameArt.org\n";
    tempString += "Music: Detroid Thema A by Project Mahlen Goscht\n";
    creditsItems.push_back(sf::Text(tempString, sf::Font::GetDefaultFont(), 30));
    for (unsigned short int i = 0; i < creditsItems.size(); i++)
    {
        creditsItems[i].SetPosition(30, 30);
        creditsItems[i].SetColor(sf::Color::White);
    }

    current = 0;
}

void CreditsState::Cleanup()
{
}

void CreditsState::Pause()
{
}

void CreditsState::Resume()
{
}

void CreditsState::HandleEvents(sf::Event* event, sf::RenderWindow* window)
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
                    if (current > 0)
                    {
                        current--;
                    }
                    break;
                case sf::Keyboard::Right:
                    if (current < (creditsItems.size() - 1))
                    {
                        current++;
                    }
                    break;
                case sf::Keyboard::Return:
                    current++;
                    break;
                case sf::Keyboard::Space:
                    break;
                case sf::Keyboard::Escape:
                    current = creditsItems.size();
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void CreditsState::Process(float frameTime)
{
    // If the items have exceeded the total amount, move on to the Main
    //+Menu state.
    if (current >= creditsItems.size())
    {
        game->PopState();
        return;
    }
}

void CreditsState::Render(sf::RenderWindow* window)
{
    window->SetView(window->GetDefaultView());
    window->Draw(creditsItems[current]);
}

#endif
