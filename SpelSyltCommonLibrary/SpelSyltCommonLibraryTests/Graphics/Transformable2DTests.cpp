#include "pch.h"
#include "CppUnitTest.h"

#include "CustomAssertions.h"

#include "../SpelSyltCommonLibrary/Graphics/Public/Transformable2D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SSCLGFXTests
{
	TEST_CLASS(SSCLVector2Tests)
	{
	public:
		TEST_METHOD(DefaultConstructedTransformable2DIsAtOriginWithScaleOneAndRotationZero)
		{
			CL::CTransformable2D Transformable;

			Assert::AreEqual(Transformable.GetRotation(), 0.f, L"Expect rotation to be zero");
			Assert::IsTrue(CL::CVector2f(0.f, 0.f) == Transformable.GetPosition(), L"Expect transformable to be in origin");
			Assert::IsTrue(CL::CVector2f(1.f, 1.f) == Transformable.GetScale(), L"Expect scale to be one");
		}

		TEST_METHOD(TransformableMovedByOneInEachDirIsAtPosition11)
		{
			CL::CTransformable2D Transformable;

			Transformable.Move(1.f, 1.f);
			Assert::IsTrue(CL::CVector2f(1.f, 1.f) == Transformable.GetPosition(), L"Expect position to now be one");
		}

		TEST_METHOD(TransformingPointAtCoordinateWithTransformablePutsPointInCorrectSpace)
		{
			CL::CTransformable2D Transformable;
			Transformable.Move(1.f, 1.f);

			CL::CVector2f Point(1.f, 1.f);
			Transformable.TransformPoint(Point);

			Assert::IsTrue(CL::CVector2f(2.f, 2.f) == Point, L"Expect point to now be in x2 y2");
		}
	};
}