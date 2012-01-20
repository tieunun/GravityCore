/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef CORE_CXX
#define CORE_CXX

#include "core.hxx"

GLuint Core::buffers[VAOCOUNT][NumVBOs];
GLuint Core::indexCount[VAOCOUNT];
GLuint Core::VAO[VAOCOUNT];

Core::Core()
{
    body = NULL;
    fixture = NULL;
}

Core::~Core()
{
}

bool Core::Initiate(float radius, unsigned int stacks, unsigned int slices)
{
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    glGenVertexArrays(VAOCOUNT, VAO);

    for (unsigned int stackNumber = 0; stackNumber <= stacks; ++stackNumber)
    {
        for (unsigned int sliceNumber = 0; sliceNumber < slices; ++sliceNumber)
        {
            float theta = stackNumber * PI / stacks;
            float phi = sliceNumber * 2 * PI / slices;
            float sinTheta = sin(theta);
            float sinPhi = sin(phi);
            float cosTheta = cos(theta);
            float cosPhi = cos(phi);
            vertices.push_back(radius * cosPhi * sinTheta);
            vertices.push_back(radius * sinPhi * sinTheta);
            vertices.push_back(radius * cosTheta);
        }
    }

    for (unsigned int stackNumber = 0; stackNumber < stacks; ++stackNumber)
    {
        for (unsigned int sliceNumber = 0; sliceNumber <= slices; ++sliceNumber)
        {
            indices.push_back((stackNumber * slices) + (sliceNumber % slices));
            indices.push_back(((stackNumber + 1) * slices) + (sliceNumber % slices));
        }
    }

    glBindVertexArray(VAO[SPHERE]);

        glGenBuffers(NumVBOs, buffers[SPHERE]);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[SPHERE][Vertices]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, NULL);
        glEnableClientState(GL_VERTEX_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[SPHERE][Normals]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
        glNormalPointer(GL_FLOAT, 0, NULL);
        glEnableClientState(GL_NORMAL_ARRAY);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[SPHERE][Indices]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    indexCount[SPHERE] = indices.size();

    glBindVertexArray(0);
    indices.clear();
    vertices.clear();

    return (true);
}

void Core::Cleanup()
{
    for (unsigned int i = 0; i < VAOCOUNT; i++)
    {
        glBindVertexArray(i);
        glDeleteBuffers(NumVBOs, buffers[i]);
    }
    glDeleteVertexArrays(VAOCOUNT, VAO);
}

bool Core::Create(float x, float y, float radius, float mass, b2World* world)
{
    this->mass = mass;
    this->radius = radius;
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->position.Set(x, y);
    bodyDef->type = b2_staticBody;
    bodyDef->userData = (void*)this;

    b2CircleShape* shape = new b2CircleShape();
    shape->m_radius = radius;

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;
    fixtureDef->density = mass / (radius * radius * PI);
    fixtureDef->friction = 0.1f;
    fixtureDef->restitution = 0.0f;
    fixtureDef->userData = (void*)massiveFixture;

    body = world->CreateBody(bodyDef);
    fixture = body->CreateFixture(fixtureDef);

    delete (bodyDef);
    delete (fixtureDef);
    delete (shape);
    return (true);
}

Core* Core::CreateCore(float x, float y, float radius, float mass, b2World* world)
{
    Core* output = new Core();
    output->Create(x, y, radius, mass, world);
    return (output);
}

void Core::Destroy(b2World* world)
{
    if (body)
    {
        world->DestroyBody(body);
        body = NULL;
        fixture = NULL;
    }
}

void Core::Process()
{
}

void Core::Render()
{
    glBindVertexArray(VAO[SPHERE]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[SPHERE][Indices]);
    glPushMatrix();
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(body->GetWorldCenter().x, body->GetWorldCenter().y, 0.0f);
        glScalef(radius, radius, radius);
        glDrawElements(GL_TRIANGLE_STRIP, indexCount[SPHERE], GL_UNSIGNED_INT, NULL);
    glPopMatrix();
    glBindVertexArray(0);
}

void Core::Pause()
{
}

void Core::Resume()
{

}

b2Vec2 Core::GetPosition()
{
    return (body->GetWorldCenter());
}

float Core::GetMass()
{
    return (mass);
}

float Core::GetRadius()
{
    return (radius);
}

#endif
