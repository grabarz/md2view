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
		"\nlayout(location = 1) in vec4 nextPosition;"
		"\nlayout(location = 2) in vec4 normal;"
		"\nlayout(location = 3) in vec4 nextNormal;"

		"\nuniform mat4 perspectiveMatrix;"
		"\nuniform float scale;"

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
		"\n	outColor = vec4(1.0, 1.0, 1.0, 1.0);"
		"\n}";
}
//----------------------------------------------------------------------------------------------------

std::string getFirstVertexShader()
{
	return
		"\n#version 330"
		"\nlayout(location = 0) in vec4 position;"
		"\nlayout(location = 1) in vec4 nextPosition;"
		"\nlayout(location = 2) in vec4 normal;"
		"\nlayout(location = 3) in vec4 nextNormal;"

		"\nsmooth out vec4 theColor;"
//		"\nsmooth out vec4 theNormal;"

		"\nuniform mat4 perspectiveMatrix;"
		"\nuniform float scale;"

		"\nvoid main()"
		"\n{"
		"\n	theColor = mix(normal, nextNormal, scale);"
//		"\n	theNormal = normal;"
		"\n	gl_Position = perspectiveMatrix * mix(position, nextPosition, scale);"
		"\n}";
}
//----------------------------------------------------------------------------------------------------

std::string getFirstFragmentShader()
{
	return
		"\n#version 330"

		"\nsmooth in vec4 theColor;"
		"\nout vec4 outColor;"
//		"\nout vec4 theNormal;"

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
	shaders.emplace_back(Shaders {getFirstVertexShader(), getFirstFragmentShader()});

	return shaders;
}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
