#include <SpelSyltCommonLibrary/Math/Public/Mat3x3.h>

#include <cmath>

#include <cassert>
#include <memory>

//------------------------------------------------------------

CL::CMat3x3::CMat3x3()
	: Matrix()
{
	MakeIdentity();
}

//------------------------------------------------------------

CL::CMat3x3::CMat3x3(const CMat3x3& InOther)
	: Matrix()
{
	operator=(InOther);
}

//------------------------------------------------------------

CL::CMat3x3::CMat3x3(CMat3x3&& InOther) noexcept
	: Matrix()
{
	operator=(InOther);
}

//------------------------------------------------------------

void CL::CMat3x3::MakeIdentity()
{
	/*
	1,0,0
	0,1,0
	0,0,1
	*/

	for (int X = 0; X < 3; ++X)
	{
		for (int Y = 0; Y < 3; ++Y)
		{
			if (X == Y)
			{
				Matrix[X][Y] = 1.f;
			}
			else
			{
				Matrix[X][Y] = 0.f;
			}
		}
	}
}

//------------------------------------------------------------

bool CL::CMat3x3::IsIdentity() const
{
	for (int X = 0; X < 3; ++X)
	{
		for (int Y = 0; Y < 3; ++Y)
		{
			if (X == Y)
			{
				if (Matrix[X][Y] != 1.f)
				{
					return false;
				}
			}
			else
			{
				if (Matrix[X][Y] != 0.f)
				{
					return false;
				}
			}
		}
	}

	return true;
}

//------------------------------------------------------------

void CL::CMat3x3::Transpose()
{
	operator=(GetTransposed());
}

//------------------------------------------------------------

CL::CMat3x3 CL::CMat3x3::GetTransposed() const
{
	CL::CMat3x3 Constructed;

	Constructed.M11() = M11();
	Constructed.M22() = M22();
	Constructed.M33() = M33();

	Constructed.M12() = M21();
	Constructed.M13() = M31();
	Constructed.M23() = M32();

	return std::move(Constructed);
}

//------------------------------------------------------------

void CL::CMat3x3::Invert()
{
	operator=(GetInverse());
}

//------------------------------------------------------------

CL::CMat3x3 CL::CMat3x3::GetInverse() const
{
	CL::CMat3x3 Constructed;

	CL::CMat3x3 RMat = GetTransposed();
	CL::CMat3x3 TMat = *this;
	TMat.M13() = 0.f;
	TMat.M23() = 0.f;

	Constructed = RMat * TMat;

	return std::move(Constructed);
}


//------------------------------------------------------------

void CL::CMat3x3::operator=(CMat3x3&& InRHS) noexcept
{
	memcpy_s(this->Matrix, sizeof(float) * 9, InRHS.Matrix, sizeof(float) * 9);
}

//------------------------------------------------------------

void CL::CMat3x3::operator=(const CMat3x3& InRHS)
{
	for (int X = 0; X < 3; ++X)
	{
		for (int Y = 0; Y < 3; ++Y)
		{
			Matrix[X][Y] = InRHS.Matrix[X][Y];
		}
	}
}

//------------------------------------------------------------

CL::CMat3x3 CL::CMat3x3::operator*(const CMat3x3& InRHS) const
{
	CL::CMat3x3 Constructed;
	
	/*
	|--
	|M11|M21|M31| 
	|---|---|---|
	|M12|M22|M32|
	|---|---|---|
	|M13|M23|M33|
	*/

	//Row 1
	Constructed.M11() = M11() * InRHS.M11() + M21() * InRHS.M12() + M31() * InRHS.M13();
	Constructed.M21() = M11() * InRHS.M21() + M21() * InRHS.M22() + M31() * InRHS.M23();
	Constructed.M31() = M11() * InRHS.M31() + M21() * InRHS.M32() + M31() * InRHS.M33();

	//Row 2
	Constructed.M12() = M12() * InRHS.M11() + M22() * InRHS.M12() + M32() * InRHS.M13();
	Constructed.M22() = M12() * InRHS.M21() + M22() * InRHS.M22() + M32() * InRHS.M23();
	Constructed.M32() = M12() * InRHS.M31() + M22() * InRHS.M32() + M32() * InRHS.M33();

	//Row 3
	Constructed.M13() = M13() * InRHS.M11() + M23() * InRHS.M12() + M33() * InRHS.M13();
	Constructed.M23() = M13() * InRHS.M21() + M23() * InRHS.M22() + M33() * InRHS.M23();
	Constructed.M33() = M13() * InRHS.M31() + M23() * InRHS.M32() + M33() * InRHS.M33();

	return std::move(Constructed);
}

