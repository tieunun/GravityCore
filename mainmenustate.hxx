/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef MAINMENU_STATE_HXX
#define MAINMENU_STATE_HXX

#include <vector>
#include <string>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "gamecore.hxx"
#include "maingamestate.hxx"
#include "creditsstate.hxx"
#include "event.cxx"
#include "menubase.hxx"
#include "fontbase.hxx"

class MainMenuState : public MenuBase, public FontBase, public State
{
    private:
    public:
        MainMenuState(GameCore* game);
        ~MainMenuState();

        void Create();
        void Destroy();

        void Pause();
        void Resume();

        void HandleEvents(GLFWEvent* event);
        void Process(float frameTime);
        void Render();

        void SelectCurrent();
};

#endif
