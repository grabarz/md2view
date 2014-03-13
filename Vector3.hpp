//----------------------------------------------------------------------------------------------------

#ifndef _VECTOR3_HPP_1F4896FB599342F7A479BE0977E0909B
#define _VECTOR3_HPP_1F4896FB599342F7A479BE0977E0909B
//----------------------------------------------------------------------------------------------------

#include <cstddef>
#include <cmath>
#include <ostream>

#include "Float.hpp"
#include "Vector3_fwd.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

template <typename T>
class Vector3
{
protected:
	T vec[3]; // xyz

public:
	typedef T scalar_type;
	
	Vector3() noexcept
	{
		vec[0] = vec[1] = vec[2] = static_cast<T>(0.0);
	}

	Vector3(const Vector3<T>& v) noexcept
	{
		vec[0] = v.vec[0];
		vec[1] = v.vec[1];
		vec[2] = v.vec[2];
	}

	Vector3(T x, T y, T z) noexcept
	{
		vec[0] = x;
		vec[1] = y;
		vec[2] = z;
	}

	T* get() noexcept
	{
		return &vec[0];
	}

	const T& operator[](std::size_t i) const noexcept
	{
		return vec[i];
	}

	bool operator==(const Vector3<T>& v) const noexcept
	{
		return v.vec[0] == vec[0] && v.vec[1] == vec[1] && v.vec[2] == vec[2];
	}

	T& operator[](std::size_t i) noexcept
	{
		return vec[i];
	}

	Vector3<T>& inc(const Vector3<T>& v) noexcept
	{
		vec[0] += v.vec[0];
		vec[1] += v.vec[1];
		vec[2] += v.vec[2];

		return *this;
	}

	Vector3<T>& inc(const Vector3<T>& v, T scale) noexcept
	{
		vec[0] += scale * v.vec[0];
		vec[1] += scale * v.vec[1];
		vec[2] += scale * v.vec[2];

		return *this;
	}

	Vector3<T>& dec(const Vector3<T>& v) noexcept
	{
		vec[0] -= v.vec[0];
		vec[1] -= v.vec[1];
		vec[2] -= v.vec[2];

		return *this;
	}

	Vector3<T>& neg() noexcept
	{
		vec[0] = -vec[0];
		vec[1] = -vec[1];
		vec[2] = -vec[2];

		return *this;
	}

	Vector3<T>& mul(T d) noexcept
	{
		vec[0] *= d;
		vec[1] *= d;
		vec[2] *= d;

		return *this;
	}

	Vector3<T>& div(T d) noexcept
	{
		vec[0] /= d;
		vec[1] /= d;
		vec[2] /= d;

		return *this;
	}

	Vector3<T>& normalize() noexcept
	{
		T d = len();

		if (d)
			div(d);

		return *this;
	}

	const T len2() const noexcept
	{
		return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
	}

	const T len() const noexcept
	{
		return sqrt(len2());
	}

	Vector3<T>& len(T l) noexcept
	{
		return mul(l / len());
	}

	bool equals(const Vector3<T>& v) const noexcept
	{
		return
			FloatEqual<T>(vec[0], v[0])
			&& FloatEqual<T>(vec[1], v[1])
			&& FloatEqual<T>(vec[2], v[2]);
	}

	bool equals(const Vector3<T>& v, T eps) const noexcept
	{
		return
			FloatEqual<T>(vec[0], v[0], eps)
			&& FloatEqual<T>(vec[1], v[1], eps)
			&& FloatEqual<T>(vec[2], v[2], eps);
	}

	static const T dotProduct(const Vector3<T>& u, const Vector3<T>& v) noexcept
	{
		return u.vec[0] * v.vec[0] + u.vec[1] * v.vec[1] + u.vec[2] * v.vec[2];
	}

	static Vector3<T> crossProduct(const Vector3<T>& u, const Vector3<T>& v) noexcept
	{
		return Vector3(
			u.vec[1] * v.vec[2] - u.vec[2] * v.vec[1],
			u.vec[2] * v.vec[0] - u.vec[0] * v.vec[2],
			u.vec[0] * v.vec[1] - u.vec[1] * v.vec[0]);
	}
};
//----------------------------------------------------------------------------------------------------

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Vector3<T>& vec)
{
	stream << "[" << vec[0] << ", " << vec[1] << ", " << vec[2] << "]";

	return stream;
}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _VECTOR3_HPP_1F4896FB599342F7A479BE0977E0909B
//----------------------------------------------------------------------------------------------------
