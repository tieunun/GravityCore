/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef MAINGAME_STATE_CXX
#define MAINGAME_STATE_CXX

#include "maingamestate.hxx"

MainGameState::MainGameState(GameCore* game) : PI(3.1415926535f)
{
    this->game = game;
}

void MainGameState::Initiate()
{
    velocityIterations = 6;
    positionIterations = 2;
    gravity = b2Vec2(0.0f, 0.0f);
    doSleep = true;
    world = new b2World(gravity);
    world->SetAllowSleeping(doSleep);
    contactListener = new ContactListener();
    world->SetContactListener(contactListener);
    Player::Initiate();

    player = new Player();
    player->Create(7.0f, 5.0f, 0.4f, 0.9f, 60.0f, world);

    playerView = new sf::View();

    //-Update Rectangle for Create function like Player-

    scaleFactor = 10.0f;
    cores.push_back(Core::CreateCore(10, 10, 2, 1000, world));
}

void MainGameState::Cleanup()
{
    while (cores.size() > 0)
    {
        cores.back()->Cleanup();
        cores.pop_back();
    }
    //-Update Rectangle for Destroy function like Player-
    player->Destroy(world);

    Player::Cleanup();
    delete player;
    delete world;
    delete contactListener;
}

void MainGameState::Pause()
{
    player->Pause();
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        cores[i]->Pause();
    }
}

void MainGameState::Resume()
{
    player->Resume();
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        cores[i]->Resume();
    }
}

void MainGameState::HandleEvents(sf::Event* event)
{
    switch (event->Type)
    {
        case sf::Event::KeyPressed:
            switch (event->Key.Code)
            {
                case sf::Keyboard::Up:
                    if (player->IsGrounded())
                    {
                        player->Impulse(0, -10);
                    }
                    break;
                case sf::Keyboard::Down:
                    player->Impulse(0, 5);
                    break;
                case sf::Keyboard::Left:
                    player->Impulse(-5, 0);
                    break;
                case sf::Keyboard::Right:
                    player->Impulse(5, 0);
                    break;
                case sf::Keyboard::Space:
                    player->StopVelocity();
                    break;
                case sf::Keyboard::Escape:
                    game->PushState(new PauseMenuState(game));
                default:
                    break;
            }
            break;
        case sf::Event::KeyReleased:
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
                case sf::Keyboard::Space:
                    break;
                default:
                    break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            switch (event->MouseButton.Button)
            {
                case sf::Mouse::Left:
                    cores.push_back(Core::CreateCore(event->MouseButton.X / scaleFactor, event->MouseButton.Y / scaleFactor, 2.0f, 1000, world));
                    break;
                case sf::Mouse::Right:
                    cores.push_back(Core::CreateCore(event->MouseButton.X / scaleFactor, event->MouseButton.Y / scaleFactor, 1.0f, 600, world));
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void MainGameState::Process(float frameTime)
{
    world->Step(frameTime, velocityIterations, positionIterations);
    player->ClearGravitation();
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        player->AddGravitation(cores[i]->GetPosition() - player->GetPosition(), cores[i]->GetMass());
    }
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        cores[i]->Process();
    }
    player->Process();

}

void MainGameState::Render(sf::RenderWindow* window)
{
    playerView->SetSize(window->GetDefaultView().GetSize());
    playerView->SetCenter(player->GetPosition().x * scaleFactor, player->GetPosition().y * scaleFactor);
    playerView->SetRotation(player->GetAngle() * 180 / PI);
    window->SetView(*playerView);
    player->Render(scaleFactor, window);
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        cores[i]->Render(scaleFactor, window);
    }

    window->SetView(window->GetDefaultView());
}

#endif

