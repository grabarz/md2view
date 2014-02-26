//----------------------------------------------------------------------------------------------------

#ifndef _COMPARATOR_HPP_1798B1EAD90B4BF6ABC9248E02ABE53E
#define _COMPARATOR_HPP_1798B1EAD90B4BF6ABC9248E02ABE53E
//----------------------------------------------------------------------------------------------------

#include <cstdint>
#include <limits>

#include "Comparator_fwd.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

template<size_t U> struct SizedType
{
	typedef void UInteger;
	typedef void Integer;
};
//----------------------------------------------------------------------------------------------------

template<> struct SizedType<4>
{
	typedef uint32_t UInteger;
	typedef int32_t Integer;
};
//----------------------------------------------------------------------------------------------------

template<> struct SizedType<8>
{
	typedef uint64_t UInteger;
	typedef int64_t Integer;
};
//----------------------------------------------------------------------------------------------------

template<typename F> class Comparator
{
private:
	typedef typename SizedType<sizeof(F)>::UInteger I;

	union Data
	{
		F asFloat;
		I asInteger;
	};

	static const size_t bitsCount = sizeof(F) * 8;
	static const size_t mantissaBitsCount = std::numeric_limits<F>::digits - 1;
	static const size_t exponentBitsCount = bitsCount - 1 - mantissaBitsCount;
	static const I signMask = static_cast<I>(1) << (bitsCount - 1);
	static const I mantissaMask = ~static_cast<I>(0) >> (exponentBitsCount + 1);
	static const I exponentMask = ~(signMask | mantissaMask);
	static const size_t precision = 4;

	Data data;

	static I convert(const I& a) noexcept
	{
		return (signMask & a) ? (~a + 1) : (signMask | a);
	}

	static I distance(const I& a, const I& b) noexcept
	{
		const I aa = convert(a);
		const I bb = convert(b);

		return (aa >= bb) ? (aa - bb) : (bb - aa);
	}

public:
	Comparator(F val)
	{
		data.asFloat = val;
	}

	bool equal(const Comparator<F>& f, size_t prec) const noexcept
	{
		return distance(data.asInteger, f.data.asInteger) <= precision;
	}

	bool equal(const Comparator<F>& f) const noexcept
	{
		return equal(f, precision);
	}
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _COMPARATOR_HPP_1798B1EAD90B4BF6ABC9248E02ABE53E
//----------------------------------------------------------------------------------------------------
