//----------------------------------------------------------------------------------------------------

#ifndef _APPLICATION_HPP_0B6EB8A0ECDDA4E0A05448A88CC104B8
#define _APPLICATION_HPP_0B6EB8A0ECDDA4E0A05448A88CC104B8
//----------------------------------------------------------------------------------------------------

#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "MD2_fwd.hpp"
#include "Program_fwd.hpp"
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
	int execute() noexcept;

private:
	void loop();

	typedef std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> WindowPtr;
	WindowPtr window;
	SDL_GLContext glContext;

	ApplicationContext context;
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _APPLICATION_HPP_0B6EB8A0ECDDA4E0A05448A88CC104B8
//----------------------------------------------------------------------------------------------------
