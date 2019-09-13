#include <SpelSyltCommonLibrary/Math/Public/Mat4x4.h>

#include <cmath>

#include <cassert>
#include <memory>

//------------------------------------------------------------

CL::CMat4x4::CMat4x4()
	: Matrix()
{
	MakeIdentity();
}

//------------------------------------------------------------

CL::CMat4x4::CMat4x4(const CMat4x4& InOther)
	: Matrix()
{
	operator=(InOther);
}

//------------------------------------------------------------

CL::CMat4x4::CMat4x4(CMat4x4&& InOther) noexcept
	: Matrix()
{
	operator=(InOther);
}

//------------------------------------------------------------

void CL::CMat4x4::MakeIdentity()
{
	/*
	1,0,0,0
	0,1,0,0
	0,0,1,0
	0,0,0,1
	*/

	for (int X = 0; X < 4; ++X)
	{
		for (int Y = 0; Y < 4; ++Y)
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

bool CL::CMat4x4::IsIdentity() const
{
	for (int X = 0; X < 4; ++X)
	{
		for (int Y = 0; Y < 4; ++Y)
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

void CL::CMat4x4::Transpose()
{
	operator=(GetTransposed());
}

//------------------------------------------------------------

CL::CMat4x4 CL::CMat4x4::GetTransposed() const 
{
	CL::CMat4x4 Constructed;

	Constructed.M11() = M11();
	Constructed.M12() = M21();
	Constructed.M13() = M31();
	Constructed.M14() = M41();

	Constructed.M21() = M12();
	Constructed.M22() = M22();
	Constructed.M23() = M32();
	Constructed.M24() = M42();

	Constructed.M31() = M13();
	Constructed.M32() = M23();
	Constructed.M33() = M33();
	Constructed.M34() = M43();

	Constructed.M41() = M14();
	Constructed.M42() = M24();
	Constructed.M43() = M34();
	Constructed.M44() = M44();

	return std::move(Constructed);
}

//------------------------------------------------------------

void CL::CMat4x4::Invert()
{
	operator=(GetInverse());
}

//------------------------------------------------------------

CL::CMat4x4 CL::CMat4x4::GetInverse() const
{
	//This might be incorrect
	CL::CMat4x4 Constructed;

	CL::CMat4x4 RMat = GetTransposed();
	CL::CMat4x4 TMat = *this;
	TMat.M14() = 0.f;
	TMat.M24() = 0.f;
	TMat.M34() = 0.f;

	Constructed = RMat * TMat;

	return std::move(Constructed);
}

//------------------------------------------------------------

void CL::CMat4x4::operator=(CMat4x4&& InRHS) noexcept
{
	memcpy_s(this->Matrix, sizeof(float) * 16, InRHS.Matrix, sizeof(float) * 16);
}

//------------------------------------------------------------

void CL::CMat4x4::operator=(const CMat4x4& InRHS)
{
	for (int X = 0; X < 4; ++X)
	{
		for (int Y = 0; Y < 4; ++Y)
		{
			Matrix[X][Y] = InRHS.Matrix[X][Y];
		}
	}
}

//------------------------------------------------------------

CL::CMat4x4 CL::CMat4x4::operator*(const CMat4x4& InRHS) const
{
	CL::CMat4x4 Constructed;

	//Row 1
	Constructed.M11() = M11() * InRHS.M11() + M21() * InRHS.M12() + M31() * InRHS.M13() + M41() * InRHS.M14();
	Constructed.M21() = M11() * InRHS.M21() + M21() * InRHS.M22() + M31() * InRHS.M23() + M41() * InRHS.M24();
	Constructed.M31() = M11() * InRHS.M31() + M21() * InRHS.M32() + M31() * InRHS.M33() + M41() * InRHS.M34();
	Constructed.M41() = M11() * InRHS.M41() + M21() * InRHS.M42() + M31() * InRHS.M43() + M41() * InRHS.M44();

	//Row 2
	Constructed.M12() = M12() * InRHS.M11() + M22() * InRHS.M12() + M32() * InRHS.M13() + M42() * InRHS.M14();
	Constructed.M22() = M12() * InRHS.M21() + M22() * InRHS.M22() + M32() * InRHS.M23() + M42() * InRHS.M24();
	Constructed.M32() = M12() * InRHS.M31() + M22() * InRHS.M32() + M32() * InRHS.M33() + M42() * InRHS.M34();
	Constructed.M42() = M12() * InRHS.M41() + M22() * InRHS.M42() + M32() * InRHS.M43() + M42() * InRHS.M44();

	//Row 3
	Constructed.M13() = M13() * InRHS.M11() + M23() * InRHS.M12() + M33() * InRHS.M13() + M43() * InRHS.M14();
	Constructed.M23() = M13() * InRHS.M21() + M23() * InRHS.M22() + M33() * InRHS.M23() + M43() * InRHS.M24();
	Constructed.M33() = M13() * InRHS.M31() + M23() * InRHS.M32() + M33() * InRHS.M33() + M43() * InRHS.M34();
	Constructed.M43() = M13() * InRHS.M41() + M23() * InRHS.M42() + M33() * InRHS.M43() + M43() * InRHS.M44();

	//Row 4
	Constructed.M14() = M14() * InRHS.M11() + M24() * InRHS.M12() + M34() * InRHS.M13() + M44() * InRHS.M14();
	Constructed.M24() = M14() * InRHS.M21() + M24() * InRHS.M22() + M34() * InRHS.M23() + M44() * InRHS.M24();
	Constructed.M34() = M14() * InRHS.M31() + M24() * InRHS.M32() + M34() * InRHS.M33() + M44() * InRHS.M34();
	Constructed.M44() = M14() * InRHS.M41() + M24() * InRHS.M42() + M34() * InRHS.M43() + M44() * InRHS.M44();

	return std::move(Constructed);
}

//------------------------------------------------------------

CL::CMat4x4 CL::CMat4x4::operator*(const float InRHS) const
{
	CL::CMat4x4 Constructed;

	for (int X = 0; X < 4; ++X)
	{
		for (int Y = 0; Y < 4; ++Y)
		{
			Constructed.Matrix[X][Y] = Matrix[X][Y] * InRHS;
		}
	}

	return std::move(Constructed);
}

//------------------------------------------------------------

void CL::CMat4x4::operator*=(const CMat4x4& InRHS)
{
	operator=(operator*(InRHS));
}

//------------------------------------------------------------

void CL::CMat4x4::operator*=(const float InRHS)
{
	operator=(operator*(InRHS));
}

//------------------------------------------------------------

//------------------------------------------------------------
//	Static Make Functions									 |
//------------------------------------------------------------

void CL::CMat4x4::MakeXRotation(CMat4x4& OutRotationMatrix, float InRadians)
{
	assert(OutRotationMatrix.IsIdentity() && "A matrix to make rotation from must be identity");

	OutRotationMatrix.M22() = cosf(InRadians);
	OutRotationMatrix.M32() = -sinf(InRadians);
	OutRotationMatrix.M23() = sinf(InRadians);
	OutRotationMatrix.M33() = cosf(InRadians);
}

//------------------------------------------------------------

void CL::CMat4x4::MakeYRotation(CMat4x4& OutRotationMatrix, float InRadians)
{
	assert(OutRotationMatrix.IsIdentity() && "A matrix to make rotation from must be identity");

	OutRotationMatrix.M11() = cosf(InRadians);
	OutRotationMatrix.M31() = sinf(InRadians);
	OutRotationMatrix.M13() = -sinf(InRadians);
	OutRotationMatrix.M33() = cosf(InRadians);
}

//------------------------------------------------------------
void CL::CMat4x4::MakeZRotation(CMat4x4& OutRotationMatrix, float InRadians)
{
	assert(OutRotationMatrix.IsIdentity() && "A matrix to make rotation from must be identity");

	OutRotationMatrix.M11() = cosf(InRadians);
	OutRotationMatrix.M21() = -sinf(InRadians);
	OutRotationMatrix.M12() = sinf(InRadians);
	OutRotationMatrix.M22() = cosf(InRadians);
}

//------------------------------------------------------------

void CL::CMat4x4::MakeXScale(CMat4x4& OutScaleMatrix, float InScale)
{
	assert(OutScaleMatrix.IsIdentity() && "A matrix to make scale from must be identity");
	OutScaleMatrix.M11() = InScale;
}

//------------------------------------------------------------

void CL::CMat4x4::MakeYScale(CMat4x4& OutScaleMatrix, float InScale)
{
	assert(OutScaleMatrix.IsIdentity() && "A matrix to make scale from must be identity");
	OutScaleMatrix.M22() = InScale;
}

//------------------------------------------------------------

void CL::CMat4x4::MakeZScale(CMat4x4& OutScaleMatrix, float InScale)
{
	assert(OutScaleMatrix.IsIdentity() && "A matrix to make scale from must be identity");
	OutScaleMatrix.M33() = InScale;
}

//------------------------------------------------------------

