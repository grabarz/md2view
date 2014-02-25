//----------------------------------------------------------------------------------------------------

#include "Application.hpp"

#include <exception>

#include <SDL2/SDL.h>
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

ApplicationContext::ApplicationContext()
{
}
//----------------------------------------------------------------------------------------------------

Application::Application(const ApplicationContext& ctx)
	: context {ctx}
	, window {nullptr, SDL_DestroyWindow}
{
}
//----------------------------------------------------------------------------------------------------

void Application::init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	window.reset(SDL_CreateWindow("md2view", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			context.width, context.height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN));

	if (window == nullptr)
		throw std::runtime_error("creating window failed!");

	glContext = SDL_GL_CreateContext(window.get());
	SDL_GL_SetSwapInterval(1);
}
//----------------------------------------------------------------------------------------------------

void Application::loop()
{
	
}
//----------------------------------------------------------------------------------------------------

int Application::execute() noexcept
{
	return 0;
}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