//------------------------------------------------------------

CL::CMat3x3 CL::CMat3x3::operator*(const float InRHS) const
{
	CL::CMat3x3 Constructed;

	for (int X = 0; X < 3; ++X)
	{
		for (int Y = 0; Y < 3; ++Y)
		{
			Constructed.Matrix[X][Y] = Matrix[X][Y] * InRHS;
		}
	}

	return std::move(Constructed);
}

//------------------------------------------------------------

void CL::CMat3x3::operator*=(const CMat3x3& InRHS)
{
	operator=(operator*(InRHS));
}

//------------------------------------------------------------

void CL::CMat3x3::operator*=(const float InRHS)
{
	operator=(operator*(InRHS));
}

//------------------------------------------------------------

//------------------------------------------------------------
//	Static Make Functions									 |
//------------------------------------------------------------

void CL::CMat3x3::MakeXRotation(CMat3x3& OutRotationMatrix, float InRadians)
{
	assert(OutRotationMatrix.IsIdentity() && "A matrix to make rotation from must be identity");

	OutRotationMatrix.M22() = cosf(InRadians);
	OutRotationMatrix.M32() = -sinf(InRadians);
	OutRotationMatrix.M23() = sinf(InRadians);
	OutRotationMatrix.M33() = cosf(InRadians);
}

//------------------------------------------------------------

void CL::CMat3x3::MakeYRotation(CMat3x3& OutRotationMatrix, float InRadians)
{
	assert(OutRotationMatrix.IsIdentity() && "A matrix to make rotation from must be identity");

	OutRotationMatrix.M11() = cosf(InRadians);
	OutRotationMatrix.M31() = sinf(InRadians);
	OutRotationMatrix.M13() = -sinf(InRadians);
	OutRotationMatrix.M33() = cosf(InRadians);
}

//------------------------------------------------------------

void CL::CMat3x3::MakeZRotation(CMat3x3& OutRotationMatrix, float InRadians)
{
	assert(OutRotationMatrix.IsIdentity() && "A matrix to make rotation from must be identity");

	OutRotationMatrix.M11() = cosf(InRadians);
	OutRotationMatrix.M21() = -sinf(InRadians);
	OutRotationMatrix.M12() = sinf(InRadians);
	OutRotationMatrix.M22() = cosf(InRadians);
}

//------------------------------------------------------------

void CL::CMat3x3::MakeXScale(CMat3x3& OutScaleMatrix, float InScale)
{
	assert(OutScaleMatrix.IsIdentity() && "A matrix to make scale from must be identity");
	OutScaleMatrix.M11() = InScale;
}

//------------------------------------------------------------

void CL::CMat3x3::MakeYScale(CMat3x3& OutScaleMatrix, float InScale)
{
	assert(OutScaleMatrix.IsIdentity() && "A matrix to make scale from must be identity");
	OutScaleMatrix.M22() = InScale;
}

//------------------------------------------------------------

void CL::CMat3x3::MakeZScale(CMat3x3& OutScaleMatrix, float InScale)
{
	assert(OutScaleMatrix.IsIdentity() && "A matrix to make scale from must be identity");
	OutScaleMatrix.M33() = InScale;
}

//------------------------------------------------------------