#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Viewport.h"
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

	LOGINFO("Initializing GLFW...");

	if (!glfwInit())
	{
		LOGERR("Failed to initialized GLFW!");
		return false;
	}

	LOGINFO("GLFW Initialized successfully!");

	glfwSetErrorCallback(error_callback);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


	LOGINFO("Creating window...");


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_MAXIMIZED, 1);

	GLFWwindow* editorWindow = glfwCreateWindow(1920, 1080, "HorizonX Engine v1.0 - <OpenGL 3.3>", NULL, NULL);

	if (!editorWindow)
	{
		LOGERR("Failed to create window!");

		return false;
	}

	LOGINFO("Window initialized successfully!");

	glfwMakeContextCurrent(editorWindow);

	glfwSwapInterval(1);

	LOGINFO("Loading OpenGL...");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOGERR("Failed to load OpenGL!");

		return false;
	}

	LOGINFO("OpenGL loaded successfully!");


	glfwSetFramebufferSizeCallback(editorWindow, framebuffer_size_callback);

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

	glViewport(0, 0, 1920, 1080);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	auto& io = ImGui::GetIO();

	unsigned char* p;
	int w, h;

	io.Fonts->GetTexDataAsRGBA32(&p, &w, &h);

	ImGui_ImplGlfw_InitForOpenGL(editorWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	ImGui::StyleColorsDark();

	HXEC_Viewport* viewport = new HXEC_Viewport("Scene Viewport");

	HX_Component viewportComponent = viewport->MakeComponent();

	HX_ID viewportID = HX_UIManager::RegisterComponent(viewportComponent);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	ImGui::NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();

	HX_UIManager::LoadComponent(viewportID);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(editorWindow);
	glfwPollEvents();

	ImGui::EndFrame();

	while (!glfwWindowShouldClose(editorWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		ImGui::NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();

		HX_UIManager::UpdateComponents();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(editorWindow);
		glfwPollEvents();

		ImGui::EndFrame();
	}

	HX_UIManager::UnloadComponent(viewportID);

	HX_UIManager::UnregisterComponent(viewportID);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();

	glfwTerminate();

    return 0;
}