#include "repch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace RuiEngine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		RE_CORE_ASSERT(windowHandle, "Window handle is null !");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RE_CORE_ASSERT(status, "Failed to initialize Glad !");

		RE_CORE_INFO("OpenGL Info:");
		RE_CORE_INFO("	Vendor:		{0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		RE_CORE_INFO("	Renderer:	{0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		RE_CORE_INFO("	Version:	{0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	
}