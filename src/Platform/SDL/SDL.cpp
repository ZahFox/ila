#include "SDL.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace Ila {

static SDL_Window* window = nullptr;
static SDL_GLContext context = nullptr;
static bool IS_RUNNING = false;

bool SetOpenGLAttributes()
{
    int major = 3;
    int minor = 2;

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE)
        != 0) {
        ILA_DEBUG_LOG("SDL", "could not set core OpenGL profile");
        return false;
    }

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major) != 0) {
        ILA_DEBUG_LOG("SDL", "could not set major OpenGL version to %d: %s", major, SDL_GetError());
        return false;
    }

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor) != 0) {
        ILA_DEBUG_LOG("SDL", "could not set minor OpenGL version to %d: %s", minor, SDL_GetError());
        return false;
    }

    return true;
}

SDLWindow::SDLWindow(const WindowProps& props)
{

    int initialized = SDL_Init(SDL_INIT_VIDEO);
    if (initialized != 0) {
        ILA_DEBUG_LOG("SDL", "failed to initialize SDL: %s", SDL_GetError());
        Shutdown();
        return;
    }

    if (!SetOpenGLAttributes()) {
        Shutdown();
        return;
    }

    window = SDL_CreateWindow(
        props.Title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        props.Width,
        props.Height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
        ILA_DEBUG_LOG("SDL", "failed to initialize SDL: %s", SDL_GetError());
        Shutdown();
        return;
    }

    context = SDL_GL_CreateContext(window);
    if (!context) {
        ILA_DEBUG_LOG("SDL", "failed to initialize SDL: %s", SDL_GetError());
        Shutdown();
        return;
    }

    glewExperimental = GL_TRUE;
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        ILA_DEBUG_LOG("GLEW", "%s", glewGetErrorString(res));
        Shutdown();
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glFrontFace(GL_CW);

    IS_RUNNING = true;
}

SDLWindow::~SDLWindow()
{
    Shutdown();
}

void SDLWindow::OnUpdate()
{
    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

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

    SDL_GL_SwapWindow(window);
}

bool SDLWindow::IsRunning()
{
    return IS_RUNNING;
}

void SDLWindow::Shutdown()
{
    if (context) {
        SDL_GL_DeleteContext(context);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}
}