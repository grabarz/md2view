//----------------------------------------------------------------------------------------------------

#ifndef _APPLICATION_HPP_0B6EB8A0ECDDA4E0A05448A88CC104B8
#define _APPLICATION_HPP_0B6EB8A0ECDDA4E0A05448A88CC104B8
//----------------------------------------------------------------------------------------------------

#include <string>

#include <boost/optional.hpp>

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
	Application(const ApplicationContext& ctx)
		: context {ctx}
	{ }

	void init();
	int execute();

private:
	ApplicationContext context;
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _APPLICATION_HPP_0B6EB8A0ECDDA4E0A05448A88CC104B8
//----------------------------------------------------------------------------------------------------
