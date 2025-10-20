#include "repch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace RuiEngine {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}