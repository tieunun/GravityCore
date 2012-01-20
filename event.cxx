/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef EVENT_CXX
#define EVENT_CXX
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>

struct GLFWEvent
{
    enum
    {
        KEY = 1,
        MOUSE_POS,
        BUTTON,
        MOUSE_WHEEL,
        RESIZE
    } type;
    GLubyte state;
    GLint key;
    GLint button;
    GLint x;
    GLint y;
    GLint width;
    GLint height;
    GLint direction;
};

#endif
