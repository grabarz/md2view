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
	prog.addUniform("perspectiveMatrix");
	prog.unload();
}
//----------------------------------------------------------------------------------------------------

void Renderer::load(const std::string& name, const MD2& md2)
{
	ModelPtr model {new Model};

	model->frames.reserve(md2.frames);

	// creating buffer
	GLuint buff;

	glGenBuffers(1, &buff);
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	glBufferData(GL_ARRAY_BUFFER, md2.data.size(), md2.data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	std::size_t normalsOffset = sizeof(float) * 3 * md2.triangles;

	for (int i = 0; i < md2.frames; ++i)
	{
		// creating VAO
		Frame frame;

		frame.triangles = md2.triangles;

		glGenVertexArrays(1, &frame.vao);
		glBindVertexArray(frame.vao);

		glBindBuffer(GL_ARRAY_BUFFER, buff);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // position		
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)normalsOffset); // normal

		glBindVertexArray(0);

		model->frames.push_back(frame);
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
	glClearColor(8, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//----------------------------------------------------------------------------------------------------

void Renderer::render(Program& prog, const Matrix4<float>& mat, const Frame& frame)
{
	prog.load();

	glBindVertexArray(frame.vao);
	prog.setUniform("perspectiveMatrix", mat);
	glDrawArrays(GL_TRIANGLES, 0, frame.triangles);
	glBindVertexArray(0);

	prog.unload();
}
//----------------------------------------------------------------------------------------------------

void Renderer::end()
{

}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
