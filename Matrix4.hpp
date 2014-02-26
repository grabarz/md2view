//----------------------------------------------------------------------------------------------------

#ifndef _MATRIX4_HPP_CCF79631D3FF4356A6B8315ADC4E9B34
#define _MATRIX4_HPP_CCF79631D3FF4356A6B8315ADC4E9B34
//----------------------------------------------------------------------------------------------------

#include <cassert>

#include "At.hpp"
#include "Float.hpp"
#include "Matrix4_fwd.hpp"
#include "Vector4.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

// Column oriented (like in OpenGL)
template <typename T, typename V4> class Matrix4
{
	Matrix4() noexcept
	{ }

protected:
	T tab[16];

public:
	typedef T scalar_type;
	typedef V4 vector4_type;

	explicit Matrix4(const T& d) noexcept
	{
		tab[1] = tab[2] = tab[3] = tab[4] = tab[6] = tab[7] =
			tab[8] = tab[9] = tab[11] = tab[12] = tab[13] = tab[14] = static_cast<T>(0.0);
		tab[0] = tab[5] = tab[10] = tab[15] = d;
	}

	Matrix4(
		const T& d0, const T& d1, const T& d2, const T& d3,
		const T& d4, const T& d5, const T& d6, const T& d7,
		const T& d8, const T& d9, const T& d10, const T& d11,
		const T& d12, const T& d13, const T& d14, const T& d15) noexcept
	{
		tab[0] = d0; tab[1] = d1; tab[2] = d2; tab[3] = d3;
		tab[4] = d4; tab[5] = d5; tab[6] = d6; tab[7] = d7;
		tab[8] = d8; tab[9] = d9; tab[10] = d10; tab[11] = d11;
		tab[12] = d12; tab[13] = d13; tab[14] = d14; tab[15] = d15;
	}

	Matrix4(const Matrix4<T, V4>& m) noexcept
	{
		tab[0] = m.tab[0]; tab[1] = m.tab[1]; tab[2] = m.tab[2]; tab[3] = m.tab[3];
		tab[4] = m.tab[4]; tab[5] = m.tab[5]; tab[6] = m.tab[6]; tab[7] = m.tab[7];
		tab[8] = m.tab[8]; tab[9] = m.tab[9]; tab[10] = m.tab[10]; tab[11] = m.tab[11];
		tab[12] = m.tab[12]; tab[13] = m.tab[13]; tab[14] = m.tab[14]; tab[15] = m.tab[15];
	}

	static Matrix4<T, V4> fromColumns(
		const V4& c0, const V4& c1, const V4& c2, const V4& c3) noexcept
	{
		return Matrix4<T, V4>(
			c0[0], c0[1], c0[2], c0[3],
			c1[0], c1[1], c1[2], c1[3],
			c2[0], c2[1], c2[2], c2[3],
			c3[0], c3[1], c3[2], c3[3]);
	}

	static Matrix4<T, V4> fromRows(
		const V4& r0, const V4& r1, const V4& r2, const V4& r3) noexcept
	{
		return Matrix4<T, V4>(
			r0[0], r1[0], r2[0], r3[0],
			r0[1], r1[1], r2[1], r3[1],
			r0[2], r1[2], r2[2], r3[2],
			r0[3], r1[3], r2[3], r3[3]);
	}

	const T& at(const std::size_t r, const std::size_t c) const noexcept
	{
		return tab[At<4>(r, c)];
	}

	T& at(const std::size_t r, const std::size_t c) noexcept
	{
		return tab[At<4>(r, c)];
	}

	const T& operator[](std::size_t i) const noexcept
	{
		return tab[i];
	}

	T& operator[](std::size_t i) noexcept
	{
		return tab[i];
	}

	V4 column(const std::size_t i) const noexcept
	{
		return V4(tab[At<4>(0, i)], tab[At<4>(1, i)], tab[At<4>(2, i)], tab[At<4>(3, i)]);
	}

	Matrix4<T, V4>& setColumn(const std::size_t i, const V4& v) noexcept
	{
		tab[At<4>(0, i)] = v[0];
		tab[At<4>(1, i)] = v[1];
		tab[At<4>(2, i)] = v[2];
		tab[At<4>(3, i)] = v[3];

		return *this;
	}

	V4 row(const std::size_t i) const noexcept
	{
		return V4(tab[At<4>(i, 0)], tab[At<4>(i, 1)], tab[At<4>(i, 2)], tab[At<4>(i, 3)]);
	}

	Matrix4<T, V4>& setRow(const std::size_t i, const V4& v) noexcept
	{
		tab[At<4>(i, 0)] = v[0];
		tab[At<4>(i, 1)] = v[1];
		tab[At<4>(i, 2)] = v[2];
		tab[At<4>(i, 3)] = v[3];

		return *this;
	}

	// algebraic operations
	Matrix4<T, V4>& inc(const Matrix4<T, V4>& m) noexcept
	{
		tab[0] += m.tab[0]; tab[1] += m.tab[1]; tab[2] += m.tab[2]; tab[3] += m.tab[3];
		tab[4] += m.tab[4]; tab[5] += m.tab[5]; tab[6] += m.tab[6]; tab[7] += m.tab[7];
		tab[8] += m.tab[8]; tab[9] += m.tab[9]; tab[10] += m.tab[10]; tab[11] += m.tab[11];
		tab[12] += m.tab[12]; tab[13] += m.tab[13]; tab[14] += m.tab[14]; tab[15] += m.tab[15];

		return *this;
	}

	Matrix4<T, V4>& dec(const Matrix4<T, V4>& m) noexcept
	{
		tab[0] -= m.tab[0]; tab[1] -= m.tab[1]; tab[2] -= m.tab[2]; tab[3] -= m.tab[3];
		tab[4] -= m.tab[4]; tab[5] -= m.tab[5]; tab[6] -= m.tab[6]; tab[7] -= m.tab[7];
		tab[8] -= m.tab[8]; tab[9] -= m.tab[9]; tab[10] -= m.tab[10]; tab[11] -= m.tab[11];
		tab[12] -= m.tab[12]; tab[13] -= m.tab[13]; tab[14] -= m.tab[14]; tab[15] -= m.tab[15];

		return *this;
	}

	Matrix4<T, V4>& mul(const T& d) noexcept
	{
		tab[0] *= d; tab[1] *= d; tab[2] *= d; tab[3] *= d;
		tab[4] *= d; tab[5] *= d; tab[6] *= d; tab[7] *= d;
		tab[8] *= d; tab[9] *= d; tab[10] *= d; tab[11] *= d;
		tab[12] *= d; tab[13] *= d; tab[14] *= d; tab[15] *= d;

		return *this;
	}

	Matrix4<T, V4>& lmul(const Matrix4<T, V4>& m) noexcept
	{
		*this = Matrix4<T, V4>::multiply(*this, m);

		return *this;
	}

	Matrix4<T, V4>& rmul(const Matrix4<T, V4>& m) noexcept
	{
		*this = Matrix4<T, V4>::multiply(m, *this);

		return *this;
	}

	const T det() const noexcept
	{
		return
			+ tab[At<4>(0, 0)] * (
				+ tab[At<4>(1, 1)] * (tab[At<4>(2, 2)] * tab[At<4>(3, 3)] - tab[At<4>(2, 3)] * tab[At<4>(3, 2)])
				- tab[At<4>(1, 2)] * (tab[At<4>(2, 1)] * tab[At<4>(3, 3)] - tab[At<4>(2, 3)] * tab[At<4>(3, 1)])
				+ tab[At<4>(1, 3)] * (tab[At<4>(2, 1)] * tab[At<4>(3, 2)] - tab[At<4>(2, 2)] * tab[At<4>(3, 1)]))
			- tab[At<4>(0, 1)] * (
				+ tab[At<4>(1, 0)] * (tab[At<4>(2, 2)] * tab[At<4>(3, 3)] - tab[At<4>(2, 3)] * tab[At<4>(3, 2)])
				- tab[At<4>(1, 2)] * (tab[At<4>(2, 0)] * tab[At<4>(3, 3)] - tab[At<4>(2, 3)] * tab[At<4>(3, 0)])
				+ tab[At<4>(1, 3)] * (tab[At<4>(2, 0)] * tab[At<4>(3, 2)] - tab[At<4>(2, 2)] * tab[At<4>(3, 0)]))
			+ tab[At<4>(0, 2)] * (
				+ tab[At<4>(1, 0)] * (tab[At<4>(2, 1)] * tab[At<4>(3, 3)] - tab[At<4>(2, 3)] * tab[At<4>(3, 1)])
				- tab[At<4>(1, 1)] * (tab[At<4>(2, 0)] * tab[At<4>(3, 3)] - tab[At<4>(2, 3)] * tab[At<4>(3, 0)])
				+ tab[At<4>(1, 3)] * (tab[At<4>(2, 0)] * tab[At<4>(3, 1)] - tab[At<4>(2, 1)] * tab[At<4>(3, 0)]))
			- tab[At<4>(0, 3)] * (
				+ tab[At<4>(1, 0)] * (tab[At<4>(2, 1)] * tab[At<4>(3, 2)] - tab[At<4>(2, 2)] * tab[At<4>(3, 1)])
				- tab[At<4>(1, 1)] * (tab[At<4>(2, 0)] * tab[At<4>(3, 2)] - tab[At<4>(2, 2)] * tab[At<4>(3, 0)])
				+ tab[At<4>(1, 2)] * (tab[At<4>(2, 0)] * tab[At<4>(3, 1)] - tab[At<4>(2, 1)] * tab[At<4>(3, 0)]));
	}

	bool equals(const Matrix4<T, V4>& m) const noexcept
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
			&& FloatEqual<T>(tab[8], m.tab[8])
			&& FloatEqual<T>(tab[9], m.tab[9])
			&& FloatEqual<T>(tab[10], m.tab[10])
			&& FloatEqual<T>(tab[11], m.tab[11])
			&& FloatEqual<T>(tab[12], m.tab[12])
			&& FloatEqual<T>(tab[13], m.tab[13])
			&& FloatEqual<T>(tab[14], m.tab[14])
			&& FloatEqual<T>(tab[15], m.tab[15]);
	}

	bool equals(const Matrix4<T, V4>& m, const T& eps) const noexcept
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
			&& FloatEqual<T>(tab[8], m.tab[8], eps)
			&& FloatEqual<T>(tab[9], m.tab[9], eps)
			&& FloatEqual<T>(tab[10], m.tab[10], eps)
			&& FloatEqual<T>(tab[11], m.tab[11], eps)
			&& FloatEqual<T>(tab[12], m.tab[12], eps)
			&& FloatEqual<T>(tab[13], m.tab[13], eps)
			&& FloatEqual<T>(tab[14], m.tab[14], eps)
			&& FloatEqual<T>(tab[15], m.tab[15], eps);
	}

	static V4 multiply(const Matrix4<T, V4>& m, const V4& v) noexcept
	{
		return V4(
			m.tab[0] * v[0] + m.tab[4] * v[1] + m.tab[8] * v[2] + m.tab[12] * v[3],
			m.tab[1] * v[1] + m.tab[5] * v[1] + m.tab[9] * v[2] + m.tab[13] * v[3],
			m.tab[2] * v[2] + m.tab[6] * v[1] + m.tab[10] * v[2] + m.tab[14] * v[3],
			m.tab[2] * v[3] + m.tab[7] * v[1] + m.tab[11] * v[2] + m.tab[15] * v[3]);
	}

	static Matrix4<T, V4> multiply(const Matrix4<T, V4>& a, const Matrix4<T, V4>& b) noexcept
	{
		Matrix4<T, V4> m;

		m.tab[At<4>(0, 0)] =
			a.tab[At<4>(0, 0)] * b.tab[At<4>(0, 0)] + a.tab[At<4>(0, 1)] * b.tab[At<4>(1, 0)] +
			a.tab[At<4>(0, 2)] * b.tab[At<4>(2, 0)] + a.tab[At<4>(0, 3)] * b.tab[At<4>(3, 0)];
		m.tab[At<4>(0, 1)] =
			a.tab[At<4>(0, 0)] * b.tab[At<4>(0, 1)] + a.tab[At<4>(0, 1)] * b.tab[At<4>(1, 1)] +
			a.tab[At<4>(0, 2)] * b.tab[At<4>(2, 1)] + a.tab[At<4>(0, 3)] * b.tab[At<4>(3, 1)];
		m.tab[At<4>(0, 2)] =
			a.tab[At<4>(0, 0)] * b.tab[At<4>(0, 2)] + a.tab[At<4>(0, 1)] * b.tab[At<4>(1, 2)] +
			a.tab[At<4>(0, 2)] * b.tab[At<4>(2, 2)] + a.tab[At<4>(0, 3)] * b.tab[At<4>(3, 2)];
		m.tab[At<4>(0, 3)] =
			a.tab[At<4>(0, 0)] * b.tab[At<4>(0, 3)] + a.tab[At<4>(0, 1)] * b.tab[At<4>(1, 3)] +
			a.tab[At<4>(0, 2)] * b.tab[At<4>(2, 3)] + a.tab[At<4>(0, 3)] * b.tab[At<4>(3, 3)];
		m.tab[At<4>(1, 0)] =
			a.tab[At<4>(1, 0)] * b.tab[At<4>(0, 0)] + a.tab[At<4>(1, 1)] * b.tab[At<4>(1, 0)] +
			a.tab[At<4>(1, 2)] * b.tab[At<4>(2, 0)] + a.tab[At<4>(1, 3)] * b.tab[At<4>(3, 0)];
		m.tab[At<4>(1, 1)] =
			a.tab[At<4>(1, 0)] * b.tab[At<4>(0, 1)] + a.tab[At<4>(1, 1)] * b.tab[At<4>(1, 1)] +
			a.tab[At<4>(1, 2)] * b.tab[At<4>(2, 1)] + a.tab[At<4>(1, 3)] * b.tab[At<4>(3, 1)];
		m.tab[At<4>(1, 2)] =
			a.tab[At<4>(1, 0)] * b.tab[At<4>(0, 2)] + a.tab[At<4>(1, 1)] * b.tab[At<4>(1, 2)] +
			a.tab[At<4>(1, 2)] * b.tab[At<4>(2, 2)] + a.tab[At<4>(1, 3)] * b.tab[At<4>(3, 2)];
		m.tab[At<4>(1, 3)] =
			a.tab[At<4>(1, 0)] * b.tab[At<4>(0, 3)] + a.tab[At<4>(1, 1)] * b.tab[At<4>(1, 3)] +
			a.tab[At<4>(1, 2)] * b.tab[At<4>(2, 3)] + a.tab[At<4>(1, 3)] * b.tab[At<4>(3, 3)];
		m.tab[At<4>(2, 0)] =
			a.tab[At<4>(2, 0)] * b.tab[At<4>(0, 0)] + a.tab[At<4>(2, 1)] * b.tab[At<4>(1, 0)] +
			a.tab[At<4>(2, 2)] * b.tab[At<4>(2, 0)] + a.tab[At<4>(2, 3)] * b.tab[At<4>(3, 0)];
		m.tab[At<4>(2, 1)] =
			a.tab[At<4>(2, 0)] * b.tab[At<4>(0, 1)] + a.tab[At<4>(2, 1)] * b.tab[At<4>(1, 1)] +
			a.tab[At<4>(2, 2)] * b.tab[At<4>(2, 1)] + a.tab[At<4>(2, 3)] * b.tab[At<4>(3, 1)];
		m.tab[At<4>(2, 2)] =
			a.tab[At<4>(2, 0)] * b.tab[At<4>(0, 2)] + a.tab[At<4>(2, 1)] * b.tab[At<4>(1, 2)] +
			a.tab[At<4>(2, 2)] * b.tab[At<4>(2, 2)] + a.tab[At<4>(2, 3)] * b.tab[At<4>(3, 2)];
		m.tab[At<4>(2, 3)] =
			a.tab[At<4>(2, 0)] * b.tab[At<4>(0, 3)] + a.tab[At<4>(2, 1)] * b.tab[At<4>(1, 3)] +
			a.tab[At<4>(2, 2)] * b.tab[At<4>(2, 3)] + a.tab[At<4>(2, 3)] * b.tab[At<4>(3, 3)];
		m.tab[At<4>(3, 0)] =
			a.tab[At<4>(3, 0)] * b.tab[At<4>(0, 0)] + a.tab[At<4>(3, 1)] * b.tab[At<4>(1, 0)] +
			a.tab[At<4>(3, 2)] * b.tab[At<4>(2, 0)] + a.tab[At<4>(3, 3)] * b.tab[At<4>(3, 0)];
		m.tab[At<4>(3, 1)] =
			a.tab[At<4>(3, 0)] * b.tab[At<4>(0, 1)] + a.tab[At<4>(3, 1)] * b.tab[At<4>(1, 1)] +
			a.tab[At<4>(3, 2)] * b.tab[At<4>(2, 1)] + a.tab[At<4>(3, 3)] * b.tab[At<4>(3, 1)];
		m.tab[At<4>(3, 2)] =
			a.tab[At<4>(3, 0)] * b.tab[At<4>(0, 2)] + a.tab[At<4>(3, 1)] * b.tab[At<4>(1, 2)] +
			a.tab[At<4>(3, 2)] * b.tab[At<4>(2, 2)] + a.tab[At<4>(3, 3)] * b.tab[At<4>(3, 2)];
		m.tab[At<4>(3, 3)] =
			a.tab[At<4>(3, 0)] * b.tab[At<4>(0, 3)] + a.tab[At<4>(3, 1)] * b.tab[At<4>(1, 3)] +
			a.tab[At<4>(3, 2)] * b.tab[At<4>(2, 3)] + a.tab[At<4>(3, 3)] * b.tab[At<4>(3, 3)];

		return m;
	}

	static Matrix4<T, V4> transpose(const Matrix4<T, V4>& m) noexcept
	{
		Matrix4<T, V4> r;

		r.tab[At<4>(0, 0)] = m.tab[At<4>(0, 0)];
		r.tab[At<4>(0, 1)] = m.tab[At<4>(1, 0)];
		r.tab[At<4>(0, 2)] = m.tab[At<4>(2, 0)];
		r.tab[At<4>(0, 3)] = m.tab[At<4>(3, 0)];
		r.tab[At<4>(1, 0)] = m.tab[At<4>(0, 1)];
		r.tab[At<4>(1, 1)] = m.tab[At<4>(1, 1)];
		r.tab[At<4>(1, 2)] = m.tab[At<4>(2, 1)];
		r.tab[At<4>(1, 3)] = m.tab[At<4>(3, 1)];
		r.tab[At<4>(2, 0)] = m.tab[At<4>(0, 2)];
		r.tab[At<4>(2, 1)] = m.tab[At<4>(1, 2)];
		r.tab[At<4>(2, 2)] = m.tab[At<4>(2, 2)];
		r.tab[At<4>(2, 3)] = m.tab[At<4>(3, 2)];
		r.tab[At<4>(3, 0)] = m.tab[At<4>(0, 3)];
		r.tab[At<4>(3, 1)] = m.tab[At<4>(1, 3)];
		r.tab[At<4>(3, 2)] = m.tab[At<4>(2, 3)];
		r.tab[At<4>(3, 3)] = m.tab[At<4>(3, 3)];

		return r;
	}

	static Matrix4<T, V4> inverse(const Matrix4<T, V4>& m) noexcept
	{
		Matrix4<T, V4> a;

		a.tab[0] =
			m.tab[5] * (m.tab[10] * m.tab[15] - m.tab[11] * m.tab[14]) -
			m.tab[9] * (m.tab[6] * m.tab[15] - m.tab[7] * m.tab[14]) +
			m.tab[13] * (m.tab[6] * m.tab[11] - m.tab[7] * m.tab[10]);

		a.tab[4] =
			m.tab[4] * (m.tab[11] * m.tab[14] - m.tab[10] * m.tab[15]) +
			m.tab[8] * (m.tab[6] * m.tab[15] - m.tab[7] * m.tab[14]) -
			m.tab[12] * (m.tab[6] * m.tab[11] - m.tab[7] * m.tab[10]);

		a.tab[8] =
			m.tab[4] * (m.tab[9] * m.tab[15] - m.tab[11] * m.tab[13]) -
			m.tab[8] * (m.tab[5] * m.tab[15] - m.tab[7] * m.tab[13]) +
			m.tab[12] * (m.tab[5] * m.tab[11] - m.tab[7] * m.tab[9]);

		a.tab[12] =
			m.tab[4] * (m.tab[10] * m.tab[13] - m.tab[9] * m.tab[14]) +
			m.tab[8] * (m.tab[5] * m.tab[14] - m.tab[6] * m.tab[13]) -
			m.tab[12] * (m.tab[5] * m.tab[10] - m.tab[6] * m.tab[9]);

		a.tab[1] =
			m.tab[1] * (m.tab[11] * m.tab[14] - m.tab[10] * m.tab[15]) +
			m.tab[9] * (m.tab[2] * m.tab[15] - m.tab[3] * m.tab[14]) -
			m.tab[13] * (m.tab[2] * m.tab[11] - m.tab[3] * m.tab[10]);

		a.tab[5] =
			m.tab[0] * (m.tab[10] * m.tab[15] - m.tab[11] * m.tab[14]) -
			m.tab[8] * (m.tab[2] * m.tab[15] - m.tab[3] * m.tab[14]) +
			m.tab[12] * (m.tab[2] * m.tab[11] - m.tab[3] * m.tab[10]);

		a.tab[9] =
			m.tab[0] * (m.tab[11] * m.tab[13] - m.tab[9] * m.tab[15]) +
			m.tab[8] * (m.tab[1] * m.tab[15] - m.tab[3] * m.tab[13]) -
			m.tab[12] * (m.tab[1] * m.tab[11] - m.tab[3] * m.tab[9]);

		a.tab[13] =
			m.tab[0] * (m.tab[9] * m.tab[14] - m.tab[10] * m.tab[13]) -
			m.tab[8] * (m.tab[1] * m.tab[14] - m.tab[2] * m.tab[13]) +
			m.tab[12] * (m.tab[1] * m.tab[10] - m.tab[2] * m.tab[9]);

		a.tab[2] =
			m.tab[1] * (m.tab[6] * m.tab[15] - m.tab[7] * m.tab[14]) -
			m.tab[5] * (m.tab[2] * m.tab[15] - m.tab[3] * m.tab[14]) +
			m.tab[13] * (m.tab[2] * m.tab[7] - m.tab[3] * m.tab[6]);

		a.tab[6] =
			m.tab[0] * (m.tab[7] * m.tab[14] - m.tab[6] * m.tab[15]) +
			m.tab[4] * (m.tab[2] * m.tab[15] - m.tab[3] * m.tab[14]) -
			m.tab[12] * (m.tab[2] * m.tab[7] - m.tab[3] * m.tab[6]);

		a.tab[10] =
			m.tab[0] * (m.tab[5] * m.tab[15] - m.tab[7] * m.tab[13]) -
			m.tab[4] * (m.tab[1] * m.tab[15] - m.tab[3] * m.tab[13]) +
			m.tab[12] * (m.tab[1] * m.tab[7] - m.tab[3] * m.tab[5]);

		a.tab[14] =
			m.tab[0] * (m.tab[6] * m.tab[13] - m.tab[5] * m.tab[14]) +
			m.tab[4] * (m.tab[1] * m.tab[14] - m.tab[2] * m.tab[13]) -
			m.tab[12] * (m.tab[1] * m.tab[6] - m.tab[2] * m.tab[5]);

		a.tab[3] =
			m.tab[1] * (m.tab[7] * m.tab[10] - m.tab[6] * m.tab[11]) +
			m.tab[5] * (m.tab[2] * m.tab[11] - m.tab[3] * m.tab[10]) -
			m.tab[9] * (m.tab[2] * m.tab[7] - m.tab[3] * m.tab[6]);

		a.tab[7] =
			m.tab[0] * (m.tab[6] * m.tab[11] - m.tab[7] * m.tab[10]) -
			m.tab[4] * (m.tab[2] * m.tab[11] - m.tab[3] * m.tab[10]) +
			m.tab[8] * (m.tab[2] * m.tab[7] - m.tab[3] * m.tab[6]);

		a.tab[11] =
			m.tab[0] * (m.tab[7] * m.tab[9] - m.tab[5] * m.tab[11]) +
			m.tab[4] * (m.tab[1] * m.tab[11] - m.tab[3] * m.tab[9]) -
			m.tab[8] * (m.tab[1] * m.tab[7] - m.tab[3] * m.tab[5]);

		a.tab[15] =
			m.tab[0] * (m.tab[5] * m.tab[10] - m.tab[6] * m.tab[9]) -
			m.tab[4] * (m.tab[1] * m.tab[10] - m.tab[2] * m.tab[9]) +
			m.tab[8] * (m.tab[1] * m.tab[6] - m.tab[2] * m.tab[5]);

		T det =
			m.tab[0] * a.tab[0] + m.tab[1] * a.tab[4] +
			m.tab[2] * a.tab[8] + m.tab[3] * a.tab[12];

		assert(det != static_cast<T>(0.0));

		a.mul(1.0 / det);

		return a;
	}
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _MATRIX3_HPP_CCF79631D3FF4356A6B8315ADC4E9B34
//----------------------------------------------------------------------------------------------------
