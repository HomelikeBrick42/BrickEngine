#include "brickenginepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace BrickEngine {



	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		BRICKENGINE_CORE_ASSERT(m_WindowHandle, "Window Handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BRICKENGINE_CORE_ASSERT(status, "Failed to initalize Glad!");

		BRICKENGINE_CORE_INFO("OpenGL Info:");
		BRICKENGINE_CORE_INFO("    Vendor: {0}", glGetString(GL_VENDOR));
		BRICKENGINE_CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
		BRICKENGINE_CORE_INFO("    Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
