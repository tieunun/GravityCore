/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef SHAPE_CXX
#define SHAPE_CXX

#include "shape.hxx"

GLuint Shape::buffers[VAOCOUNT][NumVBOs];
GLuint Shape::indexCount[VAOCOUNT];
GLuint Shape::VAO[VAOCOUNT];

Shape::Shape()
{
    body = NULL;
    fixture = NULL;
}

Shape::~Shape()
{
}

bool Shape::Initiate(float radius, unsigned int stacks, unsigned int slices)
{
    GLuint numVertices = 0;
    GLuint numFaces = 0;
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLuint> indices;
    std::string inString;
    std::string dummy;
    std::string fileType;
    std::string fileVersion;
    GLfloat tempFloat;
    GLuint tempUInt;
    GLuint faceGon;
    std::ifstream input;
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
    normals.clear();

    input.open("models/cube.ply", std::ifstream::in);
    if (input.is_open())
    {
        input >> inString;
        if (inString != "ply")
        {
            input.close();
            inString = "end_header";
        }
        input >> inString;
        while (inString != "end_header")
        {
            if (inString == "format")
            {
                input >> fileType;
                input >> fileVersion;
            } else if (inString == "element")
            {
                input >> inString;
                if (inString == "vertex")
                {
                    input >> inString;
                    std::stringstream(inString) >> numVertices;
                } else if (inString == "face")
                {
                    input >> inString;
                    std::stringstream(inString) >> numFaces;
                }
            } else if (inString == "property")
            {
                input >> inString;
                // ignore type for now
                input >> inString;
                if ((inString == "x") || (inString == "y") || (inString == "z"))
                {
                } else if ((inString == "nx") || (inString == "ny") || (inString == "nz"))
                {
                } else
                {
                    getline(input, dummy);
                }

            } else if (inString == "comment")
            {
                getline(input, dummy);
            } else
            {
                break;
            }
            input >> inString;
        }
        for (unsigned int i = 0; i < numVertices; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                input >> inString;
                std::stringstream(inString) >> tempFloat;
                vertices.push_back(tempFloat);
            }
            for (unsigned int j = 0; j < 3; j++)
            {
                input >> inString;
                std::stringstream(inString) >> tempFloat;
                normals.push_back(tempFloat);
            }
        }
        // Only handles one type of face for now
        for (unsigned int i = 0; i < numFaces; i++)
        {
            input >> inString;
            std::stringstream(inString) >> faceGon;
            for (unsigned int j = 0; j < faceGon; j++)
            {
                input >> inString;
                std::stringstream(inString) >> tempUInt;
                indices.push_back(tempUInt);
            }
        }

        input.close();



        glBindVertexArray(VAO[CUBE]);

            glGenBuffers(NumVBOs, buffers[CUBE]);
            glBindBuffer(GL_ARRAY_BUFFER, buffers[CUBE][Vertices]);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
            glVertexPointer(3, GL_FLOAT, 0, NULL);
            glEnableClientState(GL_VERTEX_ARRAY);

            glBindBuffer(GL_ARRAY_BUFFER, buffers[CUBE][Normals]);
            glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);
            glNormalPointer(GL_FLOAT, 0, NULL);
            glEnableClientState(GL_NORMAL_ARRAY);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[CUBE][Indices]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

        indexCount[CUBE] = indices.size();
        glBindVertexArray(0);
    } else
    {
        VAO[CUBE] = VAO[SPHERE];
        buffers[CUBE][Indices] = buffers[SPHERE][Indices];
        indexCount[CUBE] = indexCount[SPHERE];
    }
    indices.clear();
    vertices.clear();
    normals.clear();

    return (true);
}

void Shape::Cleanup()
{
    for (unsigned int i = 0; i < VAOCOUNT; i++)
    {
        glBindVertexArray(i);
        glDeleteBuffers(NumVBOs, buffers[i]);
    }
    glDeleteVertexArrays(VAOCOUNT, VAO);
}

bool Shape::CreateAsCircle(float x, float y, float radius, bool dynamic, b2World* world)
{
    circle = true;
    this->radius = radius;
    this->dynamic = dynamic;
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->position.Set(x, y);
    bodyDef->userData = (void*)this;

    b2CircleShape* shape = new b2CircleShape();
    shape->m_radius = radius;

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;

    fixtureDef->density = 1.0f;
    fixtureDef->friction = 1.0f;
    fixtureDef->restitution = 0.4f;
    fixtureDef->userData = (void*)masslessFixture;

    if (dynamic)
    {
        bodyDef->type = b2_dynamicBody;
    } else
    {
        bodyDef->type = b2_staticBody;
    }
    body = world->CreateBody(bodyDef);
    fixture = body->CreateFixture(fixtureDef);


    delete (bodyDef);
    delete (fixtureDef);
    delete (shape);
    return (true);
}

