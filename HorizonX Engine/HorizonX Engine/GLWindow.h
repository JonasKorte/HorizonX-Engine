#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Log.h"
#include "EditorDefaults.h"
#include "API.h"

namespace HX
{
	struct HX_API HX_GLWindowData
	{
		const char* windowTitle;
		int xPosition;
		int yPosition;
		int width;
		int height;
		int viewportX;
		int viewportY;
		int viewportWidth;
		int viewportHeight;
	};

	void HX_API error_callback(int error, const char* description);

	class HX_API HX_GLWindow
	{
	public:
		HX_GLWindow(const char* windowTitle, int xPosition, int yPosition, int width, int height);
		HX_GLWindow(HX_GLWindowData windowData);
		HX_GLWindow(const HX_GLWindow& window);

		bool Initialize();

		void Clear();

		bool Update();

		GLFWwindow* GetWindow();


		HX_GLWindowData GetWindowData();
		void SetWindowData(HX_GLWindowData windowData);

		~HX_GLWindow();

		void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		void SetViewport(float xPosition, float yPosition, float width, float height);


	private:
		HX_GLWindowData m_windowData;

		GLFWwindow* m_window;
	};
}