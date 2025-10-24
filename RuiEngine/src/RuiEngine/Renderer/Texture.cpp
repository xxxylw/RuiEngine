#include "repch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace RuiEngine {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: RE_CORE_ASSERT(false, "RendererAPI::None is currently not support!");
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}
	}
}