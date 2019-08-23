#pragma once
#include <SpelSyltCommonLibrary/Math/Public/Mat3x3.h>
#include <SpelSyltCommonLibrary/Math/Public/Vector2.h>

namespace CL
{
	class CTransformable2D
	{
	public:
		CTransformable2D();
		CTransformable2D(const CTransformable2D& InOther);
		CTransformable2D(CTransformable2D&& InOther) noexcept;

		CMat3x3& GetMatrix();

		void TransformPoint(CL::CVector2f& OutPointToTransform);

		void Move(float InX, float InY);
		void Move(const CVector2f& InOffset);
		void SetPosition(float InX, float InY);
		void SetPosition(const CVector2f& InPosition);
		CVector2f GetPosition() const;

		void Rotate(float InAngle, bool IsRadians = true);
		void SetRotation(float InAngle, bool IsRadians = true);
		float GetRotation() const;

		void Scale(float InOffset);
		void Scale(float InOffsetX, float InOffsetY);
		void Scale(const CVector2f& InOffset);

		void SetScale(float InScale);
		void SetScale(float InScaleX, float InScaleY);
		void SetScale(const CVector2f& InScale);
		CVector2f GetScale() const;

		void SetOrigin(const CVector2f& InOrigin);
		void SetOrigin(float InOriginX, float InOriginY);
		CVector2f GetOrigin() const;
	private:
		CMat3x3 Matrix;

		CVector2f Position;
		CVector2f ScaleVec;
		CVector2f Origin;
		float Rotation;

	};
}
