#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Log.h"
#include "EditorDefaults.h"

namespace HX
{
	struct HX_GLWindowData
	{
		const char* windowTitle;
		int xPosition;
		int yPosition;
		int width;
		int height;
		bool isEditor;
		int viewportX;
		int viewportY;
		int viewportWidth;
		int viewportHeight;
	};

	void error_callback(int error, const char* description);

	class HX_GLWindow
	{
	public:
		HX_GLWindow(const char* windowTitle, int xPosition, int yPosition, int width, int height, bool isEditor);
		HX_GLWindow(HX_GLWindowData windowData);
		HX_GLWindow(const HX_GLWindow& window);

		bool Initialize();

		bool WindowLoop();


		HX_GLWindowData GetWindowData();
		void SetWindowData(HX_GLWindowData windowData);

		~HX_GLWindow();

		void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	private:
		HX_GLWindowData m_windowData;

		GLFWwindow* m_window;
	};
}