#ifndef WINDOW_INCLUDED_H
#define WINDOW_INCLUDED_H

#include <iostream>
#include <string>

namespace Ila {

class Window {
public:
    Window(int width, int height, const std::string& title);
    virtual ~Window();

    void dersp() {};

private:
    void operator=(const Window& window) {}
    Window(const Window& window) {}
};
}

#endif