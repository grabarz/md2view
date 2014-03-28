//----------------------------------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <vector>

#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>

#include "Application.hpp"
#include "ApplicationContext.hpp"
#include "MD2.hpp"
#include "Shaders_fwd.hpp"
//----------------------------------------------------------------------------------------------------

namespace bpo = boost::program_options;
//----------------------------------------------------------------------------------------------------

MD2View::Shaders readProgram(const std::string& vFile, const std::string& fFile)
{
	return MD2View::Shaders("", "");
}
//----------------------------------------------------------------------------------------------------

std::vector<MD2View::MD2Ptr> readModels(const std::vector<std::string>& files)
{
	using namespace MD2View;

	std::ifstream md2stream;
	std::vector<MD2View::MD2Ptr> models;

	for (const std::string& file: files)
	{
		MD2Ptr md2 {new MD2()};

		md2stream.open(file);
		if (!md2stream.is_open())
			throw std::runtime_error("model file opening failed!");
		md2stream >> *md2;
		md2stream.close();
		models.push_back(md2);
	}

	return models;
}
//----------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	bpo::options_description desc("All options");
	desc.add_options()
		("width", bpo::value<unsigned int>()->default_value(800), "window width")
		("height", bpo::value<unsigned int>()->default_value(600), "window height")
		("model", bpo::value<std::string>(), "model")
		("vertex", bpo::value<std::string>(), "vertex shader")
		("fragment", bpo::value<std::string>(), "fragment shader")
		("input-files", bpo::value<std::vector<std::string>>(), "input files")
		("help", "help message");

	bpo::positional_options_description pos;
	pos.add("input-files", -1);

	bpo::variables_map vm;
	bpo::store(bpo::command_line_parser(argc, argv).options(desc).positional(pos).run(), vm);
	bpo::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;

		return 0;
	}

	int code = 1;

	try
	{
		MD2View::ApplicationContextPtr ctx {new MD2View::ApplicationContext()};

		if (vm.count("input-files"))
			ctx->models = readModels(vm["input-files"].as<std::vector<std::string>>());
		else
			throw std::runtime_error("model file is not specified!");

		if (vm.count("vertex") + vm.count("fragment") == 2)
			ctx->shaders.push_back(readProgram(vm["vertex"].as<std::string>(), vm["fragment"].as<std::string>()));

		ctx->width = vm["width"].as<unsigned int>();
		ctx->height = vm["height"].as<unsigned int>();

		MD2View::Application app {ctx};

		app.init();

		code = app.execute();
	}
	catch (std::exception& e)
	{
		std::cerr << "Failed with message: " << e.what() << std::endl;

		return 1;
	}

	return code;
}
//----------------------------------------------------------------------------------------------------
