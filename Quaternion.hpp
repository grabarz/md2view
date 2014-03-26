//----------------------------------------------------------------------------------------------------

#ifndef _QUATERNION_HPP_A404199B256E10B1181CEB5FA3BE88B7
#define _QUATERNION_HPP_A404199B256E10B1181CEB5FA3BE88B7
//----------------------------------------------------------------------------------------------------

#include "Quaternion_fwd.hpp"

#include <cmath>

#include "Matrix3.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

template <typename T>
struct Quaternion
{
	T x;
	T y;
	T z;
	T w;

	typedef T scalar_type;

	Quaternion() noexcept
	{
		x = y = z = w = {};
	}

	Quaternion(const Quaternion<T>& q) noexcept
	{
		*this = q;
	}

	Quaternion(T x, T y, T z, T w) noexcept
		: x {x}
		, y {y}
		, z {z}
		, w {w}
	{ }

	Quaternion(const Vector3<T>& v, T angle) noexcept
	{
		const T h = angle / 2.0;
		const T s = std::sin(h);

		x = v[0] * s;
		y = v[1] * s;
		z = v[2] * s;
		w = std::cos(h);
	}

	Quaternion<T>& operator=(const Quaternion<T>& q) noexcept
	{
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;

		return *this;
	}

	Quaternion<T>& operator=(const Vector4<T>& v) noexcept
	{
		x = v[0];
		y = v[1];
		z = v[2];
		w = v[3];

		return *this;
	}

	T* get() noexcept
	{
		return &x;
	}

	const T* get() const noexcept
	{
		return &x;
	}

	T& operator[](std::size_t i) noexcept
	{
		return *(&x + i);
	}

	T operator[](std::size_t i) const noexcept
	{
		return *(&x + i);
	}

	Quaternion<T>& inc(const Quaternion<T>& q) noexcept
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;

		return *this;
	}

	Quaternion<T>& inc(const Quaternion<T>& q, T scale) noexcept
	{
		x += scale * q.x;
		y += scale * q.y;
		z += scale * q.z;
		w += scale * q.w;

		return *this;
	}

	Quaternion<T>& dec(const Quaternion<T>& q) noexcept
	{
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;

		return *this;
	}

	Quaternion<T>& mul(T a) noexcept
	{
		x *= a;
		y *= a;
		z *= a;
		w *= a;

		return *this;
	}

	Vector3<T> mul(const Vector3<T>& v) const noexcept
	{
		const T xx = x * x;
		const T yy = y * y;
		const T zz = z * z;
		const T ww = w * w;

		const T xxzz = xx - zz;
		const T wwyy = ww - yy;

		const T xw2 = x * w * 2.0;
		const T xy2 = x * y * 2.0;
		const T xz2 = x * z * 2.0;
		const T yw2 = y * w * 2.0;
		const T yz2 = y * z * 2.0;
		const T zw2 = z * w * 2.0;

		return Vector3<T>(
			(xxzz + wwyy) * v[0] + (xy2 + zw2) * v[1] + (xz2 - yw2) * v[2],
			(xy2 - zw2) * v[0] + (yy + ww - xx - zz)* v[1] + (yz2 + xw2) * v[2],
			(xz2 + yw2)* v[0] + (yz2 - xw2) * v[1] + (wwyy - xxzz) * v[2]);
	}

	Quaternion<T>& neg() noexcept
	{
		mul(-1.0);

		return *this;
	}

	T len2() const noexcept
	{
		return x * x + y * y + z * z + w * w;
	}

	T len() const noexcept
	{
		return sqrt(len2());
	}

	Quaternion<T>& len(T l) noexcept
	{
		mul(l / len());

		return *this;
	}

	Quaternion<T>& normalize() noexcept
	{
		T l = len();

		if (l)
			mul(1 / l);

		return *this;
	}

	template <typename M = Matrix3<T>>
	M toMatrix3() const
	{
		T wx, wy, wz;
		T xx, yy, yz;
		T xy, xz, zz;
		T x2, y2, z2;

		x2 = x + x;
		y2 = y + y;
		z2 = z + z;

		xx = x * x2;
		xy = x * y2;
		xz = x * z2;

		yy = y * y2;
		yz = y * z2;
		zz = z * z2;

		wx = w * x2;
		wy = w * y2;
		wz = w * z2;

		return M(
			1.0 - (yy + zz),
			xy - wz,
			xz + wy,
			xy + wz,
			1.0 - (xx + zz),
			yz - wx,
			xz - wy,
			yz + wx,
			1.0 - (xx + yy));
	}

 	static Quaternion<T> multiply(const Quaternion<T>& a, const Quaternion<T>& b) noexcept
	{
		return Quaternion<T>(
			a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
			a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z);
	}

	bool equals(const Quaternion<T>& q) const noexcept
	{
		return
			FloatEqual<T>(x, q.x)
			&& FloatEqual<T>(y, q.y)
			&& FloatEqual<T>(z, q.z)
			&& FloatEqual<T>(w, q.w);
	}

	bool equals(const Quaternion<T>& q, T eps) const noexcept
	{
		return
			FloatEqual<T>(x, q.x, eps)
			&& FloatEqual<T>(y, q.y, eps)
			&& FloatEqual<T>(z, q.z, eps)
			&& FloatEqual<T>(w, q.w, eps);
	}
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _QUATERNION_HPP_A404199B256E10B1181CEB5FA3BE88B7
//----------------------------------------------------------------------------------------------------
