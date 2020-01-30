#include "SDL.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace Ila {

static SDL_Window* window = nullptr;
static SDL_GLContext context = nullptr;
static bool IS_RUNNING = false;

void InitOpenGL()
{
    int major = 3;
    int minor = 2;

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE)
        != 0) {
        // ILA_DEBUG_LOG('ERROR',
        //     "Could not set core OpenGL profile");
    }

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major) != 0) {
        // ILA_DEBUG_LOG("ERROR",
        //     "Could not set major OpenGL version to %d: %s",
        //     major, SDL_GetError());
    }

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor) != 0) {
        // ILA_DEBUG_LOG("ERROR",
        //     "Could not set minor OpenGL version to %d: %s",
        //     minor, SDL_GetError());
    }
}

SDLWindow::SDLWindow(const WindowProps& props)
{
    InitOpenGL();

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        props.Title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        props.Width,
        props.Height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        ILA_DEBUG_LOG("ERROR", "%s", glewGetErrorString(res));
        throw std::runtime_error("Render device could not be initialized");
    }

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glFrontFace(GL_CW);

    IS_RUNNING = true;
}

SDLWindow::~SDLWindow()
{
    if (context) {
        SDL_GL_DeleteContext(context);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}

void SDLWindow::OnUpdate()
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT: {
            IS_RUNNING = false;
            break;
        }
        default: {
            break;
        }
        }
    }

    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}

bool SDLWindow::IsRunning()
{
    return IS_RUNNING;
}
}