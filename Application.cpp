//----------------------------------------------------------------------------------------------------

#include "Application.hpp"

#include <exception>

#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>

#include "Program.hpp"
//----------------------------------------------------------------------------------------------------

namespace
{
//----------------------------------------------------------------------------------------------------

std::string getDefaultVertexShader()
{
	return
		"\n#version 330"
		"\nlayout(location = 0) in vec4 position;"
		"\nlayout(location = 1) in vec4 normal;"

		"\nuniform mat4 perspectiveMatrix;"

		"\nvoid main()"
		"\n{"
		"\n	gl_Position = perspectiveMatrix * position;"
		"\n}";
}
//----------------------------------------------------------------------------------------------------

std::string getDefaultFragmentShader()
{
	return
		"\n#version 330"

		"\nout vec4 outColor;"

		"\nvoid main()"
		"\n{"
		"\n	outColor = vec4(0.0, 1.0, 0.0, 1.0);"
		"\n}";
}
//----------------------------------------------------------------------------------------------------

} // namespace
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

ApplicationContext::ApplicationContext()
	: program {new Program {getDefaultVertexShader(), getDefaultFragmentShader()}}
{
}
//----------------------------------------------------------------------------------------------------

Application::Application(const ApplicationContext& ctx)
	: context {ctx}
	, window {nullptr, SDL_DestroyWindow}
	, camera {{-70.0, 0.0, -70.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 0.0}}
	, frustum {60.0, 40.0, 20.0, 175.0}
	, mvpMatrix {1.0}
{
	
}
//----------------------------------------------------------------------------------------------------

void Application::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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

int Application::execute()
{
	start();

	while (running)
	{
		processInput();
		integrate();
		display();
	}

	shutdown();

	return 0;
}
//----------------------------------------------------------------------------------------------------

void Application::start()
{
	setupKeys();

	context.program->compile();

	renderer.initProgram(*context.program);

	// load objects
	renderer.load("Object", *context.model);

	object.model = renderer.getModel("Object");
}
//----------------------------------------------------------------------------------------------------

void Application::setupKeys()
{
	keys.addAction(
		SDLK_ESCAPE, std::bind(&Application::breakLoop, this), "quit from application");
	keys.addAction(
		SDLK_w, std::bind(&Camera::forward, std::ref(camera)), "move forward");
	keys.addAction(
		SDLK_s, std::bind(&Camera::backward, std::ref(camera)), "move backward");
	keys.addAction(
		SDLK_a, std::bind(&Camera::strafeLeft, std::ref(camera)), "strafe left");
	keys.addAction(
		SDLK_d, std::bind(&Camera::strafeRight, std::ref(camera)), "strafe right");
	keys.addAction(
		SDLK_c, std::bind(&Camera::moveDown, std::ref(camera)), "move down");
	keys.addAction(
		SDLK_SPACE, std::bind(&Camera::moveUp, std::ref(camera)), "move up");
	keys.addAction(
		SDLK_h, std::bind(&Frustum::incHeight, std::ref(frustum)), "increase height of view");
	keys.addAction(
		SDLK_j, std::bind(&Frustum::decHeight, std::ref(frustum)), "decrease height of view");
	keys.addAction(
		SDLK_k, std::bind(&Frustum::incWidth, std::ref(frustum)), "increase width of view");
	keys.addAction(
		SDLK_l, std::bind(&Frustum::decWidth, std::ref(frustum)), "decrease width of view");
	keys.addAction(
		SDLK_u, std::bind(&Frustum::incFar, std::ref(frustum)), "increase far");
	keys.addAction(
		SDLK_i, std::bind(&Frustum::decFar, std::ref(frustum)), "decrease far");
	keys.addAction(
		SDLK_o, std::bind(&Frustum::incNear, std::ref(frustum)), "increase near");
	keys.addAction(
		SDLK_p, std::bind(&Frustum::decNear, std::ref(frustum)), "decrease near");
	keys.addAction(
		SDLK_n, std::bind(&Object::nextFrame, std::ref(object)), "next frame");
	keys.addAction(
		SDLK_m, std::bind(&Object::prevFrame, std::ref(object)), "previous frame");

}
//----------------------------------------------------------------------------------------------------

void Application::processInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				keys.processDown(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				keys.processUp(event.key.keysym.sym);
				break;
			case SDL_QUIT:
				breakLoop();
				break;
		}
	}
}
//----------------------------------------------------------------------------------------------------

void Application::integrate()
{
	double dt = 0.0;

	camera.update(dt);
	frustum.update(dt);
	object.update(dt);

	mvpMatrix = Matrix4<float>::multiply(frustum.getMatrix(), camera.getMatrix());
}
//----------------------------------------------------------------------------------------------------

void Application::display()
{
	renderer.begin();
	renderer.render(*context.program, mvpMatrix, *object.model, object.getFrame());
	renderer.end();

	SDL_GL_SwapWindow(window.get());
}
//----------------------------------------------------------------------------------------------------

void Application::breakLoop()
{
	running = false;
}
//----------------------------------------------------------------------------------------------------

void Application::shutdown()
{
	SDL_GL_DeleteContext(glContext);
	window.reset();
	SDL_Quit();
}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
