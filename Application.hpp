//----------------------------------------------------------------------------------------------------

#ifndef _APPLICATION_HPP_0B6EB8A0ECDDA4E0A05448A88CC104B8
#define _APPLICATION_HPP_0B6EB8A0ECDDA4E0A05448A88CC104B8
//----------------------------------------------------------------------------------------------------

#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "Camera.hpp"
#include "Frustum.hpp"
#include "KeyManager.hpp"
#include "MD2_fwd.hpp"
#include "Program_fwd.hpp"
#include "Renderer.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

struct ApplicationContext
{
	typedef unsigned int Pixels;

	Pixels width;
	Pixels height;

	ProgramPtr program;
	MD2Ptr model;

	// texture

	ApplicationContext();
};
//----------------------------------------------------------------------------------------------------

class Application
{
public:
	Application(const ApplicationContext& ctx);

	void init();
	int execute();

private:
	void start();
	void setupKeys();
	void processInput();
	void integrate();
	void display();
	void shutdown();

	void breakLoop();

	typedef std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> WindowPtr;

	WindowPtr window;
	SDL_GLContext glContext;
	ApplicationContext context;
	bool running {true};

	KeyManager keys;
	Frustum frustum;
	Camera camera;
	Renderer renderer;

	Object object;
	Matrix4<float> mvpMatrix;
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _APPLICATION_HPP_0B6EB8A0ECDDA4E0A05448A88CC104B8
//----------------------------------------------------------------------------------------------------
