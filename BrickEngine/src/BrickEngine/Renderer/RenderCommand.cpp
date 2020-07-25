#include "brickenginepch.h"
#include "RenderCommand.h"

#include "BrickEngine/Platform/OpenGL/OpenGLRendererAPI.h"

namespace BrickEngine {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}
