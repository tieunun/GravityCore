/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef MENU_BASE_HXX
#define MENU_BASE_HXX

#include <vector>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glfw.h>

#include <ft2build.h>
#include FT_FREETYPE_H

class MenuBase
{
    protected:
        // Items to be displayed
        std::vector<std::string> menuItems;
        // Currently highlighted item
        unsigned short current;

    public:
        MenuBase();
        virtual ~MenuBase();
        static bool Initiate();
        static void Cleanup();

        void NextItem();
        void PreviousItem();
        virtual void SelectCurrent() = 0;
};

#endif
