//----------------------------------------------------------------------------------------------------

#ifndef _CAMERA_HPP_1774D639DF07DBB517B6769EFEF06875
#define _CAMERA_HPP_1774D639DF07DBB517B6769EFEF06875
//----------------------------------------------------------------------------------------------------

#include "Camera_fwd.hpp"

#include "Frustum.hpp"
#include "Matrix4.hpp"
#include "Vector3.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

class Camera
{
public:
	Camera(const Vector3<float>& pos, const Vector3<float>& dir, const Vector3<float>& u);

	void update(float dt);
	const Matrix4<float>& getMatrix() const;

	void forward();
	void backward();
	void rotateLeft();
	void rotateRight();
	void strafeLeft();
	void strafeRight();
	void lookUp();
	void lookDown();
	void moveUp();
	void moveDown();

	Vector3<float> position;
	Vector3<float> direction;
	Vector3<float> up;

private:
	void updateMatrix();

	Matrix4<float> matrix;
	Matrix4<float> orientation;
	Matrix4<float> translation;

	Vector3<float> velocity;
	Vector3<float> acceleration;
	float damping {0.4};
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _CAMERA_HPP_1774D639DF07DBB517B6769EFEF06875
//----------------------------------------------------------------------------------------------------
