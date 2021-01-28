#include <iostream>
#include <GLWindow.h>
#include "Viewport.h"
#include "UIManager.h"
#include "Registry.h"

using namespace HX;
using namespace HXEditor;
using namespace HXEditor::Components;

int main()
{
    LOG("HorizonX Engine v1.0 - Jonas Korte 2021");

    NEWLINE();
    NEWLINE();
    NEWLINE();

    LOGINFO("Booting Editor...");

    LOG("Executable Path: ");
    LOG(GetExecutablePath());

    NEWLINE();
    NEWLINE();

    HX_GLWindow* wnd = new HX_GLWindow("HorizonX Editor v1.0 - <OpenGL 4.6>", 0, 0, 1920, 1080, false);

    if (!wnd->Initialize())
    {
        return -1;
    }

    bool shouldClose = false;

    while (!shouldClose)
    {
        wnd->Clear();


        shouldClose = !wnd->Update();
    }

    delete wnd;

    return 0;
}