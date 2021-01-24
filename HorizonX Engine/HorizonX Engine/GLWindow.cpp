#include "GLWindow.h"

namespace HX
{
	HX_GLWindow::HX_GLWindow(const char* windowTitle, int xPosition, int yPosition, int width, int height, bool isEditor)
	{
		this->m_windowData.windowTitle = windowTitle;
		this->m_windowData.xPosition = xPosition;
		this->m_windowData.yPosition = yPosition;
		this->m_windowData.width = width;
		this->m_windowData.height = height;
		this->m_windowData.isEditor = isEditor;

		if (this->m_windowData.isEditor)
		{
			this->m_windowData.viewportX = HX_EditorDefaults::defaultViewportX;
			this->m_windowData.viewportY = HX_EditorDefaults::defaultViewportY;
			this->m_windowData.viewportWidth = HX_EditorDefaults::defaultViewportWidth;
			this->m_windowData.viewportWidth = HX_EditorDefaults::defaultViewportWidth;
		}
		else
		{
			this->m_windowData.viewportX = 0;
			this->m_windowData.viewportY = 0;
			this->m_windowData.viewportWidth = 1920;
			this->m_windowData.viewportWidth = 1080;
		}

		this->m_window = NULL;
	}

	HX_GLWindow::HX_GLWindow(HX_GLWindowData windowData)
	{
		this->m_windowData = windowData;
		this->m_window = NULL;
	}

	HX_GLWindow::HX_GLWindow(const HX_GLWindow& window)
	{
		this->m_windowData = window.m_windowData;
		this->m_window = window.m_window;
	}

	HX_GLWindow::~HX_GLWindow()
	{
		LOGINFO("Quiting...");

		glfwDestroyWindow(this->m_window);

		glfwTerminate();
	}

	bool HX_GLWindow::Initialize()
	{
		LOGINFO("Initializing GLFW...");

		if (!glfwInit())
		{
			LOGERR("Failed to initialized GLFW!");
			return false;
		}

		LOGINFO("GLFW Initialized successfully!");

		glfwSetErrorCallback(error_callback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

		GLFWmonitor* monitor;

		if (this->m_windowData.isEditor)
		{
			monitor = NULL;

			glfwWindowHint(GLFW_MAXIMIZED, 1);
		}
		else
		{
			monitor = glfwGetPrimaryMonitor();
		}

		glfwWindowHint(GLFW_RED_BITS, 8);
		glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8);
		glfwWindowHint(GLFW_ALPHA_BITS, 8);
		glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		LOGINFO("Creating window...");

		this->m_window = glfwCreateWindow(this->m_windowData.width, this->m_windowData.height, this->m_windowData.windowTitle, monitor, NULL);

		if (!this->m_window)
		{
			LOGERR("Failed to create window!");

			return false;
		}

		LOGINFO("Window initialized successfully!");

		glfwMakeContextCurrent(this->m_window);

		glfwSetWindowUserPointer(this->m_window, this);

		auto framebuffer_size_func = [](GLFWwindow* window, int width, int height)
		{
			static_cast<HX_GLWindow*>(glfwGetWindowUserPointer(window))->framebuffer_size_callback(window, width, height);
		};

		glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_func);

		LOGINFO("Loading OpenGL...");

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOGERR("Failed to load OpenGL!");

			return false;
		}

		LOGINFO("OpenGL loaded successfully!");

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glViewport(this->m_windowData.viewportX, this->m_windowData.viewportY, this->m_windowData.viewportWidth, this->m_windowData.viewportHeight);

		return true;
	}

	bool HX_GLWindow::WindowLoop()
	{
		while (!glfwWindowShouldClose(this->m_window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glfwSwapBuffers(this->m_window);
			glfwPollEvents();
		}

		return true;
	}

	void error_callback(int error, const char* description)
	{
		LOGERR(description);
	}

	void HX_GLWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		if (this->m_windowData.isEditor)
		{
			return;
		}
		else
		{
			glViewport(0, 0, width, height);
		}
	}
}