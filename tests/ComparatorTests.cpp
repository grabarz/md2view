//----------------------------------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>

#include <Comparator.hpp>
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(MathComparatorTests)
//----------------------------------------------------------------------------------------------------

using namespace MD2View;
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(ComparatorTestDouble1)
{
	double value1 = 123.32;
	Comparator<double> a(value1);

	double value2 = 123.32;
	Comparator<double> b(value2);

	BOOST_CHECK(a.equal(b));
	BOOST_CHECK(b.equal(a));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(ComparatorTestDouble2)
{
	double value1 = -123.32;
	Comparator<double> a(value1);

	double value2 = 123.32;
	Comparator<double> b(value2);

	BOOST_CHECK(!a.equal(b));
	BOOST_CHECK(!b.equal(a));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(ComparatorTestDouble3)
{
	double value1 = 123.3242835;
	Comparator<double> a(value1);

	double value2 = 123.3242834;
	Comparator<double> b(value2);

	BOOST_CHECK(!a.equal(b));
	BOOST_CHECK(!b.equal(a));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(ComparatorTestDouble4)
{
	double value1 = 1123.3242833331115;
	Comparator<double> a(value1);

	double value2 = 1123.3242833331114;
	Comparator<double> b(value2);

	BOOST_CHECK(a.equal(b, 4));
	BOOST_CHECK(b.equal(a, 4));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(ComparatorTestFloat1)
{
	double value1 = 123.32;
	Comparator<float> a(value1);

	double value2 = 123.32;
	Comparator<float> b(value2);

	BOOST_CHECK(a.equal(b));
	BOOST_CHECK(b.equal(a));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(ComparatorTestFloat2)
{
	double value1 = -123.32;
	Comparator<float> a(value1);

	double value2 = 123.32;
	Comparator<float> b(value2);

	BOOST_CHECK(!a.equal(b));
	BOOST_CHECK(!b.equal(a));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(ComparatorTestFloat3)
{
	double value1 = 123.3245;
	Comparator<float> a(value1);

	double value2 = 123.3244;
	Comparator<float> b(value2);

	BOOST_CHECK(!a.equal(b));
	BOOST_CHECK(!b.equal(a));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END()
//----------------------------------------------------------------------------------------------------
