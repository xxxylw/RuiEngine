#pragma once

#include "RuiEngine/Renderer/GraphicsContext.h"
struct GLFWwindow;

namespace RuiEngine {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}