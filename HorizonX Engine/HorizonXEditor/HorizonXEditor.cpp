#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include <GLWindow.h>
#include "imgui_impl_opengl3.h"
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

    HX::HX_GLWindow* wnd = new HX::HX_GLWindow("HorizonX Editor v1.0 - <OpenGL 3.3>", 0, 0, 1920, 1080, true);

    if (!wnd->Initialize())
    {
        return -1;
    }

    gladLoadGL();

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    auto& _io = ImGui::GetIO();

    _io.DisplaySize = ImVec2(wnd->GetWindowData().width, wnd->GetWindowData().height);
    _io.DeltaTime = 1.f / 60.f;

    unsigned char* p;
    int w, h;

    _io.Fonts->GetTexDataAsRGBA32(&p, &w, &h);

    ImGui_ImplGlfw_InitForOpenGL(wnd->GetWindow(), true);
    ImGui_ImplOpenGL3_Init(NULL);

    //HXEC_Viewport* viewport = new HXEC_Viewport(wnd, "Scene View");

    //HX_Component viewportComponent = viewport->MakeComponent();

    // (viewportComponent.id == "")
    //{
        //return -1;
   // }

    //HX_UIManager::LoadComponent(viewportComponent.id);

    bool shouldClose = false;

    while (!shouldClose)
    {
        wnd->Clear();

        ImGui::NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        //HX_UIManager::UpdateComponents()

        bool show_demo = true;

        ImGui::ShowDemoWindow(&show_demo);

        show_demo = true;

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        ImGui::EndFrame();


        shouldClose = !wnd->Update();
    }


    //HX_UIManager::UnloadComponent(viewportComponent.id);

    //HX_UIManager::UnregisterComponent(viewportComponent.id);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    delete wnd;

    return 0;
}