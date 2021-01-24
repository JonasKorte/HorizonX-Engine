#include <iostream>
#include <GLWindow.h>
#include "Viewport.h"
#include "UIManager.h"

using namespace HX;
using namespace HXEditor;
using namespace HXEditor::Components;

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

    HXEC_Viewport* viewport = new HXEC_Viewport(wnd, "Scene View");

    HX_Component viewportComponent = viewport->MakeComponent();

    HX_UIManager::RegisterComponent(viewportComponent);

    HX_UIManager::LoadComponent(viewportComponent.id);

    bool shouldClose = false;

    while (!shouldClose)
    {
        wnd->Clear();

        // Render

        // Update GUI
        HX_UIManager::UpdateComponents();

        shouldClose = !wnd->Update();
    }

    HX_UIManager::UnloadComponent(viewportComponent.id);

    HX_UIManager::UnregisterComponent(viewportComponent.id);

    delete wnd;

    return 0;
}