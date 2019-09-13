#pragma once

namespace CL
{
	class CMat4x4
	{
	public:
		CMat4x4();
		CMat4x4(const CMat4x4& InOther);
		CMat4x4(CMat4x4&& InOther) noexcept;

		void MakeIdentity();
		bool IsIdentity() const;

		void Transpose();
		CMat4x4 GetTransposed() const;

		void Invert();
		CMat4x4 GetInverse() const;

		static void MakeXScale(CMat4x4& OutScaleMatrix, float InRadians);
		static void MakeYScale(CMat4x4& OutScaleMatrix, float InRadians);
		static void MakeZScale(CMat4x4& OutScaleMatrix, float InRadians);

		static void MakeXRotation(CMat4x4& OutRotationMatrix, float InRadians);
		static void MakeYRotation(CMat4x4& OutRotationMatrix, float InRadians);
		static void MakeZRotation(CMat4x4& OutRotationMatrix, float InRadians);

		CMat4x4 operator*(const CMat4x4& InRHS) const;
		CMat4x4 operator*(const float InRHS) const;

		void operator=(CMat4x4&& InRHS) noexcept;
		void operator=(const CMat4x4& InRHS);
		void operator*=(const CMat4x4& InRHS);
		void operator*=(const float InRHS);

		inline float& M11() { return Matrix[0][0]; };
		inline float& M21() { return Matrix[0][1]; };
		inline float& M31() { return Matrix[0][2]; };
		inline float& M41() { return Matrix[0][3]; };
		inline float& M12() { return Matrix[1][0]; };
		inline float& M22() { return Matrix[1][1]; };
		inline float& M32() { return Matrix[1][2]; };
		inline float& M42() { return Matrix[1][3]; };
		inline float& M13() { return Matrix[2][0]; };
		inline float& M23() { return Matrix[2][1]; };
		inline float& M33() { return Matrix[2][2]; };
		inline float& M43() { return Matrix[2][3]; };
		inline float& M14() { return Matrix[3][0]; };
		inline float& M24() { return Matrix[3][1]; };
		inline float& M34() { return Matrix[3][2]; };
		inline float& M44() { return Matrix[3][3]; };
		
		inline float M11() const { return Matrix[0][0]; };
		inline float M21() const { return Matrix[0][1]; };
		inline float M31() const { return Matrix[0][2]; };
		inline float M41() const { return Matrix[0][3]; };
		inline float M12() const { return Matrix[1][0]; };
		inline float M22() const { return Matrix[1][1]; };
		inline float M32() const { return Matrix[1][2]; };
		inline float M42() const { return Matrix[1][3]; };
		inline float M13() const { return Matrix[2][0]; };
		inline float M23() const { return Matrix[2][1]; };
		inline float M33() const { return Matrix[2][2]; };
		inline float M43() const { return Matrix[2][3]; };
		inline float M14() const { return Matrix[3][0]; };
		inline float M24() const { return Matrix[3][1]; };
		inline float M34() const { return Matrix[3][2]; };
		inline float M44() const { return Matrix[3][3]; };

	private:
		float Matrix[4][4];
	};
}