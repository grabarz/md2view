//----------------------------------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>

#include <Float.hpp>
#include <Matrix3.hpp>
#include <Quaternion.hpp>
#include <Vector4.hpp>
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(MathQuaternionTests)
//----------------------------------------------------------------------------------------------------

using namespace MD2View;
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Constructor_whenNoParametersPassed_constructsZeroQuaternion)
{
	Quaternion<float> q;

	BOOST_CHECK(q.equals({0.0, 0.0, 0.0, 0.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Constructor_whenParametersPassed_constructsQuaternion)
{
	Quaternion<float> q {1.0, 2.0, 3.0, 4.0};

	BOOST_CHECK(q.equals({1.0, 2.0, 3.0, 4.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Constructor_whenVectorPassed_constructsQuaternion)
{
	Vector3<float> v {1.0, 2.0, 3.0};
	Quaternion<float> q {v, 0.0};

	BOOST_CHECK(q.equals({0.0, 0.0, 0.0, 1.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(AssignOperator_whenQuaternionPassed_copiesValue)
{
	Quaternion<float> q {1.0, 2.0, 3.0, 4.0};
	Quaternion<float> qq;

	qq = q;

	BOOST_CHECK(qq.equals({1.0, 2.0, 3.0, 4.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(AssignOperator_whenVectorPassed_copiesValue)
{
	Vector4<float> v {1.0, 2.0, 3.0, 4.0};
	Quaternion<float> q;

	q = v;

	BOOST_CHECK(q.equals({1.0, 2.0, 3.0, 4.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(PointerGet_whenNoArgumentsPassed_returnsConstPointer)
{
	const Quaternion<float> q {1.0, 2.0, 3.0, 4.0};

	const float* f = q.get();

	BOOST_CHECK(q.equals({f[0], f[1], f[2], f[3]}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(PointerGet_whenNoArgumentsPassed_returnsPointer)
{
	Quaternion<float> q {1.0, 2.0, 3.0, 4.0};

	float* f = q.get();

	BOOST_CHECK(q.equals({f[0], f[1], f[2], f[3]}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(IndexOperator_whenIndexPassed_returnsReferenceElement)
{
	Quaternion<float> q {1.0, 2.0, 3.0, 4.0};

	q[0] = 2.0;
	q[1] = 5.0;
	q[2] = 0.0;
	q[3] = 8.0;

	BOOST_CHECK(q.equals({2.0, 5.0, 0.0, 8.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(IndexOperator_whenIndexPassed_returnsElement)
{
	const Quaternion<float> q {1.0, 2.0, 3.0, 4.0};

	BOOST_CHECK(q.equals({q[0], q[1], q[2], q[3]}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Increment_whenQuaternionPassed_increasesQuaternion)
{
	Quaternion<float> q {1.0, 2.0, 3.0, 4.0};
	Quaternion<float> qq {1.0, 2.0, 3.0, 4.0};

	q.inc(qq);

	BOOST_CHECK(q.equals({2.0, 4.0, 6.0, 8.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(IncrementWithScale_whenQuaternionPassed_increasesWithScaleQuaternion)
{
	Quaternion<float> q {1.0, 2.0, 3.0, 4.0};
	Quaternion<float> qq {1.0, 2.0, 3.0, 4.0};

	q.inc(qq, 2.0);

	BOOST_CHECK(q.equals({3.0, 6.0, 9.0, 12.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Decrement_whenQuaternionPassed_decrementsQuaternion)
{
	Quaternion<float> q {1.0, 2.0, 3.0, 4.0};
	Quaternion<float> qq {1.0, 2.0, 3.0, 4.0};

	q.dec(qq);

	BOOST_CHECK(q.equals({0.0, 0.0, 0.0, 0.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Multiply_whenScalarPassed_multipliesQuaternion)
{
	Quaternion<float> q {1.0, 2.0, 3.0, 4.0};

	q.mul(2.0);

	BOOST_CHECK(q.equals({2.0, 4.0, 6.0, 8.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Negate_whenNoArgumentsPassed_negatesQuaternion)
{
	Quaternion<float> q {1.0, 2.0, 3.0, 4.0};

	q.neg();

	BOOST_CHECK(q.equals({-1.0, -2.0, -3.0, -4.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Lenght_whenNoArgumentsPassed_returnsLenghtOfQuaternion)
{
	Quaternion<float> q {1.0, 1.0, 1.0, 1.0};

	BOOST_CHECK(FloatEqual<float>(q.len(), 2.0));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Lenght_whenNoArgumentsPassed_returnsLenght2OfQuaternion)
{
	Quaternion<float> q {1.0, 1.0, 1.0, 1.0};

	BOOST_CHECK(FloatEqual<float>(q.len2(), 4.0));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Lenght_whenNoArgumentsPassed_setsLenghtOfQuaternion)
{
	Quaternion<float> q {1.0, 1.0, 2.0, 3.0};

	q.len(2.0);

	BOOST_CHECK(FloatEqual<float>(q.len(), 2.0));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Normalize_whenNoArgumentsPassed_normalizesQuaternion)
{
	Quaternion<float> q {1.0, 1.0, 2.0, 3.0};

	q.normalize();

	BOOST_CHECK(FloatEqual<float>(q.len(), 1.0));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Multiply_whenTwoQuaternionPassed_multipliesQuaternions)
{
	Quaternion<float> q {2.0, 3.0, 4.0, 1.0};
	Quaternion<float> p {1.0, 5.0, 6.0, 2.0};
	Quaternion<float> qq = Quaternion<float>::multiply(q, p);

	BOOST_CHECK(qq.equals({3.0, 3.0, 21.0, -39.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(Multiply_whenQuaternionAndVectorPassed_multipliesQuaternionAndVector)
{
	Quaternion<float> q {2.0, 3.0, 4.0, 1.0};
	Vector3<float> p {1.0, 5.0, 6.0};
	Vector3<float> qq = q.mul(p);

	BOOST_CHECK(qq.equals({140.0, 122.0, 146.0}));
}
//----------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END()
//----------------------------------------------------------------------------------------------------
