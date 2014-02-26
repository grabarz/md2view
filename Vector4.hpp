//----------------------------------------------------------------------------------------------------

#ifndef _VECTOR4_HPP_94B290F0D3154FABA6049C3E1991F6BD
#define _VECTOR4_HPP_94B290F0D3154FABA6049C3E1991F6BD
//----------------------------------------------------------------------------------------------------

#include <cassert>
#include <cstddef>
#include <cmath>

#include "Float.hpp"
#include "Vector4_fwd.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

template<typename T> class Vector4
{
protected:
	T vec[4]; // xyzv

public:
	typedef T scalar_type;

	Vector4() noexcept
	{
		vec[0] = vec[1] = vec[2] = vec[3] = static_cast<T>(0.0);
	}

	Vector4(const Vector4<T>& v) noexcept
	{
		vec[0] = v.vec[0];
		vec[1] = v.vec[1];
		vec[2] = v.vec[2];
		vec[3] = v.vec[3];
	}

	Vector4(T x, T y, T z, T v) noexcept
	{
		vec[0] = x;
		vec[1] = y;
		vec[2] = z;
		vec[3] = v;
	}

	const T& operator[](std::size_t i) const noexcept
	{
		return vec[i];
	}

	T& operator[](std::size_t i) noexcept
	{
		return vec[i];
	}

	bool operator==(const Vector4<T>& v) const noexcept
	{
		return
			v.vec[0] == vec[0]
			&& v.vec[1] == vec[1]
			&& v.vec[2] == vec[2]
			&& v.vec[3] == vec[3];
	}

	Vector4<T>& inc(const Vector4<T>& v) noexcept
	{
		vec[0] += v.vec[0];
		vec[1] += v.vec[1];
		vec[2] += v.vec[2];
		vec[3] += v.vec[3];

		return *this;
	}

	Vector4<T>& inc(const Vector4<T>& v, T scale) noexcept
	{
		vec[0] += scale * v.vec[0];
		vec[1] += scale * v.vec[1];
		vec[2] += scale * v.vec[2];
		vec[3] += scale * v.vec[3];

		return *this;
	}

	Vector4<T>& dec(const Vector4<T>& v) noexcept
	{
		vec[0] -= v.vec[0];
		vec[1] -= v.vec[1];
		vec[2] -= v.vec[2];
		vec[3] -= v.vec[3];

		return *this;
	}

	Vector4<T>& neg() noexcept
	{
		vec[0] = -vec[0];
		vec[1] = -vec[1];
		vec[2] = -vec[2];
		vec[3] = -vec[3];

		return *this;
	}

	Vector4<T>& mul(T d) noexcept
	{
		vec[0] *= d;
		vec[1] *= d;
		vec[2] *= d;
		vec[3] *= d;

		return *this;
	}

	Vector4<T>& div(T d) noexcept
	{
		vec[0] /= d;
		vec[1] /= d;
		vec[2] /= d;
		vec[3] /= d;

		return *this;
	}

	Vector4<T>& normalize() noexcept
	{
		T d = len();

		assert(d != static_cast<T>(0.0));
		div(d);

		return *this;
	}

	const T len2() const noexcept
	{
		return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2] + vec[3] * vec[3];
	}

	const T len() const noexcept
	{
		return sqrt(len2());
	}

	Vector4<T>& len(T m) noexcept
	{
		return mul(m / len());
	}

	bool equals(const Vector4<T>& v) const noexcept
	{
		return
			FloatEqual<T>(vec[0], v[0])
			&& FloatEqual<T>(vec[1], v[1])
			&& FloatEqual<T>(vec[2], v[2])
			&& FloatEqual<T>(vec[3], v[3]);
	}

	bool equals(const Vector4<T>& v, T eps) const noexcept
	{
		return
			FloatEqual<T>(vec[0], v[0], eps)
			&& FloatEqual<T>(vec[1], v[1], eps)
			&& FloatEqual<T>(vec[2], v[2], eps)
			&& FloatEqual<T>(vec[3], v[3], eps);
	}

	static T dotProduct(const Vector4<T>& u, const Vector4<T>& v) noexcept
	{
		return
			u.vec[0] * v.vec[0] + u.vec[1] * v.vec[1] +
			u.vec[2] * v.vec[2] + u.vec[3] * v.vec[3];
	}

	static Vector4<T> crossProduct(const Vector4<T>& u, const Vector4<T>& v) noexcept
	{
		return Vector4(
			u.vec[1] * v.vec[2] - u.vec[2] * v.vec[1],
			u.vec[2] * v.vec[0] - u.vec[0] * v.vec[2],
			u.vec[0] * v.vec[1] - u.vec[1] * v.vec[0]);
	}
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _VECTOR4_HPP_94B290F0D3154FABA6049C3E1991F6BD
//----------------------------------------------------------------------------------------------------
