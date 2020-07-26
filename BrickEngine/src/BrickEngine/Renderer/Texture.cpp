#include "brickenginepch.h"
#include "Texture.h"

#include "Renderer.h"
#include "BrickEngine/Platform/OpenGL/OpenGLTexture.h"

namespace BrickEngine {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		BRICKENGINE_CORE_ASSERT(false, "Renderer::None is Currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLTexture2D>(path);
		}

		BRICKENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