bool Shape::CreateAsRectangle(float x, float y, float halfWidth, float halfHeight, float angle, bool dynamic, b2World* world)
{
    circle = false;
    this->halfWidth = halfWidth;
    this->halfHeight = halfHeight;
    this->dynamic = dynamic;
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->position.Set(x, y);
    // Set the dynamic / static type accordingly
    bodyDef->type = (dynamic ? b2_dynamicBody : b2_staticBody);
    bodyDef->angle = angle;
    bodyDef->userData = (void*)this;

    b2PolygonShape* shape = new b2PolygonShape();
    shape->SetAsBox(halfWidth, halfHeight);

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;

    fixtureDef->density = 1.0f;
    fixtureDef->friction = 0.3f;
    fixtureDef->userData = (void*)masslessFixture;

    body = world->CreateBody(bodyDef);
    fixture = body->CreateFixture(fixtureDef);

    delete (bodyDef);
    delete (fixtureDef);
    delete (shape);
    return (true);
}

bool Shape::CreateAsExit(float x, float y, float radius, b2World* world)
{
    circle = true;
    this->radius = radius;
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->position.Set(x, y);
    bodyDef->userData = (void*)this;
    bodyDef->type = b2_staticBody;

    b2CircleShape* shape = new b2CircleShape();
    shape->m_radius = radius;

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;

    fixtureDef->density = 1.0f;
    fixtureDef->friction = 1.0f;
    fixtureDef->restitution = 0.4f;
    fixtureDef->isSensor = true;
    fixtureDef->userData = (void*)exitSensor;

    body = world->CreateBody(bodyDef);
    fixture = body->CreateFixture(fixtureDef);

    delete (bodyDef);
    delete (fixtureDef);
    delete (shape);
    return (true);
}

Shape* Shape::CreateCircle(float x, float y, float radius, bool dynamic, b2World* world)
{
    Shape* output = new Shape();
    output->CreateAsCircle(x, y, radius, dynamic, world);
    return (output);
}

Shape* Shape::CreateRectangle(float x, float y, float halfWidth, float halfHeight, float angle, bool dynamic, b2World* world)
{
    Shape* output = new Shape();
    output->CreateAsRectangle(x, y, halfWidth, halfHeight, angle, dynamic, world);
    return (output);
}

Shape* Shape::CreateExit(float x, float y, float radius, b2World* world)
{
    Shape* output = new Shape();
    output->CreateAsExit(x, y, radius, world);
    return (output);
}

void Shape::Destroy(b2World* world)
{
    if (body)
    {
        world->DestroyBody(body);
        body = NULL;
        fixture = NULL;
    }
}

void Shape::Process()
{
}

void Shape::Render()
{
    if (circle)
    {
        glBindVertexArray(VAO[SPHERE]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[SPHERE][Indices]);
        glPushMatrix();
            glColor3f(0.0f, 0.0f, 1.0f);
            glTranslatef(body->GetWorldCenter().x, body->GetWorldCenter().y, 0.0f);
            glScalef(radius, radius, radius);
            glDrawElements(GL_TRIANGLE_STRIP, indexCount[SPHERE], GL_UNSIGNED_INT, NULL);
        glPopMatrix();
        glBindVertexArray(0);
    } else
    {
        glBindVertexArray(VAO[CUBE]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[CUBE][Indices]);
        glPushMatrix();
            glColor3f(0.0f, 1.0f, 0.0f);
            glTranslatef(body->GetWorldCenter().x, body->GetWorldCenter().y, 0.0f);
            glScalef(halfWidth, halfHeight, 1.0f);
            glDrawElements(GL_QUADS, indexCount[CUBE], GL_UNSIGNED_INT, NULL);
        glPopMatrix();
        glBindVertexArray(0);
    }
}

void Shape::Pause()
{
}

void Shape::Resume()
{

}

void Shape::Impulse(float x, float y)
{
    body->SetLinearVelocity(b2Vec2(x, y) + body->GetLinearVelocity());
}

b2Vec2 Shape::GetPosition()
{
    return (body->GetPosition());
}

float Shape::GetHalfWidth()
{
    return (halfWidth);
}

float Shape::GetHalfHeight()
{
    return (halfHeight);
}

float Shape::GetAngle()
{
    return (body->GetAngle());
}

float Shape::GetRadius()
{
    return (radius);
}

bool Shape::IsDynamic()
{
    return (dynamic);
}

#endif
