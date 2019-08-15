#include "pch.h"
#include "CppUnitTest.h"

#include "../SpelSyltCommonLibrary/Container/Public/Array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SSCLContainerTests
{
	TEST_CLASS(SSCLArrayTests)
	{
	public:
		TEST_METHOD(DoesRangeBasedForWork)
		{
			struct STest
			{
				STest()
					: z(0)
					, w(0)
				{
				}

				STest(int x, int y)
					: z(x)
					, w(y)
				{
				}

			private:
				int z;
				int w;
			};

			CL::TArray<STest> Array(20);
			Array.EmplaceBack(1, 2);
			Array.EmplaceBack(4, 5);



		}
	};
}