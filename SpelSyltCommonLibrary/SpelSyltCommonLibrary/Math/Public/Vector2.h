#pragma once
#include <cmath>
#include "Math/Public/NumericDefines.h"

//------------------------------------------------------------

namespace CL
{
	template<typename T>
	class CVector2
	{
	public:
		CVector2();
		CVector2(T InX, T InY);
		explicit CVector2(T InXY);
		CVector2(const CVector2& InOther);
		explicit CVector2(CVector2&& InOther);

		float Length() const;
		T Length2() const;

		T Dot(const CVector2& InOther) const;

		CVector2 GetNormalized() const;
		void Normalize();

		//Const Operators
		CVector2 operator+(const CVector2& InRHS) const;
		CVector2 operator-(const CVector2& InRHS) const;
		CVector2 operator-() const;
		CVector2 operator/(const CVector2& InRHS) const;
		CVector2 operator/(const float InRHS) const;
		CVector2 operator*(const CVector2& InRHS) const;
		CVector2 operator*(const float InRHS) const;
		bool operator==(const CVector2& InRHS) const;

		//Modifier Operators
		void operator=(const CVector2& InRHS);
		void operator+=(const CVector2& InRHS);
		void operator-=(const CVector2& InRHS);
		void operator/=(const CVector2& InRHS);
		void operator/=(const float InRHS);
		void operator*=(const CVector2& InRHS);
		void operator*=(const float InRHS);
	
		T X;
		T Y;
	};
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T>::CVector2()
	: X(static_cast<T>(0))
	, Y(static_cast<T>(0))
{
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T>::CVector2(T InXY)
	: X(InXY)
	, Y(InXY)
{
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T>::CVector2(T InX, T InY)
	: X(InX)
	, Y(InY)
{
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T>::CVector2(const CVector2& InOther)
	: X(InOther.X)
	, Y(InOther.Y)
{
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T>::CVector2(CVector2&& InOther)
	: X(std::move(InOther.X))
	, Y(std::move(InOther.Y))
{
}

//------------------------------------------------------------

template<typename T>
inline float CL::CVector2<T>::Length() const
{
	return sqrtf(static_cast<float>(Length2()));
}

//------------------------------------------------------------

template<typename T>
inline T CL::CVector2<T>::Length2() const
{
	return ( X * X ) + ( Y * Y );
}

//------------------------------------------------------------

template<typename T>
inline T CL::CVector2<T>::Dot(const CVector2& InOther) const
{
	return (X * InOther.X) + (Y * InOther.Y);
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T> CL::CVector2<T>::GetNormalized() const
{
	return operator/(Length());
}

//------------------------------------------------------------

template<typename T>
inline void CL::CVector2<T>::Normalize()
{
	operator/=(Length());
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T> CL::CVector2<T>::operator+(const CVector2& InRHS) const
{
	return CVector2<T>(X + InRHS.X, Y + InRHS.Y);
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T> CL::CVector2<T>::operator-(const CVector2& InRHS) const
{
	return CVector2(X - InRHS.X, Y - InRHS.Y);
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T> CL::CVector2<T>::operator-() const
{
	return CVector2(-X, -Y);
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T> CL::CVector2<T>::operator/(const CVector2& InRHS) const
{
	return CVector2(X / InRHS.X, Y / InRHS.Y);
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T> CL::CVector2<T>::operator/(const float InRHS) const
{
	return CVector2(X / InRHS, Y / InRHS);
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T> CL::CVector2<T>::operator*(const CVector2& InRHS) const
{
	return CVector2(X * InRHS.X, Y * InRHS.Y);
}

//------------------------------------------------------------

template<typename T>
inline CL::CVector2<T> CL::CVector2<T>::operator*(const float InRHS) const
{
	return CVector2(X * InRHS, Y * InRHS);
}

//------------------------------------------------------------

template<typename T>
inline bool CL::CVector2<T>::operator==(const CVector2& InRHS) const
{
	if constexpr (std::is_floating_point_v<T>)
	{
		const bool XMatch = (X <= InRHS.X + FLOATING_POINT_ACCEPTANCE) || (X >= InRHS.X - FLOATING_POINT_ACCEPTANCE);
		const bool YMatch = (Y <= InRHS.Y + FLOATING_POINT_ACCEPTANCE) || (Y >= InRHS.Y - FLOATING_POINT_ACCEPTANCE);
		return XMatch && YMatch;
	}

	return (X == InRHS.X) && (Y == InRHS.Y);
}

//------------------------------------------------------------

template<typename T>
inline void CL::CVector2<T>::operator=(const CVector2& InRHS)
{
	X = InRHS.X;
	Y = InRHS.Y;
}

//------------------------------------------------------------

template<typename T>
inline void CL::CVector2<T>::operator+=(const CVector2& InRHS)
{
	operator=(operator+(InRHS));
}

//------------------------------------------------------------

template<typename T>
inline void CL::CVector2<T>::operator-=(const CVector2& InRHS)
{
	operator=(operator-(InRHS));
}

//------------------------------------------------------------

template<typename T>
inline void CL::CVector2<T>::operator/=(const CVector2& InRHS)
{
	operator=(operator/(InRHS));
}

//------------------------------------------------------------

template<typename T>
inline void CL::CVector2<T>::operator/=(const float InRHS)
{
	operator=(operator/(InRHS));
}

//------------------------------------------------------------

template<typename T>
inline void CL::CVector2<T>::operator*=(const CVector2& InRHS)
{
	operator=(operator*(InRHS));
}

//------------------------------------------------------------

template<typename T>
inline void CL::CVector2<T>::operator*=(const float InRHS)
{
	operator=(operator*(InRHS));
}

//------------------------------------------------------------