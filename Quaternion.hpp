//----------------------------------------------------------------------------------------------------

#ifndef _QUATERNION_HPP_A404199B256E10B1181CEB5FA3BE88B7
#define _QUATERNION_HPP_A404199B256E10B1181CEB5FA3BE88B7
//----------------------------------------------------------------------------------------------------

#include "Quaternion_fwd.hpp"

#include "Vector3.hpp"
#include "Vector4.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

template <typename T>
class Quaternion
{
	T data[4];

public:
	typedef T scalar_type;

	Quaternion() noexcept
	{
		data[0] = data[1] = data[2] = data[3] = {};
	}

	Quaternion(T x, T y, T z, T w) noexcept
	{
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}

	Quaternion(const Vector4<T>& v) noexcept
	{
		data[0] = v[0];
		data[1] = v[1];
		data[2] = v[2];
		data[3] = v[3];
	}

	Quaternion<T>& operator=(const Quaternion<T>& q) noexcept
	{
		data[0] = q.data[0];
		data[1] = q.data[1];
		data[2] = q.data[2];
		data[3] = q.data[3];

		return *this;
	}

	Quaternion<T>& operator=(const Vector4<T>& v) noexcept
	{
		data[0] = v[0];
		data[1] = v[1];
		data[2] = v[2];
		data[3] = v[3];

		return *this;
	}

	T* get() noexcept
	{
		return &data[0];
	}

	const T* get() const noexcept
	{
		return &data[0];
	}

	T& operator[](std::size_t i) noexcept
	{
		return data[i];
	}

	T operator[](std::size_t i) const noexcept
	{
		return data[i];
	}

	Quaternion<T>& inc(const Quaternion<T>& q) noexcept
	{
		data[0] += q.data[0];
		data[1] += q.data[1];
		data[2] += q.data[2];
		data[3] += q.data[3];

		return *this;
	}

	Quaternion<T>& inc(const Quaternion<T>& q, T scale) noexcept
	{
		data[0] += scale * q.data[0];
		data[1] += scale * q.data[1];
		data[2] += scale * q.data[2];
		data[3] += scale * q.data[3];

		return *this;
	}

	Quaternion<T>& dec(const Quaternion<T>& q) noexcept
	{
		data[0] -= q.data[0];
		data[1] -= q.data[1];
		data[2] -= q.data[2];
		data[3] -= q.data[3];

		return *this;
	}

	Quaternion<T>& mul(T a) noexcept
	{
		data[0] *= a;
		data[1] *= a;
		data[2] *= a;
		data[3] *= a;

		return *this;
	}

	Vector3<T> mul(const Vector3<T>& v) noexcept
	{
		T xx = data[0] * data[0];
		T yy = data[1] * data[1];
		T zz = data[2] * data[2];
		T ww = data[3] * data[3];

		T xxzz = xx - zz;
		T wwyy = ww - yy;

		T xw2 = data[0] * data[3] * 2.0;
		T xy2 = data[0] * data[1] * 2.0;
		T xz2 = data[0] * data[2] * 2.0;
		T yw2 = data[1] * data[3] * 2.0;
		T yz2 = data[1] * data[2] * 2.0;
		T zw2 = data[2] * data[3] * 2.0;

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
		return data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3];
	}

	T len() const noexcept
	{
		return sqrt(len2());
	}

	Quaternion<T>& len(T l) noexcept
	{
		normalize().mul(l);

		return *this;
	}

	Quaternion<T>& normalize() noexcept
	{
		T l = len();

		if (l)
			mul(1 / l);

		return *this;
	}

	static Quaternion<T> multiply(const Quaternion<T>& a, const Quaternion<T>& b) noexcept
	{
		return Quaternion<T>(
			a.data[3] * b.data[0] + a.data[0] * b.data[3] + a.data[1] * b.data[2] - a.data[2] * b.data[1],
			a.data[3] * b.data[1] + a.data[1] * b.data[3] + a.data[2] * b.data[0] - a.data[0] * b.data[2],
			a.data[3] * b.data[2] + a.data[2] * b.data[3] + a.data[0] * b.data[1] - a.data[1] * b.data[0],
			a.data[3] * b.data[3] - a.data[0] * b.data[0] - a.data[1] * b.data[1] - a.data[2] * b.data[2]);
	}

	bool equals(const Quaternion<T>& q) const noexcept
	{
		return
			FloatEqual<T>(data[0], q.data[0])
			&& FloatEqual<T>(data[1], q.data[1])
			&& FloatEqual<T>(data[2], q.data[2])
			&& FloatEqual<T>(data[3], q.data[3]);
	}

	bool equals(const Quaternion<T>& q, T eps) const noexcept
	{
		return
			FloatEqual<T>(data[0], q.data[0], eps)
			&& FloatEqual<T>(data[1], q.data[1], eps)
			&& FloatEqual<T>(data[2], q.data[2], eps)
			&& FloatEqual<T>(data[3], q.data[3], eps);
	}
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _QUATERNION_HPP_A404199B256E10B1181CEB5FA3BE88B7
//----------------------------------------------------------------------------------------------------
