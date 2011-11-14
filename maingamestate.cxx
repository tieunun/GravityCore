/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef MAINGAME_STATE_CXX
#define MAINGAME_STATE_CXX

#include <iostream>

#include "maingamestate.hxx"
#include "pausemenustate.hxx"

MainGameState::MainGameState(Core* game)
{
    this->game = game;
}

void MainGameState::Initiate()
{
    velocityIterations = 6;
    positionIterations = 2;
    gravity = b2Vec2(0.0f, 9.8f);
    doSleep = true;
    world = new b2World(gravity);
    world->SetAllowSleeping(doSleep);
    contactListener = new ContactListener();
    world->SetContactListener(contactListener);
    Player::Initiate();

    player = new Player();
    player->Create(7.0f, 5.0f, 0.4f, 0.9f, true, world);

    //-Update Rectangle for Create function like Player-
    ground = new Shape();
    ground->InitiateAsRectangle(11.0f, 15.0f, 10.0f, 1.0f, false, world);

    scaleFactor = 30.0f;
}

void MainGameState::Cleanup()
{
    while (circles.size() > 0)
    {
        circles.back()->Cleanup();
        circles.pop_back();
    }
    //-Update Rectangle for Destroy function like Player-
    player->Destroy(world);
    ground->Cleanup();

    Player::Cleanup();
    delete player;
    delete world;
    delete contactListener;
}

void MainGameState::Pause()
{
    player->Pause();
    ground->Pause();
    for (unsigned int i = 0; i < circles.size(); i++)
    {
        circles[i]->Pause();
    }
}

void MainGameState::Resume()
{
    player->Resume();
    ground->Resume();
    for (unsigned int i = 0; i < circles.size(); i++)
    {
        circles[i]->Resume();
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
                    if (player->GetGrounded())
                    {
                        player->Impulse(0, -5);
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
                    circles.push_back(new Shape());
                    circles.back()->InitiateAsCircle(event->MouseButton.X / scaleFactor, event->MouseButton.Y / scaleFactor, 0.5f, true, world);
                    break;
                case sf::Mouse::Right:
                    circles.push_back(new Shape());
                    circles.back()->InitiateAsRectangle(event->MouseButton.X / scaleFactor, event->MouseButton.Y / scaleFactor, 1.0f, 1.0f, false, world);
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
    player->Process(scaleFactor);
    ground->Process(scaleFactor);
    for (unsigned int i = 0; i < circles.size(); i++)
    {
        circles[i]->Process(scaleFactor);
    }
}

void MainGameState::Render(sf::RenderWindow* window)
{
    player->Render(window);
    ground->Render(window);
    for (unsigned int i = 0; i < circles.size(); i++)
    {
        circles[i]->Render(window);
    }
}

#endif

