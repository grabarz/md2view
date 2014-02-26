//----------------------------------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>

#include <Float.hpp>
#include <Vector4.hpp>
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(MathVector4Tests)
//----------------------------------------------------------------------------------------------------

using namespace MD2View;
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(ZeroVectorTest)
{
	const Vector4<double> a;
	const Vector4<double> b {0.0, 0.0, 0.0, 0.0};

	BOOST_CHECK(a == b);
	BOOST_CHECK(a.equals(b));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(EqualsTest)
{
	const Vector4<double> a {32.3, 435.432344, 3454.343400, 3.23440099};
	const Vector4<double> b {32.3, 435.432344, 3454.343400, 3.23440099};

	BOOST_CHECK(a.equals(a));
	BOOST_CHECK(a.equals(b));
	BOOST_CHECK(b.equals(a));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(IndexingTest)
{
	Vector4<double> a {2.3, 4.2, 8.1, 3.3};

	BOOST_CHECK(FloatEqual<double>(a[0], 2.3));
	BOOST_CHECK(FloatEqual<double>(a[1], 4.2));
	BOOST_CHECK(FloatEqual<double>(a[2], 8.1));
	BOOST_CHECK(FloatEqual<double>(a[3], 3.3));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(IncTest)
{
	Vector4<double> a {2.3, 4.2, 8.1, 6.7};
	Vector4<double> b {1.3, 1.2, 0.1, 0.001};

	BOOST_CHECK(a.inc(b).equals({3.6, 5.4, 8.2, 6.701}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(IncScaledTest)
{
	Vector4<double> a {2.3, 4.2, 8.1, 6.7};
	Vector4<double> b {1.3, 1.2, 0.1, 0.001};

	BOOST_CHECK(a.inc(b, 10.0).equals({15.3, 16.2, 9.1, 6.71}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(DecTest)
{
	Vector4<double> a {2.3, 4.2, 8.1, 3.4};
	Vector4<double> b {1.3, 1.2, 0.1, 0.2};

	BOOST_CHECK(a.dec(b).equals({1.0, 3.0, 8.0, 3.2}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(NegTest)
{
	Vector4<double> a {2.3, 4.2, 8.1, 5.3};

	BOOST_CHECK(a.neg().equals({-2.3, -4.2, -8.1, -5.3}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(MulTest)
{
	Vector4<double> a {2.3, 4.2, 8.1, 7.2};

	BOOST_CHECK(a.mul(2.0).equals({4.6, 8.4, 16.2, 14.4}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(DivTest)
{
	Vector4<double> a {4.6, 8.4, 16.2, 14.4};

	BOOST_CHECK(a.div(2.0).equals({2.3, 4.2, 8.1, 7.2}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(NormalizeTest)
{
	Vector4<double> a {10.0, 0.0, 0.0, 0.0};

	BOOST_CHECK(a.normalize().equals({1.0, 0.0, 0.0, 0.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Len2Test)
{
	const Vector4<double> a {10.0, 0.0, 0.0, 0.0};

	BOOST_CHECK(FloatEqual<double>(a.len2(), 100.0));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(LenTest)
{
	const Vector4<double> a {10.0, 0.0, 0.0, 0.0};

	BOOST_CHECK(FloatEqual<double>(a.len(), 10.0));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(LenSetTest)
{
	Vector4<double> a {10.0, 0.0, 0.0, 0.0};

	BOOST_CHECK(FloatEqual<double>(a.len(2.0).len(), 2.0));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(DotProducTest)
{
	const Vector4<double> a {1.0, 3.0, -5.0, 1.0};
	const Vector4<double> b {4.0, -2.0, -1.0, 1.0};

	BOOST_CHECK(FloatEqual<double>(Vector4<double>::dotProduct(a, b), 4.0));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(CrossProductTest)
{
	// Vector4<double> a {2.0, 1.0, -1.0};
	// Vector4<double> b {-3.0, 4.0, 1.0};
	// Vector4<double> c {5.0, 1.0, 11.0};

	// BOOST_CHECK(a.rprod(b).equals(c));
	// BOOST_CHECK(b.rprod(a).equals(c.neg()));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END()
//----------------------------------------------------------------------------------------------------
