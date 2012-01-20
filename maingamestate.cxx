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

void MainGameState::Create()
{
    glDisable(GL_BLEND);
    glEnable(GL_RESCALE_NORMAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);

    currentStage = 0;
    stages.push_back("stage1.grav");
    stages.push_back("stage2.grav");
    stages.push_back("stage3.grav");
    stages.push_back("stage4.grav");

    velocityIterations = 6;
    positionIterations = 2;
    gravity = b2Vec2(0.0f, 0.0f);
    doSleep = true;
    world = new b2World(gravity);
    world->SetAllowSleeping(doSleep);
    contactListener = new ContactListener();
    world->SetContactListener(contactListener);
    Player::Initiate();
    Core::Initiate();
    Shape::Initiate();

    player = new Player();
    exit = new Shape();

    minimapScaleFactor = 2.0f;
    scaleFactor = 20.0f;

    LoadStage(0);
}

void MainGameState::Destroy()
{
    // Destroy all instances of everything
    ClearStage();

    // Clean up classes
    Core::Cleanup();
    Shape::Cleanup();
    Player::Cleanup();

    delete exit;
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
    exit->Destroy(world);
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

    struct ExitData
    {
        float x;
        float y;
        float radius;
    } exitData;

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
    input.open(("stages/" + fileName).c_str(), std::ios::in | std::ios::binary);

    if (!input.is_open())
    {
        return;
    }

    ClearStage();
    // Input Player information
    input.read((char*)&playerData, sizeof(PlayerData));

    player->Create(playerData.x, playerData.y, playerData.halfWidth, playerData.halfHeight, playerData.mass, world);

    // Input Exit information
    input.read((char*)&exitData, sizeof(ExitData));

    exit->CreateAsExit(exitData.x, exitData.y, exitData.radius, world);

    // Input Core information
    input.read((char*)&size, sizeof(unsigned int));

    for (unsigned int i = 0; i < size; i++)
    {
        input.read((char*)&coreData, sizeof(CoreData));
        cores.push_back(Core::CreateCore(coreData.x, coreData.y, coreData.radius, coreData.mass, world));
    }

    // input Rectangle information
    input.read((char*)&size, sizeof(unsigned int));

    for (unsigned int i = 0; i < size; i++)
    {
        input.read((char*)&rectangleData, sizeof(RectangleData));
        shapes.push_back(Shape::CreateRectangle(rectangleData.x, rectangleData.y, rectangleData.halfWidth, rectangleData.halfHeight, rectangleData.angle, rectangleData.dynamic, world));
    }

    input.close();
}

void MainGameState::LoadStage(int stageNumber)
{
    LoadStage(stages[stageNumber]);
}

void MainGameState::LoadNextStage()
{
    currentStage++;
    if (currentStage < stages.size())
    {
        LoadStage(currentStage);
    } else
    {
        PopState();
    }
}

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

    struct ExitData
    {
        float x;
        float y;
        float radius;
    } exitData;

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
    output.open(("stages/" + fileName).c_str(), std::ios::out | std::ios::binary);

    // Output Player information
    playerData.x = player->GetPosition().x;
    playerData.y = player->GetPosition().y;
    playerData.halfWidth = player->GetHalfWidth();
    playerData.halfHeight = player->GetHalfHeight();
    playerData.mass = player->GetMass();

    output.write((char*)&playerData, sizeof(PlayerData));

     // Output Exit information
    exitData.x = exit->GetPosition().x;
    exitData.y = exit->GetPosition().y;
    exitData.radius = exit->GetRadius();

    output.write((char*)&exitData, sizeof(ExitData));

    // Output Core information
    size = cores.size();
    output.write((char*)&size, sizeof(unsigned int));

    for (unsigned int i = 0; i < size; i++)
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

    for (unsigned int i = 0; i < size; i++)
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

void MainGameState::Pause()
{
    exit->Pause();
    player->Pause();
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        cores[i]->Pause();
    }
    for (unsigned int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->Pause();
    }
    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_LIGHTING_BIT | GL_ENABLE_BIT | GL_VIEWPORT_BIT);
    glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
}


void MainGameState::Resume()
{
    exit->Pause();
    player->Resume();
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        cores[i]->Resume();
    }
    for (unsigned int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->Resume();
    }
    glPopAttrib();
    glPopClientAttrib();
    SendResizeEvent();
}

void MainGameState::HandleEvents(GLFWEvent* event)
{
    switch (event->type)
    {
        case GLFWEvent::KEY:
            if (event->state == GLFW_PRESS)
            {
                switch (event->key)
                {
                    case GLFW_KEY_LEFT:
                        player->MoveLeft();
                        break;
                    case GLFW_KEY_RIGHT:
                        player->MoveRight();
                        break;
                    case GLFW_KEY_SPACE:
                        if (player->IsGrounded())
                        {
                            player->Jump();
                        } else
                        {
                            player->StopVelocity();
                        }
                        break;
                    case GLFW_KEY_ESC:
                        PushState(new PauseMenuState(game));
                        break;
                    default:
                        break;
                }
            } else
            {
                switch (event->key)
                {
                    case GLFW_KEY_LEFT:
                    case GLFW_KEY_RIGHT:
                        player->StopMoving();
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
            if (((GLfloat)event->width / (GLfloat)event->height) > (15.0f / 10.0f))
            {
                glFrustum(((GLfloat)event->width) / ((GLfloat)event->height) * (-10.0f), ((GLfloat)event->width) / ((GLfloat)event->height) * (10.0f), -10.0f, 10.0f, 80.0f, 200.0f);
            } else
            {
                glFrustum(-15.0f, 15.0f, ((GLfloat)event->height) / ((GLfloat)event->width) * (-15.0f), ((GLfloat)event->height) / ((GLfloat)event->width) * (15.0f ), 80.0f, 200.0f);
            }
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
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

    // If you win, move to the next stage
    if (player->IsExited())
    {
        LoadNextStage();
    }
    // If you die, reload the current stage
    if (player->IsDead())
    {
        LoadStage(currentStage);
    }
}

void MainGameState::Render()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glRotatef(player->GetAngle() * 180.0f / PI, 0.0f, 0.0f, -1.0f);
    gluLookAt(player->GetPosition().x, player->GetPosition().y, 150.0, player->GetPosition().x, player->GetPosition().y, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);

    // Set and render the normal view
    player->Render();
    for (unsigned int i = 0; i < cores.size(); i++)
    {
        cores[i]->Render();
    }
    for (unsigned int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->Render();
    }

    exit->Render();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

#endif

