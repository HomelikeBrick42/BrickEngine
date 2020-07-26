#include "brickenginepch.h"
#include "BrickEngine/Renderer/Shader.h"

#include "BrickEngine/Renderer/Renderer.h"

#include "BrickEngine/Platform/OpenGL/OpenGLShader.h"

namespace BrickEngine {

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		BRICKENGINE_CORE_ASSERT(false, "Renderer::None is Currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLShader(filepath);
		}

		BRICKENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		BRICKENGINE_CORE_ASSERT(false, "Renderer::None is Currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		BRICKENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
