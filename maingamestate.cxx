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
    player->Create(10.0f, 5.0f, 0.3f, 0.9f, 60.0f, world);

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
    cores.push_back(Core::CreateCore(10, 15, 5, 10000, world));
    shapes.push_back(Shape::CreateRectangle(10, 6, 1, 1, 0, false, world));
}

void MainGameState::Cleanup()
{
    bgm->Stop();
    // Destroy all instances of everything
    ClearStage();

    // Clean up classes
    Core::Cleanup();
    Player::Cleanup();
    delete bgm;
    delete playerView;
    delete player;
    delete minimapView;
    delete minimapBox;
    delete world;
    delete contactListener;
}

void MainGameState::ClearStage()
{
    while (cores.size() > 0)
    {
        cores.back()->Destroy(world);
        delete cores.back();
        cores.pop_back();
    }
    while (shapes.size() > 0)
    {
        shapes.back()->Destroy(world);
        delete shapes.back();
        shapes.pop_back();
    }
    player->Destroy(world);
}

void MainGameState::LoadStage(std::string fileName)
{
    struct PlayerData
    {
        float x;
        float y;
        float halfWidth;
        float halfHeight;
        float mass;
    } playerData;

    struct RectangleData
    {
        float x;
        float y;
        float halfWidth;
        float halfHeight;
        float angle;
        bool dynamic;
    } rectangleData;

    struct CoreData
    {
        float x;
        float y;
        float radius;
        float mass;
    } coreData;

    unsigned int size;

    std::ifstream input;
    input.open(fileName.c_str(), std::ios::in | std::ios::binary);

    if (!input.is_open())
    {
        return;
    }

    ClearStage();
    // Input Player information
    input.read((char*)&playerData, sizeof(PlayerData));

    player->Create(playerData.x, playerData.y, playerData.halfWidth, playerData.halfHeight, playerData.mass, world);

    // Input Core information
    input.read((char*)&size, sizeof(unsigned int));

    for (int i = 0; i < size; i++)
    {
        input.read((char*)&coreData, sizeof(CoreData));
        cores.push_back(Core::CreateCore(coreData.x, coreData.y, coreData.radius, coreData.mass, world));
    }

    // input Rectangle information
    input.read((char*)&size, sizeof(unsigned int));

    for (int i = 0; i < size; i++)
    {
        input.read((char*)&rectangleData, sizeof(RectangleData));
        shapes.push_back(Shape::CreateRectangle(rectangleData.x, rectangleData.y, rectangleData.halfWidth, rectangleData.halfHeight, rectangleData.angle, rectangleData.dynamic, world));
    }

    input.close();
}

void LoadStage(int stageNumber);

void MainGameState::SaveStage(std::string fileName)
{
    struct PlayerData
    {
        float x;
        float y;
        float halfWidth;
        float halfHeight;
        float mass;
    } playerData;

    struct RectangleData
    {
        float x;
        float y;
        float halfWidth;
        float halfHeight;
        float angle;
        bool dynamic;
    } rectangleData;

    struct CoreData
    {
        float x;
        float y;
        float radius;
        float mass;
    } coreData;

    unsigned int size;

    std::ofstream output;
    output.open(fileName.c_str(), std::ios::out | std::ios::binary);
    // Output Player information
    playerData.x = player->GetPosition().x;
    playerData.y = player->GetPosition().y;
    playerData.halfWidth = player->GetHalfWidth();
    playerData.halfHeight = player->GetHalfHeight();
    playerData.mass = player->GetMass();

    output.write((char*)&playerData, sizeof(PlayerData));

    // Output Core information
    size = cores.size();
    output.write((char*)&size, sizeof(unsigned int));

    for (int i = 0; i < size; i++)
    {
        coreData.x = cores[i]->GetPosition().x;
        coreData.y = cores[i]->GetPosition().y;
        coreData.radius = cores[i]->GetRadius();
        coreData.mass = cores[i]->GetMass();

        output.write((char*)&coreData, sizeof(CoreData));
    }

    // Output Rectangle information
    size = shapes.size();
    output.write((char*)&size, sizeof(unsigned int));

    for (int i = 0; i < size; i++)
    {
        rectangleData.x = shapes[i]->GetPosition().x;
        rectangleData.y = shapes[i]->GetPosition().y;
        rectangleData.halfWidth = shapes[i]->GetHalfWidth();
        rectangleData.halfHeight = shapes[i]->GetHalfHeight();
        rectangleData.angle = shapes[i]->GetAngle();
        rectangleData.dynamic = shapes[i]->IsDynamic();

        output.write((char*)&rectangleData, sizeof(RectangleData));
    }

    output.close();
}

void LoadNextStage();

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
                    player->MoveLeft();
                    break;
                case sf::Keyboard::Right:
                    player->MoveRight();
                    break;
                case sf::Keyboard::Space:
                    if (player->IsGrounded())
                    {
                        player->Jump();
                    } else
                    {
                        player->StopVelocity();
                    }
                    break;
                case sf::Keyboard::Escape:
                    PushState(new PauseMenuState(game));
                    break;
                case sf::Keyboard::O:
                    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::IsKeyPressed(sf::Keyboard::RControl))
                    {
                        LoadStage("test.bin");
                    }
                    break;
                case sf::Keyboard::S:
                    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::IsKeyPressed(sf::Keyboard::RControl))
                    {
                        SaveStage("test.bin");
                    }
                    break;
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
                    player->StopMoving();
                    break;
                case sf::Keyboard::Right:
                    player->StopMoving();
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
                    cores.push_back(Core::CreateCore(round(window->ConvertCoords(event->MouseButton.X, event->MouseButton.Y, *playerView).x / scaleFactor), round(window->ConvertCoords(event->MouseButton.X, event->MouseButton.Y, *playerView).y / scaleFactor), 2.0f, 10000, world));
                    break;
                case sf::Mouse::Right:
                    // Create a massless shape at the point of the mouse click
                    shapes.push_back(Shape::CreateRectangle(round(window->ConvertCoords(event->MouseButton.X, event->MouseButton.Y, *playerView).x / scaleFactor), round(window->ConvertCoords(event->MouseButton.X, event->MouseButton.Y, *playerView).y / scaleFactor), 1.0f, 1.0f, 0.0f, false, world));
                    break;
                case sf::Mouse::Middle:
                    scaleFactor = 30;
                    break;
                default:
                    break;
            }
            break;
        case sf::Event::MouseWheelMoved:
            scaleFactor += event->MouseWheel.Delta;
            if (scaleFactor < 1)
            {
                scaleFactor = 1;
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
    // Apply gravitational force and movement
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

