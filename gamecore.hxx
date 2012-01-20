#ifndef GAMECORE_HXX
#define GAMECORE_HXX

#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glfw.h>
#include <GL/glu.h>


#include "event.cxx"

class State;

class GameCore
{
    private:
        int WINDOWWIDTH;
        int WINDOWHEIGHT;
        std::string TITLE;

        GLFWEvent* event;

        static bool exit;

        std::vector<State*> states;
        static std::queue<GLFWEvent> events;
        static int mouseX, mouseY;

        GLfloat prevFrametime, frametime;

    public:
        GameCore(std::string title);
        ~GameCore();

        static void GLFWCALL KeyCallback(int key, int state);
        static void GLFWCALL MousePosCallback(int x, int y);
        static void GLFWCALL MouseButtonCallback(int button, int state);
        static void GLFWCALL MouseWheelCallback(int position);
        static void GLFWCALL WindowResizeCallback(int width, int height);
        static int GLFWCALL WindowCloseCallback();

        void SendResizeEvent();

        int Run();
        bool Initiate();
        void Cleanup();
        void HandleEvents();
        void Process();
        void Render();
        void CheckErrors();
        // Function Pointer, implemented so that menus don't constantly render
        void (*GrabEvents)();

        void PushState(State* state);
        void PopState();
        void PopStates(unsigned int num);

        int GetWidth();
        int GetHeight();

        void SetPollEvents();
        void SetWaitEvents();
};

#endif
