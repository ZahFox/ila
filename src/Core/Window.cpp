#include "Platform/SDL/SDL.h"

namespace Ila {

Scope<Window> Window::Create(const WindowProps& props)
{
    return CreateScope<SDLWindow>(props);
}
}