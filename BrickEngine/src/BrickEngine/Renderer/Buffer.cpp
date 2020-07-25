#include "brickenginepch.h"
#include "Buffer.h"

#include "BrickEngine/Renderer/Renderer.h"

#include "BrickEngine/Platform/OpenGL/OpenGLBuffer.h"

namespace BrickEngine {



	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		BRICKENGINE_CORE_ASSERT(false, "Renderer::None is Currently not supported!"); return nullptr; break;
			case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size); break;
		}

		BRICKENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		BRICKENGINE_CORE_ASSERT(false, "Renderer::None is Currently not supported!"); return nullptr; break;
			case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(indices, count); break;
		}

		BRICKENGINE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
