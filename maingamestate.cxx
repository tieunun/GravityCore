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
    minimapView = new sf::View();

    playerView->SetSize(sf::Vector2f(game->GetWidth(), game->GetHeight()));

    minimapView->SetViewport(sf::FloatRect(0.05f, 0.05f, 0.15f, 0.15f));
    minimapView->SetSize(sf::Vector2f(game->GetWidth() * minimapView->GetViewport().Width, game->GetHeight() * minimapView->GetViewport().Height));

    minimapBox = new sf::Shape();
    *minimapBox = sf::Shape::Rectangle(game->GetWidth() * minimapView->GetViewport().Left, game->GetHeight() * minimapView->GetViewport().Top, game->GetWidth() * minimapView->GetViewport().Width, game->GetHeight() * minimapView->GetViewport().Height, sf::Color(0, 0, 0, 127), 2, sf::Color::Magenta);
    minimapBox->EnableFill(true);
    minimapBox->EnableOutline(true);

    bgm = new sf::Music();
    bgm->OpenFromFile("audio/music/background.ogg");
    bgm->SetLoop(true);
    bgm->Play();

    minimapScaleFactor = 2.0f;
    scaleFactor = 20.0f;
    cores.push_back(Core::CreateCore(10, 10, 2, 1000, world));
}

void MainGameState::Cleanup()
{
    bgm->Stop();
    // Destroy all instances of everything
    while (cores.size() > 0)
    {
        cores.back()->Destroy(world);
        cores.pop_back();
    }
    while (shapes.size() > 0)
    {
        shapes.back()->Destroy(world);
        shapes.pop_back();
    }
    player->Destroy(world);

    // Clean up classes
    Core::Cleanup();
    Player::Cleanup();
    delete bgm;
    delete playerView;
    delete minimapView;
    delete minimapBox;
    delete player;
    delete world;
    delete contactListener;
}

void MainGameState::Pause()
{
    bgm->Pause();
    player->Pause();
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        cores[i]->Pause();
    }
    for (unsigned int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->Pause();
    }
}


void MainGameState::Resume()
{
    bgm->Play();
    player->Resume();
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        cores[i]->Resume();
    }
    for (unsigned int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->Resume();
    }
}

void MainGameState::HandleEvents(sf::Event* event, sf::RenderWindow* window)
{
    switch (event->Type)
    {
        case sf::Event::KeyPressed:
            switch (event->Key.Code)
            {
                case sf::Keyboard::Up:
                    break;
                case sf::Keyboard::Down:
                    //player->Impulse(0, 5);
                    break;
                case sf::Keyboard::Left:
                    if (player->IsGrounded())
                    {
                        player->Impulse(-5, 0);
                    }
                    break;
                case sf::Keyboard::Right:
                    if (player->IsGrounded())
                    {
                        player->Impulse(5, 0);
                    }
                    break;
                case sf::Keyboard::Space:
                    if (player->IsGrounded())
                    {
                        player->Impulse(0, -10);
                    } else
                    {
                        player->StopVelocity();
                    }
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
                    // Create a core on a left click at the point of the click
                    cores.push_back(Core::CreateCore(window->ConvertCoords(event->MouseButton.X, event->MouseButton.Y, *playerView).x / scaleFactor, window->ConvertCoords(event->MouseButton.X, event->MouseButton.Y, *playerView).y / scaleFactor, 2.0f, 1000, world));
                    break;
                case sf::Mouse::Right:
                    // Create a massless shape at the point of the mouse click
                    shapes.push_back(Shape::CreateCircle(window->ConvertCoords(event->MouseButton.X, event->MouseButton.Y, *playerView).x / scaleFactor, window->ConvertCoords(event->MouseButton.X, event->MouseButton.Y, *playerView).y / scaleFactor, 1.0f, false, world));
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
    // Run a step of simulation in the Box2D world
    world->Step(frameTime, velocityIterations, positionIterations);
    // Reset the player's gravitation
    player->ClearGravitation();
    // Combine the gravitation from all the cores on the player
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        player->AddGravitation(cores[i]->GetPosition() - player->GetPosition(), cores[i]->GetMass());
    }
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        cores[i]->Process();
    }
    // Apply gravitational force
    player->Process();

}

void MainGameState::Render(sf::RenderWindow* window)
{
    // Set and render the normal view
    playerView->SetCenter(player->GetPosition().x * scaleFactor, player->GetPosition().y * scaleFactor);
    playerView->SetRotation(player->GetAngle() * 180.0f / PI);
    window->SetView(*playerView);
    player->Render(scaleFactor, window);
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        cores[i]->Render(scaleFactor, window);
    }
    for (unsigned int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->Render(scaleFactor, window);
    }

    // Set and render the minimap bounding box
    window->SetView(window->GetDefaultView());
    window->Draw(*minimapBox);

    // Set and render the minimap on the bounding box
    minimapView->SetCenter(player->GetPosition().x * minimapScaleFactor, player->GetPosition().y * minimapScaleFactor);
    window->SetView(*minimapView);
    player->Render(minimapScaleFactor, window);
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        cores[i]->Render(minimapScaleFactor, window);
    }
    for (unsigned int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->Render(minimapScaleFactor, window);
    }
}

#endif

