#include "pch.h"
#include "CppUnitTest.h"

#include <../SpelSyltCommonLibrary/Math/Public/Vector2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VECTORS_ARE_EQUAL(Vec1, Vec2) Assert::AreEqual(Vec1.X, Vec2.X, L"Expected Vectors to match")

namespace SSCLMathTests
{
	TEST_CLASS(SSCLVectorTests)
	{
	public:
		TEST_METHOD(DefaultContructedVectorXYIsZero)
		{
			CL::CVector2<int> Vec2;

			Assert::AreEqual(0, Vec2.X, L"Expect Vec2 x to be zero");
			Assert::AreEqual(0, Vec2.Y, L"Expect Vec2 y to be zero");
		}

		TEST_METHOD(ValueConstructedVectorXYMatchesConstrucVals)
		{
			CL::CVector2<int> Vec2(1,2);

			Assert::AreEqual(1, Vec2.X, L"Expect Vec2 x to match construct val");
			Assert::AreEqual(2, Vec2.Y, L"Expect Vec2 y to match construct val");
		}

		TEST_METHOD(SingleValueConstructedVectorXYMatchesConstrucVal)
		{
			CL::CVector2<int> Vec2(1);

			Assert::AreEqual(1, Vec2.X, L"Expect Vec2 x to match construct val");
			Assert::AreEqual(1, Vec2.Y, L"Expect Vec2 y to match construct val");
		}

		TEST_METHOD(CopyConstrucetdVectorMatchesConstructVec)
		{
			CL::CVector2<int> Vec2(CL::CVector2<int>(5, 10));

			Assert::AreEqual(5, Vec2.X, L"Expect Vec2 x to match construct val");
			Assert::AreEqual(10, Vec2.Y, L"Expect Vec2 y to match construct val");
		}

		TEST_METHOD(MoveConstructedVectorMatchesConstructVec)
		{
			CL::CVector2<int> MoveVec(1, 2);
			CL::CVector2<int> Vec2(std::move(MoveVec));

			Assert::AreEqual(1, Vec2.X, L"Expect Vec2 x to match construct val");
			Assert::AreEqual(2, Vec2.Y, L"Expect Vec2 y to match construct val");
		}

		TEST_METHOD(Length2OfVectorMatchesPythagorianVal)
		{
			const int X = 2;
			const int Y = 4;
			const int X2 = X * X;
			const int Y2 = Y * Y;
			const int ExpectedLen2 = X2 + Y2;

			CL::CVector2<int> Vec(X, Y);
			const int Len2 = Vec.Length2();

			Assert::AreEqual(ExpectedLen2, Len2);
		}

		TEST_METHOD(Vec1DotProductOfVec2ReturnProjectedLen)
		{
			const int ExpectedDot = 4;
			CL::CVector2<int> Vec1(2, 2);
			CL::CVector2<int> Vec2(2, 0);

			const int Dot = Vec1.Dot(Vec2);

			Assert::AreEqual(Dot, ExpectedDot);
		}

		TEST_METHOD(Vec1SameAsVec2ExpectedToReturnTrueOnEqualityOperation)
		{
			CL::CVector2<float> Vec1(3.f, 5.f);
			CL::CVector2<float> Vec2(3.f, 5.f);

			Assert::IsTrue(Vec1 == Vec2);
		}

		//TODO: Operators are mainly tested but we need clean tests for them!
	};
}