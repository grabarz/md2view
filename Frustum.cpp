//----------------------------------------------------------------------------------------------------

#include "Frustum.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

Frustum::Frustum(float l, float r, float t, float b, float n, float f)
	: left(l)
	, right(r)
	, top(t)
	, bottom(b)
	, near(n)
	, far(f)
	, matrix {0.0}
{
}
//----------------------------------------------------------------------------------------------------

Frustum::Frustum(float width, float height, float n, float f)
	: Frustum(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, n, f)
{
}
//----------------------------------------------------------------------------------------------------

Frustum::Frustum()
	: Frustum(10.0, 10.0, 1.0, 20.0)
{
}
//----------------------------------------------------------------------------------------------------

void Frustum::incFar()
{
	far += 1.0;
}
//----------------------------------------------------------------------------------------------------

void Frustum::decFar()
{
	far -= 1.0;
}
//----------------------------------------------------------------------------------------------------

void Frustum::incNear()
{
	near += 1.0;
}
//----------------------------------------------------------------------------------------------------

void Frustum::decNear()
{
	near -= 1.0;
}
//----------------------------------------------------------------------------------------------------

void Frustum::incWidth()
{
	float w = ((right - left) + 1.0) / 2.0;

	left = -w;
	right = w;
}
//----------------------------------------------------------------------------------------------------

void Frustum::decWidth()
{
	float w = ((right - left) - 1.0) / 2.0;

	left = -w;
	right = w;
}
//----------------------------------------------------------------------------------------------------

void Frustum::incHeight()
{
	float h = ((top - bottom) + 1.0) / 2.0;

	bottom = -h;
	top = h;
}
//----------------------------------------------------------------------------------------------------

void Frustum::decHeight()
{
	float h = ((top - bottom) - 1.0) / 2.0;

	bottom = -h;
	top = h;
}
//----------------------------------------------------------------------------------------------------

void Frustum::update(float dt)
{
	updateMatrix();
}
//----------------------------------------------------------------------------------------------------

const Matrix4<float>& Frustum::getMatrix() const
{
	return matrix;
}
//----------------------------------------------------------------------------------------------------

void Frustum::updateMatrix()
{
	matrix[At<4>(0, 0)] = 2.0 * near / (right - left);
	matrix[At<4>(1, 1)] = 2.0 * near / (top - bottom);
	matrix[At<4>(0, 2)] = (right + left) / (right - left);
	matrix[At<4>(1, 2)] = (top + bottom) / (top - bottom);
	matrix[At<4>(2, 2)] = -(far + near) / (far - near);
	matrix[At<4>(3, 2)] = -1.0;
	matrix[At<4>(2, 3)] = -(2 * far * near) / (far - near);
}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
