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
	, matrix {1.0}
	, orientation {1.0}
	, translation {1.0}
{
	
}
//----------------------------------------------------------------------------------------------------

void Camera::update(double dt)
{
	updateMatrix();
}
//----------------------------------------------------------------------------------------------------

const Matrix4<float>& Camera::getMatrix() const
{
	return matrix;
}
//----------------------------------------------------------------------------------------------------

void Camera::updateMatrix()
{
	typedef Vector3<float> V3;

	V3 zAxis(direction);
	//zAxis.dec(position);
	zAxis.normalize();

	V3 xAxis = V3::crossProduct(up, zAxis);
	xAxis.normalize();

	V3 yAxis = V3::crossProduct(zAxis, xAxis);

	translation[At<4>(0, 3)] = -position[0];
	translation[At<4>(1, 3)] = -position[1];
	translation[At<4>(2, 3)] = -position[2];

	// Matrix4<float> orientation {
	// 	xAxis[0], yAxis[0], zAxis[0], 0.0,
	// 	xAxis[1], yAxis[1], zAxis[1], 0.0,
	// 	xAxis[2], yAxis[2], zAxis[2], 0.0,
	// 	0.0, 0.0, 0.0, 1.0};

	orientation[At<4>(0, 0)] = xAxis[0];
	orientation[At<4>(1, 0)] = xAxis[1];
	orientation[At<4>(2, 0)] = xAxis[2];

	orientation[At<4>(0, 1)] = yAxis[0];
	orientation[At<4>(1, 1)] = yAxis[1];
	orientation[At<4>(2, 1)] = yAxis[2];

	orientation[At<4>(0, 2)] = zAxis[0];
	orientation[At<4>(1, 2)] = zAxis[1];
	orientation[At<4>(2, 2)] = zAxis[2];

	matrix = Matrix4<float>::multiply(translation, orientation);
//	matrix = Matrix4<float>::multiply(orientation, translation);
}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
