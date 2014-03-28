//----------------------------------------------------------------------------------------------------

#include "Shaders.hpp"

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

		"\nsmooth out vec4 theColor;"

		"\nuniform mat4 perspectiveMatrix;"

		"\nvoid main()"
		"\n{"
		"\n	theColor = position;"
		"\n	gl_Position = perspectiveMatrix * position;"
		"\n}";
}
//----------------------------------------------------------------------------------------------------

std::string getDefaultFragmentShader()
{
	return
		"\n#version 330"

		"\nsmooth in vec4 theColor;"
		"\nout vec4 outColor;"

		"\nvoid main()"
		"\n{"
		"\n	outColor = vec4(abs(theColor.x), abs(theColor.y), abs(theColor.z), 1.0);"
		"\n}";
}
//----------------------------------------------------------------------------------------------------

} // namespace
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

ShadersVector getShaders() noexcept
{
	ShadersVector shaders;

	shaders.emplace_back(Shaders {getDefaultVertexShader(), getDefaultFragmentShader()});

	return shaders;
}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
