#pragma once

#include "Math/Public/NumericDefines.h"

namespace CL
{
	namespace Conv
	{
		float ToDegrees(float InRad)
		{
			return InRad * (180.f / PI);
		}

		float ToRadians(float InDeg)
		{
			return InDeg * (PI / 180.f);
		}
	}
}