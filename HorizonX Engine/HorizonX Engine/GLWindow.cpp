#include "GLWindow.h"

namespace HX
{
	GLWindow::GLWindow(const char* windowTitle, int xPosition, int yPosition, int width, int height)
	{
		this->m_windowData.windowTitle = windowTitle;
		this->m_windowData.xPosition = xPosition;
		this->m_windowData.yPosition = yPosition;
		this->m_windowData.width = width;
		this->m_windowData.height = height;
		this->m_windowData.viewportX = 0;
		this->m_windowData.viewportY = 0;
		this->m_windowData.viewportWidth = width;
		this->m_windowData.viewportWidth = height;

		this->m_window = NULL;
	}

	GLWindow::GLWindow(GLWindowData windowData)
	{
		this->m_windowData = windowData;
		this->m_window = NULL;
	}

	GLWindow::GLWindow(const GLWindow& window)
	{
		this->m_windowData = window.m_windowData;
		this->m_window = window.m_window;
	}

	GLWindow::~GLWindow()
	{
		LOGINFO("Quiting...");

		glfwDestroyWindow(this->m_window);

		glfwTerminate();
	}

	bool GLWindow::Initialize()
	{
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
		this->m_window = glfwCreateWindow(this->m_windowData.width, this->m_windowData.height, this->m_windowData.windowTitle, monitor, NULL);

		if (!this->m_window)
		{
			LOGERR("Failed to create window!");

			return false;
		}

		LOGINFO("Window initialized successfully!");

		glfwMakeContextCurrent(this->m_window);

		glfwSwapInterval(1);

		glfwSetWindowUserPointer(this->m_window, this);

		LOGINFO("Loading OpenGL...");

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOGERR("Failed to load OpenGL!");

			return false;
		}

		LOGINFO("OpenGL loaded successfully!");

		auto framebuffer_size_func = [](GLFWwindow* window, int width, int height)
		{
			static_cast<GLWindow*>(glfwGetWindowUserPointer(window))->framebuffer_size_callback(window, width, height);
		};

		glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_func);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glViewport(this->m_windowData.viewportX, this->m_windowData.viewportY, this->m_windowData.viewportWidth, this->m_windowData.viewportHeight);

		return true;
	}

	void GLWindow::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	bool GLWindow::Update()
	{
		glfwSwapBuffers(this->m_window);
		glfwPollEvents();

		return !glfwWindowShouldClose(this->m_window);
	}

	void error_callback(int error, const char* description)
	{
		LOGERR(description);
	}

	void GLWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void GLWindow::SetViewport(float xPosition, float yPosition, float width, float height)
	{
		this->m_windowData.viewportX = xPosition;
		this->m_windowData.viewportY = yPosition;
		this->m_windowData.width = width;
		this->m_windowData.height = height;
	}

	GLFWwindow* GLWindow::GetWindow()
	{
		return this->m_window;
	}

	GLWindowData GLWindow::GetWindowData()
	{
		return this->m_windowData;
	}
}