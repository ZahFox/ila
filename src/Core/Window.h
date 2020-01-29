#pragma once

#include "Core/Common.h"

namespace Ila {

struct WindowProps {
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(const std::string& title = "ila",
        unsigned int width = 1280,
        unsigned int height = 720)
        : Title(title)
        , Width(width)
        , Height(height)
    {
    }
};

class Window {
public:
    Window() = default;
    virtual ~Window() = default;

    virtual void OnUpdate() = 0;
    virtual bool IsRunning() = 0;

    static Scope<Window> Create(const WindowProps& props = WindowProps());

private:
    void operator=(const Window& window) {}
    Window(const Window& window) {}
};
}