#include <iostream>
#include <GLWindow.h>
#include "Viewport.h"

int main()
{
    LOG("HorizonX Engine v1.0 - Jonas Korte 2021");

    NEWLINE();
    NEWLINE();

    LOGINFO("Booting Editor...");

    HX::HX_GLWindow* wnd = new HX::HX_GLWindow("HorizonX Editor v1.0 - <OpenGL 4>", 0, 0, 1920, 1080, true);

    if (!wnd->Initialize())
    {
        return -1;
    }

    bool shouldClose = false;

    while (!shouldClose)
    {
        wnd->Clear();

        // Render

        // Update GUI


        shouldClose = !wnd->Update();
    }

    delete wnd;

    return 0;
}