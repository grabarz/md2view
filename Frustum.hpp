//----------------------------------------------------------------------------------------------------

#ifndef _FRUSTUM_HPP_9EF95D7F38B75DA5C42325F396416D10
#define _FRUSTUM_HPP_9EF95D7F38B75DA5C42325F396416D10
//----------------------------------------------------------------------------------------------------

#include "Frustum_fwd.hpp"

#include "Matrix4.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

class Frustum
{
public:
	Frustum(float l, float r, float t, float b, float n, float f);
	Frustum(float width, float height, float n, float f);
	Frustum();

	void update(float dt);
	const Matrix4<float>& getMatrix() const;

	void incFar();
	void decFar();

	void incNear();
	void decNear();

	void incWidth();
	void decWidth();

	void incHeight();
	void decHeight();

private:
	void updateMatrix();

	float left;
	float right;
	float top;
	float bottom;
	float near;
	float far;

	Matrix4<float> matrix;
};
//----------------------------------------------------------------------------------------------------

} // namespace DasModel
//----------------------------------------------------------------------------------------------------

#endif // _FRUSTUM_HPP_9EF95D7F38B75DA5C42325F396416D10
//----------------------------------------------------------------------------------------------------
