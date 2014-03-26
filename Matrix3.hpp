//----------------------------------------------------------------------------------------------------

#ifndef _MATRIX3_HPP_25F4B8E039D3485AADBFBED3EFAD9295
#define _MATRIX3_HPP_25F4B8E039D3485AADBFBED3EFAD9295
//----------------------------------------------------------------------------------------------------

#include "Matrix3_fwd.hpp"

#include <cassert>

#include "At.hpp"
#include "Vector3.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------
// Column oriented (like in OpenGL)
template<typename T, typename V3> class Matrix3
{
	Matrix3()
	{ }

protected:
	T tab[9];

public:
	typedef T scalar_type;
	typedef V3 vector3_type;

	explicit Matrix3(const T d) noexcept
	{
		tab[1] = tab[2] = tab[3] = tab[5] = tab[6] = tab[7] = {};
		tab[0] = tab[4] = tab[8] = d;
	}

	Matrix3(
		const T d0, const T d1, const T d2,
		const T d3, const T d4, const T d5,
		const T d6, const T d7, const T d8) noexcept
	{
		tab[0] = d0; tab[1] = d1; tab[2] = d2;
		tab[3] = d3; tab[4] = d4; tab[5] = d5;
		tab[6] = d6; tab[7] = d7; tab[8] = d8;
	}

	Matrix3(const Matrix3<T, V3>& m) noexcept
	{
		tab[0] = m.tab[0]; tab[1] = m.tab[1]; tab[2] = m.tab[2];
		tab[3] = m.tab[3]; tab[4] = m.tab[4]; tab[5] = m.tab[5];
		tab[6] = m.tab[6]; tab[7] = m.tab[7]; tab[8] = m.tab[8];
	}

	static Matrix3<T, V3> fromColumns(
		const V3& c0, const V3& c1, const V3& c2) noexcept
	{
		return Matrix3<T, V3>(c0[0], c0[1], c0[2], c1[0], c1[1], c1[2], c2[0], c2[1], c2[2]);
	}

	static Matrix3<T, V3> fromRows(
		const V3& r0, const V3& r1, const V3& r2) noexcept
	{
		return Matrix3<T, V3>(r0[0], r1[0], r2[0], r0[1], r1[1], r2[1], r0[2], r1[2], r2[2]);
	}

	const T& at(const std::size_t r, const std::size_t c) const noexcept
	{
		return tab[At<3>(r, c)];
	}

	T& at(const std::size_t r, const std::size_t c) noexcept
	{
		return tab[At<3>(r, c)];
	}

	const T& operator[](std::size_t i) const noexcept
	{
		return tab[i];
	}

	T& operator[](std::size_t i) noexcept
	{
		return tab[i];
	}

	V3 column(const std::size_t i) const noexcept
	{
		return V3(tab[At<3>(0, i)], tab[At<3>(1, i)], tab[At<3>(2, i)]);
	}

	Matrix3<T, V3>& setColumn(const std::size_t i, const V3& v) noexcept
	{
		tab[At<3>(0, i)] = v[0];
		tab[At<3>(1, i)] = v[1];
		tab[At<3>(2, i)] = v[2];

		return *this;
	}

	V3 row(const std::size_t i) const noexcept
	{
		return V3(tab[At<3>(i, 0)], tab[At<3>(i, 1)], tab[At<3>(i, 2)]);
	}

	Matrix3<T, V3>& setRow(const std::size_t i, const V3& v) noexcept
	{
		tab[At<3>(i, 0)] = v[0];
		tab[At<3>(i, 1)] = v[1];
		tab[At<3>(i, 2)] = v[2];

		return *this;
	}

	// algebraic operations
	Matrix3<T, V3>& inc(const Matrix3<T, V3>& m) noexcept
	{
		tab[0] += m.tab[0]; tab[1] += m.tab[1]; tab[2] += m.tab[2];
		tab[3] += m.tab[3]; tab[4] += m.tab[4]; tab[5] += m.tab[5];
		tab[6] += m.tab[6]; tab[7] += m.tab[7]; tab[8] += m.tab[8];

		return *this;
	}

	Matrix3<T, V3>& dec(const Matrix3<T, V3>& m) noexcept
	{
		tab[0] -= m.tab[0]; tab[1] -= m.tab[1]; tab[2] -= m.tab[2];
		tab[3] -= m.tab[3]; tab[4] -= m.tab[4]; tab[5] -= m.tab[5];
		tab[6] -= m.tab[6]; tab[7] -= m.tab[7]; tab[8] -= m.tab[8];

		return *this;
	}

	Matrix3<T, V3>& mul(const T d) noexcept
	{
		tab[0] *= d; tab[1] *= d; tab[2] *= d;
		tab[3] *= d; tab[4] *= d; tab[5] *= d;
		tab[6] *= d; tab[7] *= d; tab[8] *= d;

		return *this;
	}

	Matrix3<T, V3>& lmul(const Matrix3<T, V3>& m) noexcept
	{
		*this = Matrix3<T, V3>::multiply(*this, m);

		return *this;
	}

	Matrix3<T, V3>& rmul(const Matrix3<T, V3>& m) noexcept
	{
		*this = Matrix3<T, V3>::multiply(m, *this);

		return *this;
	}

	const T det() const noexcept
	{
		return
			tab[0] * (tab[4] * tab[8] - tab[5] * tab[7]) +
			tab[1] * (tab[5] * tab[6] - tab[3] * tab[8]) +
			tab[2] * (tab[3] * tab[7] - tab[4] * tab[6]);
	}

	bool equals(const Matrix3<T, V3>& m) const noexcept
	{
		return
			FloatEqual<T>(tab[0], m.tab[0])
			&& FloatEqual<T>(tab[1], m.tab[1])
			&& FloatEqual<T>(tab[2], m.tab[2])
			&& FloatEqual<T>(tab[3], m.tab[3])
			&& FloatEqual<T>(tab[4], m.tab[4])
			&& FloatEqual<T>(tab[5], m.tab[5])
			&& FloatEqual<T>(tab[6], m.tab[6])
			&& FloatEqual<T>(tab[7], m.tab[7])
			&& FloatEqual<T>(tab[8], m.tab[8]);
	}

	bool equals(const Matrix3<T, V3>& m, const T eps) const noexcept
	{
		return
			FloatEqual<T>(tab[0], m.tab[0], eps)
			&& FloatEqual<T>(tab[1], m.tab[1], eps)
			&& FloatEqual<T>(tab[2], m.tab[2], eps)
			&& FloatEqual<T>(tab[3], m.tab[3], eps)
			&& FloatEqual<T>(tab[4], m.tab[4], eps)
			&& FloatEqual<T>(tab[5], m.tab[5], eps)
			&& FloatEqual<T>(tab[6], m.tab[6], eps)
			&& FloatEqual<T>(tab[7], m.tab[7], eps)
			&& FloatEqual<T>(tab[8], m.tab[8], eps);
	}

	static V3 multiply(const Matrix3<T, V3>& m, const V3& v) noexcept
	{
		return V3(
			m.tab[0] * v[0] + m.tab[3] * v[1] + m.tab[6] * v[2],
			m.tab[1] * v[1] + m.tab[4] * v[1] + m.tab[7] * v[2],
			m.tab[2] * v[2] + m.tab[5] * v[1] + m.tab[8] * v[2]);
	}

	static Matrix3<T, V3> multiply(const Matrix3<T, V3>& a, const Matrix3<T, V3>& b) noexcept
	{
		Matrix3<T, V3> m;

		m.tab[At<3>(0, 0)] =
			a.tab[At<3>(0, 0)] * b.tab[At<3>(0, 0)] +
			a.tab[At<3>(0, 1)] * b.tab[At<3>(1, 0)] +
			a.tab[At<3>(0, 2)] * b.tab[At<3>(2, 0)];
		m.tab[At<3>(0, 1)] =
			a.tab[At<3>(0, 0)] * b.tab[At<3>(0, 1)] +
			a.tab[At<3>(0, 1)] * b.tab[At<3>(1, 1)] +
			a.tab[At<3>(0, 2)] * b.tab[At<3>(2, 1)];
		m.tab[At<3>(0, 2)] =
			a.tab[At<3>(0, 0)] * b.tab[At<3>(0, 2)] +
			a.tab[At<3>(0, 1)] * b.tab[At<3>(1, 2)] +
			a.tab[At<3>(0, 2)] * b.tab[At<3>(2, 2)];
		m.tab[At<3>(1, 0)] =
			a.tab[At<3>(1, 0)] * b.tab[At<3>(0, 0)] +
			a.tab[At<3>(1, 1)] * b.tab[At<3>(1, 0)] +
			a.tab[At<3>(1, 2)] * b.tab[At<3>(2, 0)];
		m.tab[At<3>(1, 1)] =
			a.tab[At<3>(1, 0)] * b.tab[At<3>(0, 1)] +
			a.tab[At<3>(1, 1)] * b.tab[At<3>(1, 1)] +
			a.tab[At<3>(1, 2)] * b.tab[At<3>(2, 1)];
		m.tab[At<3>(1, 2)] =
			a.tab[At<3>(1, 0)] * b.tab[At<3>(0, 2)] +
			a.tab[At<3>(1, 1)] * b.tab[At<3>(1, 2)] +
			a.tab[At<3>(1, 2)] * b.tab[At<3>(2, 2)];
		m.tab[At<3>(2, 0)] =
			a.tab[At<3>(2, 0)] * b.tab[At<3>(0, 0)] +
			a.tab[At<3>(2, 1)] * b.tab[At<3>(1, 0)] +
			a.tab[At<3>(2, 2)] * b.tab[At<3>(2, 0)];
		m.tab[At<3>(2, 1)] =
			a.tab[At<3>(2, 0)] * b.tab[At<3>(0, 1)] +
			a.tab[At<3>(2, 1)] * b.tab[At<3>(1, 1)] +
			a.tab[At<3>(2, 2)] * b.tab[At<3>(2, 1)];
		m.tab[At<3>(2, 2)] =
			a.tab[At<3>(2, 0)] * b.tab[At<3>(0, 2)] +
			a.tab[At<3>(2, 1)] * b.tab[At<3>(1, 2)] +
			a.tab[At<3>(2, 2)] * b.tab[At<3>(2, 2)];

		return m;
	}

	static Matrix3<T, V3> transpose(const Matrix3<T, V3>& m) noexcept
	{
		Matrix3<T, V3> r;

		r.tab[At<3>(0, 0)] = m.tab[At<3>(0, 0)];
		r.tab[At<3>(0, 1)] = m.tab[At<3>(1, 0)];
		r.tab[At<3>(0, 2)] = m.tab[At<3>(2, 0)];
		r.tab[At<3>(1, 0)] = m.tab[At<3>(0, 1)];
		r.tab[At<3>(1, 1)] = m.tab[At<3>(1, 1)];
		r.tab[At<3>(1, 2)] = m.tab[At<3>(2, 1)];
		r.tab[At<3>(2, 0)] = m.tab[At<3>(0, 2)];
		r.tab[At<3>(2, 1)] = m.tab[At<3>(1, 2)];
		r.tab[At<3>(2, 2)] = m.tab[At<3>(2, 2)];

		return r;
	}

	static Matrix3<T, V3> inverse(const Matrix3<T, V3>& m) noexcept
	{
		T det = m.det();
	
		assert(det != static_cast<T>(0.0));
			
		Matrix3<T, V3> a;
		
		a.tab[0] =  (m.tab[4] * m.tab[8] - m.tab[5] * m.tab[7]);
		a.tab[1] = -(m.tab[1] * m.tab[8] - m.tab[2] * m.tab[7]);
		a.tab[2] =  (m.tab[1] * m.tab[5] - m.tab[2] * m.tab[4]);
		a.tab[3] = -(m.tab[3] * m.tab[8] - m.tab[5] * m.tab[6]);
		a.tab[4] =  (m.tab[0] * m.tab[8] - m.tab[2] * m.tab[6]);
		a.tab[5] = -(m.tab[0] * m.tab[5] - m.tab[2] * m.tab[3]);
		a.tab[6] =  (m.tab[3] * m.tab[7] - m.tab[4] * m.tab[6]);
		a.tab[7] = -(m.tab[0] * m.tab[7] - m.tab[1] * m.tab[6]);
		a.tab[8] =  (m.tab[0] * m.tab[4] - m.tab[1] * m.tab[3]);

		a.mul(1.0 / det);

		return a;
	}
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _MATRIX3_HPP_25F4B8E039D3485AADBFBED3EFAD9295
//----------------------------------------------------------------------------------------------------
