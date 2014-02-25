//----------------------------------------------------------------------------------------------------

#include <iostream>

#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>

#include <SDL2/SDL.h>
//----------------------------------------------------------------------------------------------------

namespace bpo = boost::program_options;
//----------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	bpo::options_description desc("All options");
	desc.add_options()
		("width", bpo::value<int>()->default_value(800), "window width")
		("height", bpo::value<int>()->default_value(600), "window height")
		("model", bpo::value<std::string>()->default_value("model.md2"), "model")
		("vertex", bpo::value<std::string>(), "vertex shader")
		("fragment", bpo::value<std::string>(), "fragment shader")
		("help", "help message");

	bpo::variables_map vm;
	bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
	bpo::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;

		return 1;
	}
}
//----------------------------------------------------------------------------------------------------
