//----------------------------------------------------------------------------------------------------

#include "Renderer.hpp"

#include <stdexcept>

#include "Animation.hpp"
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
	prog.addUniform("scale");
	prog.unload();
}
//----------------------------------------------------------------------------------------------------

ModelPtr Renderer::load(const MD2& md2, const AnimationVector& anims)
{
	ModelPtr model = std::make_shared<Model>();

	model->vaos.reserve(md2.frames);

	// creating data buffer
	GLuint buff;
	glGenBuffers(1, &buff);
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	glBufferData(GL_ARRAY_BUFFER, md2.data.size() * sizeof(float), md2.data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// creating indices buffer
	GLuint indices;
	glGenBuffers(1, &indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, md2.indices.size() * sizeof(unsigned short), md2.indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	model->indices = md2.indices.size();

	std::size_t normalsOffset = sizeof(float) * md2.frames * md2.vertices * 3; // !!!!!

	int animation = 0;

	for (int i = 0; i < md2.frames; ++i)
	{
		if (i > anims[animation].lastFrame)
			++animation;

		// creating VAO
		GLuint vao;
		std::size_t off = i * md2.vertices * 3 * sizeof(float);
		std::size_t nextOff = (i == anims[animation].lastFrame ? anims[animation].firstFrame : i + 1) * md2.vertices * 3 * sizeof(float);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, buff);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)off); // position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)nextOff); // next frame position
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)(normalsOffset + off)); // normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void *)(normalsOffset + nextOff)); // next normal
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);

		glBindVertexArray(0);

		model->vaos.push_back(vao);
	}

	return model;
}
//----------------------------------------------------------------------------------------------------

void Renderer::init()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
}
//----------------------------------------------------------------------------------------------------

void Renderer::begin()
{
	glClearColor(8, 0, 0, 1);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//----------------------------------------------------------------------------------------------------

void Renderer::render(Program& prog, const Matrix4<float>& mat, float scale, const Model& obj, std::size_t frame)
{
	prog.load();

	glBindVertexArray(obj.vaos[frame]);
	prog.setUniform("perspectiveMatrix", mat);
	prog.setUniform("scale", scale);
	glDrawElements(GL_TRIANGLES, obj.indices, GL_UNSIGNED_SHORT, 0);
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
