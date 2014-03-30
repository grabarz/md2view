//----------------------------------------------------------------------------------------------------

#ifndef _APPLICATION_HPP_0B6EB8A0ECDDA4E0A05448A88CC104B8
#define _APPLICATION_HPP_0B6EB8A0ECDDA4E0A05448A88CC104B8
//----------------------------------------------------------------------------------------------------

#include <memory>
#include <vector>

#include <SDL2/SDL.h>

#include "Animation.hpp"
#include "ApplicationContext_fwd.hpp"
#include "Camera.hpp"
#include "Frustum.hpp"
#include "KeyManager.hpp"
#include "Model_fwd.hpp"
#include "Object.hpp"
#include "Program_fwd.hpp"
#include "Renderer.hpp"
#include "Timer.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

class Application
{
public:
	Application(const ApplicationContextPtr& ctx);

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
	ApplicationContextPtr context;
	bool running {true};

	Timer timer;
	KeyManager keys;
	Frustum frustum;
	Camera camera;
	Renderer renderer;

	ProgramVector programs;
	ModelVector models;
	AnimationVector animations;

	Object object;
	Matrix4<float> mvpMatrix;
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _APPLICATION_HPP_0B6EB8A0ECDDA4E0A05448A88CC104B8
//----------------------------------------------------------------------------------------------------
