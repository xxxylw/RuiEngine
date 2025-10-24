#include "repch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace RuiEngine {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(
			path.c_str(),
			&width,
			&height,
			&channels,
			0
		);
		if (!data)
		{
			RE_CORE_ERROR("Failed to load texture at path: {0}, reasion: {1}", path, stbi_failure_reason());
			RE_CORE_ASSERT(data, "Failed to load texture at path: {0}, reasion: {1}", path, stbi_failure_reason());
		}

		m_Width = width;
		m_Height = height;

		GLenum format = (channels == 4 ? GL_RGBA : GL_RGB);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, (channels == 4 ? GL_RGBA8 : GL_RGB8), m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		/* AMD 芯片 加这一句，不加的话会报异常， 在glTextureSubImage2D之前 */
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTextureSubImage2D(
			m_RendererID,
			0, 0, 0,
			m_Width, m_Height,
			format, GL_UNSIGNED_BYTE,
			data
		);
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot = 0) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}