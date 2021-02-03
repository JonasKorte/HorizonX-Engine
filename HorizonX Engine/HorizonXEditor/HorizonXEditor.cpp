#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Viewport.h"
#include "GLWindow.h"
#include "UIManager.h"
#include "Registry.h"
#include <MeshRenderer.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace HX;
using namespace HXEditor;
using namespace HXEditor::Components;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
    LOG("HorizonX Engine v1.0 - Jonas Korte 2021");

    NEWLINE();
    NEWLINE();
    NEWLINE();

    LOGINFO("Booting Editor...");

    NEWLINE();
    NEWLINE();


	GLWindow* window = new GLWindow("HorizonX Editor v1.0 - <OpenGL 3.3>", 0, 0, 1920, 1080);

	if (!window->Initialize())
	{
		return -1;
	}

	if (!gladLoadGLLoader(window->GetLoadProc()))
	{
		delete window;

		glfwTerminate();

		return -1;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	auto& io = ImGui::GetIO();

	unsigned char* p;
	int w, h;

	io.Fonts->GetTexDataAsRGBA32(&p, &w, &h);

	ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	ImGui::StyleColorsDark();

	HXEC_Viewport* viewport = new HXEC_Viewport("Scene Viewport");

	HX_Component viewportComponent = viewport->MakeComponent();

	HX_ID viewportID = HX_UIManager::RegisterComponent(viewportComponent);

	ImGui::NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();

	HX_UIManager::LoadComponent(viewportID);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGui::EndFrame();

	ShaderToggles toggles = {};

	toggles.hasVertex = true;
	toggles.hasFragment = true;
	toggles.hasGeometry = false;
	toggles.hasTesselation = false;
	toggles.hasCompute = false;

	Shader* shader = new Shader("L:/HorizonX-Engine/HorizonX Engine/Build/Shaders/Default.hxshader", toggles);

	if (!shader->LoadShader())
	{
		LOGERR("Failed to load shader!");

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();

		ImGui::DestroyContext();

		delete window;

		glfwTerminate();
		return -1;
	}


	Material* material = new Material(shader);

	Vertex v1 = {};

	v1.position.x = 0.0f;
	v1.position.y = 1.0f;
	v1.position.z = 0.0f;

	Vertex v2 = {};

	v2.position.x = -1.0f;
	v2.position.y = -1.0f;
	v2.position.z = 0.0f;

	Vertex v3 = {};

	v3.position.x = 1.0f;
	v3.position.y = -1.0f;
	v3.position.z = 0.0f;

	Mesh mesh;

	mesh.push_back(v1);
	mesh.push_back(v2);
	mesh.push_back(v3);

	MeshRenderer* meshRenderer = new MeshRenderer(mesh, material);

	meshRenderer->Initialize();

	while (!glfwWindowShouldClose(window->GetWindow()))
	{
		window->Clear();

		ImGui::NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();

		HX_UIManager::UpdateComponents();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		meshRenderer->Draw();

		ImGui::EndFrame();

		window->Update();
	}

	HX_UIManager::UnloadComponent(viewportID);

	HX_UIManager::UnregisterComponent(viewportID);

	delete meshRenderer;

	delete material;

	delete shader;

	delete window;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();

	glfwTerminate();

    return 0;
}