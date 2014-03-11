//----------------------------------------------------------------------------------------------------

#include "Program.hpp"

#include "Matrix4.hpp"
//----------------------------------------------------------------------------------------------------

namespace
{
//----------------------------------------------------------------------------------------------------

GLuint makeShader(GLenum type, const std::string& source)
{
	GLuint shader = glCreateShader(type);
	const GLchar* src = source.c_str();

	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		throw std::runtime_error("shader compilation error!");
	}

	return shader;
}
//----------------------------------------------------------------------------------------------------

GLuint makeProgram(GLuint v, GLuint f)
{
	GLuint program = glCreateProgram();

	glAttachShader(program, v);
	glAttachShader(program, f);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		throw std::runtime_error("program linking error!");
	}

	glDetachShader(program, v);
	glDetachShader(program, f);

	return program;
}
//----------------------------------------------------------------------------------------------------

} // namespace
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

Program::Program(const std::string& vStr, const std::string& fStr)
	: vShader {vStr}
	, fShader {fStr}
	, program {}
{
}
//----------------------------------------------------------------------------------------------------

void Program::compile()
{
	GLuint vsh = makeShader(GL_VERTEX_SHADER, vShader);
	GLuint fsh = makeShader(GL_FRAGMENT_SHADER, fShader);

	program = makeProgram(vsh, fsh);

	glDeleteShader(vsh);
	glDeleteShader(fsh);

	vShader.clear();
	fShader.clear();
}
//----------------------------------------------------------------------------------------------------

void Program::load()
{
	glUseProgram(program);
}
//----------------------------------------------------------------------------------------------------

void Program::unload()
{
	glUseProgram(0);
}
//----------------------------------------------------------------------------------------------------

void Program::addUniform(const std::string& uniform)
{
	uniforms[uniform] = glGetUniformLocation(program, uniform.c_str());
}
//----------------------------------------------------------------------------------------------------

template <>
void Program::setUniform<Matrix4<float>>(const std::string& uniform, const Matrix4<float>& val)
{
	
}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
