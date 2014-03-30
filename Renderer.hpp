//----------------------------------------------------------------------------------------------------

#ifndef _RENDERER_HPP_2557FE3F410C8F39795FD533541879FE
#define _RENDERER_HPP_2557FE3F410C8F39795FD533541879FE
//----------------------------------------------------------------------------------------------------

#include "Renderer_fwd.hpp"

#include "Animation_fwd.hpp"
#include "Matrix4_fwd.hpp"
#include "MD2_fwd.hpp"
#include "Model.hpp"
#include "Program.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

class Renderer
{
public:
	Renderer();

	ModelPtr load(const MD2& md2, const AnimationVector& anims);

	void init();

	void begin();
	void end();

	void initProgram(Program& prog);
	void render(Program& prog, const Matrix4<float>& mat, float scale, const Model& obj, std::size_t frame);
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _RENDERER_HPP_2557FE3F410C8F39795FD533541879FE
//----------------------------------------------------------------------------------------------------
