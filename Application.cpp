//----------------------------------------------------------------------------------------------------

#include "Application.hpp"

#include <exception>
#include <iostream>

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
//		"\n	gl_Normal = perspectiveMatrix * normal;"
		"\n	gl_Position = perspectiveMatrix * position;"
//		"\n	gl_Position = vec4(0.0, 0.0,0.0,1.0);"
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
	, camera {{90.0, 0.0, 0.0}, {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}}
	, frustum {100.0, 100.0, 0.005, 250.0}
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
	context.program->compile();

	renderer.initProgram(*context.program);

	// load objects
	renderer.load("Object", *context.model);

	object.model = renderer.getModel("Object");
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
				onKeyDown(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				onKeyUp(event.key.keysym.sym);
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

// 	std::cout << "camera:" << std::endl << camera.getMatrix() << std::endl;
// 	std::cout << "position:" << camera.position << std::endl;
// 	std::cout << "direction:" << camera.direction << std::endl;
// 	std::cout << "up:" << camera.up << std::endl;
// 	std::cout << "frustum:" << std::endl << frustum.getMatrix() << std::endl;
	mvpMatrix = Matrix4<float>::multiply(camera.getMatrix(), frustum.getMatrix());
//	mvpMatrix = Matrix4<float>::multiply(frustum.getMatrix(), camera.getMatrix());
// 	std::cout << "mvp:" << std::endl << mvpMatrix << std::endl;
}
//----------------------------------------------------------------------------------------------------

void Application::display()
{
	renderer.begin();
	renderer.render(*context.program, mvpMatrix, object.getFrame());
	renderer.end();

	SDL_GL_SwapWindow(window.get());
}
//----------------------------------------------------------------------------------------------------

void Application::breakLoop()
{
	running = false;
}
//----------------------------------------------------------------------------------------------------

void Application::onKeyDown(SDL_Keycode key)
{
	switch (key)
	{
		case SDLK_ESCAPE:
			breakLoop();
			break;
	}
}
//----------------------------------------------------------------------------------------------------

void Application::onKeyUp(SDL_Keycode key)
{
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
