#include "Core/Window.h"

using namespace Ila;

int main()
{
    ILA_CORE_LOG("STARTUP", "INFO", "ila is starting up");
    auto window = Window::Create();
    return 0;
}
