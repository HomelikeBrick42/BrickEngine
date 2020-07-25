#include "brickenginepch.h"
#include "BrickEngine/Renderer/VertexArray.h"

#include "BrickEngine/Renderer/Renderer.h"

#include "BrickEngine/Platform/OpenGL/OpenGLVertexArray.h"

namespace BrickEngine {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		BRICKENGINE_CORE_ASSERT(false, "Renderer::None is Currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();
		}

		BRICKENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
