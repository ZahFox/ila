#pragma once

#include "Core/Window.h"

namespace Ila {

class SDLWindow : public Window {
public:
    SDLWindow(const WindowProps& props);
    virtual ~SDLWindow();

    void OnUpdate() override;

    bool IsRunning() override;

private:
    void Shutdown();
};
}