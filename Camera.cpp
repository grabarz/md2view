//----------------------------------------------------------------------------------------------------

#include "Camera.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

Camera::Camera(const Vector3<float>& pos, const Vector3<float> dir, const Vector3<float>& u)
	: position {pos}
	, direction {dir}
	, up {u}
	, matrix {0.0}
{
	
}
//----------------------------------------------------------------------------------------------------

void Camera::update(double dt)
{
}
//----------------------------------------------------------------------------------------------------

const Matrix4<float>& Camera::getMatrix() const
{
	return matrix;
}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
