#include <utility>
#include <cmath>

#include <SpelSyltCommonLibrary/Graphics/Public/Transformable2D.h>
#include <SpelSyltCommonLibrary/Math/Public/Conversions.h>


//------------------------------------------------------------

CL::CTransformable2D::CTransformable2D()
	: Matrix()
	, Position()
	, ScaleVec(1.f, 1.f)
	, Rotation(0.f)
{
}

//------------------------------------------------------------

CL::CTransformable2D::CTransformable2D(const CTransformable2D& InOther)
	: Matrix(InOther.Matrix)
	, Position()
	, ScaleVec(1.f, 1.f)
	, Rotation(0.f)
{
}

//------------------------------------------------------------

CL::CTransformable2D::CTransformable2D(CTransformable2D&& InOther) noexcept
	: Matrix(std::move(InOther.Matrix))
	, Position()
	, ScaleVec(1.f, 1.f)
	, Rotation(0.f)
{
}

//------------------------------------------------------------

CL::CMat3x3& CL::CTransformable2D::GetMatrix()
{
	return Matrix;
}

//------------------------------------------------------------

void CL::CTransformable2D::TransformPoint(CL::CVector2f& OutPointToTransform)
{
	OutPointToTransform *= Matrix;
}

//------------------------------------------------------------

void CL::CTransformable2D::Move(float InX, float InY)
{
	Matrix.X() += InX;
	Matrix.Y() += InY;
}

//------------------------------------------------------------

void CL::CTransformable2D::Move(const CVector2f& InOffset)
{
	Move(InOffset.X, InOffset.Y);
}

//------------------------------------------------------------

void CL::CTransformable2D::SetPosition(float InX, float InY)
{
	Matrix.X() = InX;
	Matrix.Y() = InY;
}

//------------------------------------------------------------

void CL::CTransformable2D::SetPosition(const CVector2f& InPosition)
{
	SetPosition(InPosition.X, InPosition.Y);
}

//------------------------------------------------------------

CL::CVector2f CL::CTransformable2D::GetPosition() const
{
	return std::move(CVector2f(Matrix.X(), Matrix.Y()));
}

//------------------------------------------------------------

void CL::CTransformable2D::Rotate(float InAngle, bool IsRadians)
{
	float AngleRad = IsRadians ? InAngle : Conv::ToRadians(InAngle);

	Rotation += AngleRad;

	CMat3x3 ZRotMat;
	CMat3x3::MakeZRotation(ZRotMat, AngleRad);

	Matrix *= ZRotMat;
}

//------------------------------------------------------------

void CL::CTransformable2D::SetRotation(float InAngle, bool IsRadians)
{
	CMat3x3 ZRotMat;
	CMat3x3::MakeZRotation(ZRotMat, -Rotation);
	Matrix *= ZRotMat;

	Rotation = 0.f;
	Rotate(InAngle, IsRadians);
}

//------------------------------------------------------------

float CL::CTransformable2D::GetRotation() const
{
	return Rotation;
}

//------------------------------------------------------------

void CL::CTransformable2D::Scale(float InOffset)
{
	Scale(InOffset, InOffset);
}

//------------------------------------------------------------

void CL::CTransformable2D::Scale(float InOffsetX, float InOffsetY)
{
	CMat3x3 ScaleMatX;
	CMat3x3::MakeXScale(ScaleMatX, InOffsetX);
	CMat3x3 ScaleMatY;
	CMat3x3::MakeYScale(ScaleMatY, InOffsetY);

	Matrix *= (ScaleMatX * ScaleMatY);
	ScaleVec += CVector2f(InOffsetX, InOffsetY);
}

//------------------------------------------------------------

void CL::CTransformable2D::Scale(const CL::CVector2f& InOffset)
{
	Scale(InOffset.X, InOffset.Y);
}

//------------------------------------------------------------

void CL::CTransformable2D::SetScale(float InScale)
{
	SetScale(InScale, InScale);
}

//------------------------------------------------------------

void CL::CTransformable2D::SetScale(float InScaleX, float InScaleY)
{
	const float OriginalScale = 1.f;
	const float ScaleOffsetX = OriginalScale - ScaleVec.X;
	const float ScaleOffsetY = OriginalScale - ScaleVec.Y;
	Scale(ScaleVec.X + ScaleOffsetX, ScaleVec.Y + ScaleOffsetY);

	CMat3x3 ScaleMatX;
	CMat3x3::MakeXScale(ScaleMatX, InScaleX);

	CMat3x3 ScaleMatY;
	CMat3x3::MakeYScale(ScaleMatY, InScaleY);

	Matrix *= (ScaleMatX * ScaleMatY);

	ScaleVec.X = InScaleX;
	ScaleVec.Y = InScaleY;
}

//------------------------------------------------------------

void CL::CTransformable2D::SetScale(const CVector2f& InScale)
{
	SetScale(InScale.X, InScale.Y);
}

//------------------------------------------------------------

CL::CVector2f CL::CTransformable2D::GetScale() const
{
	return std::move(ScaleVec);
}

//------------------------------------------------------------