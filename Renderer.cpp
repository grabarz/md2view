//----------------------------------------------------------------------------------------------------

#include "Renderer.hpp"

#include <stdexcept>

#include "Matrix4.hpp"
#include "MD2.hpp"
#include "Model.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

Renderer::Renderer()
{
}
//----------------------------------------------------------------------------------------------------

void Renderer::initProgram(Program& prog)
{
	prog.load();
	prog.addUniform("mvp");
	prog.unload();
}
//----------------------------------------------------------------------------------------------------

void Renderer::load(const std::string& name, const MD2& md2)
{
	ModelPtr model {new Model};

	for (const auto& frame : md2.frames)
	{
		GLuint vbuff, nbuff;

		glGenBuffers(1, &vbuff);
		glBindBuffer(GL_ARRAY_BUFFER, vbuff);
		glBufferData(GL_ARRAY_BUFFER, frame.vertices.size(), frame.vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &nbuff);
		glBindBuffer(GL_ARRAY_BUFFER, nbuff);
		glBufferData(GL_ARRAY_BUFFER, frame.normals.size(), frame.normals.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		Frame f;

		f.vao = 0;
		f.size = frame.vertices.size();

		model->frames.push_back(f);
	}

	models[name] = model;
}
//----------------------------------------------------------------------------------------------------

ModelPtr Renderer::getModel(const std::string& name)
{
	std::map<std::string, ModelPtr>::iterator it = models.find(name);

	if (it == models.end())
		throw std::runtime_error("unable to load model!");

	return it->second;
}
//----------------------------------------------------------------------------------------------------

void Renderer::begin()
{
	glClearColor(1,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//----------------------------------------------------------------------------------------------------

void Renderer::render(Program& prog, const Matrix4<float>& mat, const Frame& frame)
{
	prog.load();
	prog.setUniform("mvp", mat);
	// draw
	prog.unload();
}
//----------------------------------------------------------------------------------------------------

void Renderer::end()
{

}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
