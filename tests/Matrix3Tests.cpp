//----------------------------------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>

#include <Float.hpp>
#include <Matrix3.hpp>
#include <Vector3.hpp>
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(MathMatrix3Tests)
//----------------------------------------------------------------------------------------------------

using namespace MD2View;
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(CompareTest)
{
	Matrix3<double> m {2.0, 4.5, 2.4, 5.5, 9.2, 4.6, 4.2, 1.3, 4.7};
	Matrix3<double> mm {2.0, 4.5, 2.4, 5.5, 9.2, 4.6, 4.2, 1.3, 4.7};

	BOOST_CHECK(m.equals(mm));
	BOOST_CHECK(mm.equals(m));
	BOOST_CHECK(m.equals(m));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(ZeroTest)
{
	Matrix3<double> m(0.0);
	Matrix3<double> mm {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

	BOOST_CHECK(m.equals(mm));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(CopyConstructorTest)
{
	Matrix3<double> m {2.0, 4.5, 2.4, 5.5, 9.2, 4.6, 4.2, 1.3, 4.7};
	Matrix3<double> mm(m);

	BOOST_CHECK(m.equals(mm));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(DiagonalTest)
{
	Matrix3<double> m(5.0);
	Matrix3<double> mm {5.0, 0.0, 0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 5.0};

	BOOST_CHECK(m.equals(mm));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(MakeFromColumnsTest)
{
	Vector3<double> v1 {-2.0, 3.3, 4.5};
	Vector3<double> v2 {3.5, 2.3, -8.4};
	Vector3<double> v3 {7.4, -3.5, 4.5};

	auto m = Matrix3<double>::fromColumns(v1, v2, v3);
	Matrix3<double> mm {-2.0, 3.3, 4.5, 3.5, 2.3, -8.4, 7.4, -3.5, 4.5};

	BOOST_CHECK(m.equals(mm));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(MakeFromRowsTest)
{
	Vector3<double> v1 {-2.0, 3.3, 4.5};
	Vector3<double> v2 {3.5, 2.3, -8.4};
	Vector3<double> v3 {7.4, -3.5, 4.5};

	Matrix3<double> m = Matrix3<double>::fromRows(v1, v2, v3);
	Matrix3<double> mm {-2.0, 3.5, 7.4, 3.3, 2.3, -3.5, 4.5, -8.4, 4.5};

	BOOST_CHECK(m.equals(mm));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(AtTest)
{
	Matrix3<double> m {-2.0, 3.5, 7.4, 3.3, 2.3, -3.5, 4.5, -8.4, 4.5};

	BOOST_CHECK(FloatEqual<double>(m.at(1, 0), 3.5));
	BOOST_CHECK(FloatEqual<double>(m.at(0, 1), 3.3));
	BOOST_CHECK(FloatEqual<double>(m.at(1, 2), -8.4));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(GetColumnTest)
{
	Matrix3<double> m {-2.0, 3.5, 7.4, 3.3, 2.3, -3.5, 4.5, -8.4, 4.5};

	BOOST_CHECK(m.column(0).equals({-2.0, 3.5, 7.4}));
	BOOST_CHECK(m.column(2).equals({4.5, -8.4, 4.5}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(SetColumnTest)
{
	Matrix3<double> m {-2.0, 3.5, 7.4, 3.3, 2.3, -3.5, 4.5, -8.4, 4.5};
	Vector3<double> v {0.4, 3.7, -35.3};

	BOOST_CHECK(m.setColumn(2, v).column(2).equals(v));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(GetRowTest)
{
	Matrix3<double> m {-2.0, 3.5, 7.4, 3.3, 2.3, -3.5, 4.5, -8.4, 4.5};

	BOOST_CHECK(m.row(0).equals({-2.0, 3.3, 4.5}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(SetRowTest)
{
	Matrix3<double> m {-2.0, 3.5, 7.4, 3.3, 2.3, -3.5, 4.5, -8.4, 4.5};
	Vector3<double> v {0.4, 3.7, -35.3};

	BOOST_CHECK(m.setRow(2, v).row(2).equals(v));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(IncTest)
{
	Matrix3<double> m {-2.0, 3.5, 7.4, 3.3, 2.3, -3.5, 4.5, -8.4, 4.5};
	Matrix3<double> mm {-2.0, 3.5, 7.4, 3.3, 2.3, -3.5, 4.5, -8.4, 4.5};

	BOOST_CHECK(m.inc(mm).equals({-4.0, 7.0, 14.8, 6.6, 4.6, -7.0, 9.0, -16.8, 9.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(DecTest)
{
	Matrix3<double> m {-4.0, 7.0, 14.8, 6.6, 4.6, -7.0, 9.0, -16.8, 9.0};
	Matrix3<double> mm {-2.0, 3.5, 7.4, 3.3, 2.3, -3.5, 4.5, -8.4, 4.5};

	BOOST_CHECK(m.dec(mm).equals(mm));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(StaticMultiplyTest)
{
	Matrix3<double> m {1.0, 4.0, 2.0, 2.0, 3.0, 3.0, 4.0, 1.0, 5.0};
	Matrix3<double> mm {3.0, -2.0, 3.0, 9.0, 8.0, 1.0, 1.0, 2.0, 4.0};
	Matrix3<double> r {11.0, 9.0, 15.0, 29.0, 61.0, 47.0, 21.0, 14.0, 28.0};

	BOOST_CHECK(Matrix3<double>::multiply(m, mm).equals(r));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(LeftMultiplyTest)
{
	Matrix3<double> m {1.0, 4.0, 2.0, 2.0, 3.0, 3.0, 4.0, 1.0, 5.0};
	Matrix3<double> mm {3.0, -2.0, 3.0, 9.0, 8.0, 1.0, 1.0, 2.0, 4.0};
	Matrix3<double> r {11.0, 9.0, 15.0, 29.0, 61.0, 47.0, 21.0, 14.0, 28.0};

	m.lmul(mm);
	BOOST_CHECK(m.equals(r));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(RightMultiplyTest)
{
	Matrix3<double> m {1.0, 4.0, 2.0, 2.0, 3.0, 3.0, 4.0, 1.0, 5.0};
	Matrix3<double> mm {3.0, -2.0, 3.0, 9.0, 8.0, 1.0, 1.0, 2.0, 4.0};
	Matrix3<double> r {11.0, 9.0, 15.0, 29.0, 61.0, 47.0, 21.0, 14.0, 28.0};

	mm.rmul(m);
	BOOST_CHECK(mm.equals(r));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(VectorMultiplyTest)
{
	Matrix3<double> m(1.0);
	Vector3<double> v(2.0, 3.0, 4.0);
	Vector3<double> u(2.1, 3.1, 4.1);

	BOOST_CHECK(Matrix3<double>::multiply(m, v).equals(v));
	BOOST_CHECK(!Matrix3<double>::multiply(m, v).equals(u));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(ScalarMultiplyTest)
{
	Matrix3<double> m {-4.0, 7.0, 14.8, 6.6, 4.6, -7.0, 9.0, -16.8, 9.0};
	Matrix3<double> r {-8.0, 14.0, 29.6, 13.2, 9.2, -14.0, 18.0, -33.6, 18.0};

	BOOST_CHECK(m.mul(2.0).equals(r));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(DeterminantTest)
{
	Matrix3<double> m {-4.0, 7.0, 4.0, 6.0, 7.0, -2.0, 9.0, -11.0, 9.0};
	Matrix3<double> mm {5.0, 2.0, 3.0, 3.0, 4.0, 6.0, 7.0, 9.0, 4.0};

	BOOST_CHECK(m.det() == -1184.0);
	BOOST_CHECK(m.det() != -1184.00001);
	BOOST_CHECK(mm.det() == -133.0);
	BOOST_CHECK(mm.det() != -132.9999999999);
	BOOST_CHECK(mm.det() != 133.0);
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(TransposeTest)
{
	Matrix3<double> m {1.0, 3.0, 2.0, 2.0, 2.0, 1.0, 3.0, 1.0, 3.0};
	Matrix3<double> mm {1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 2.0, 1.0, 3.0};
	Matrix3<double> mmm {1.0, 2.0, 3.0, 3.0, 2.00001, 1.0, 2.0, 1.0, 3.0};
																	 
	BOOST_CHECK(Matrix3<double>::transpose(m).equals(mm));
	BOOST_CHECK(!Matrix3<double>::transpose(m).equals(mmm));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(InverseTest)
{
	Matrix3<double> m {4.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0};
	Matrix3<double> mm {4.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.000001};
	Matrix3<double> r {2.0, -3.0, 1.0, 0.0, 3.0, -3.0, -2.0, 6.0, 2.0};
	Matrix3<double> id(1.0);

	r.mul(1.0 / 6.0);

	Matrix3<double> xxx = Matrix3<double>::multiply(m, Matrix3<double>::inverse(m));

	BOOST_CHECK(Matrix3<double>::inverse(m).equals(r));
	BOOST_CHECK(xxx.equals(id, 0.000000000000001));
	BOOST_CHECK(!Matrix3<double>::inverse(mm).equals(r));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END()
//----------------------------------------------------------------------------------------------------
