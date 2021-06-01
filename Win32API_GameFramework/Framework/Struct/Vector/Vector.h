#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Math/Math.h"



struct FVector :
	public CObject
{
public :
	float X;
	float Y;

public :
	FVector();
	FVector(float x, float y);

public :
	// v1 과 v2 의 거리를 반환하는 함수
	static float Distance(const FVector& v1, const FVector& v2);

	// from 에서 to 로의 방향을 반환합니다.
	static FVector Direction(const FVector& from, const FVector& to);

public :
	// Vector 의 길이를 반환합니다.
	float Length() const;

	// X*X + Y*Y 의 값을 반환합니다.
	FORCEINLINE float SizeSquared() const
	{ return X * X + Y * Y; }

	// 이 벡터를 단위벡터로 만듭니다.
	void Normalize();

	// 이 벡터를 이용하여 단위벡터를 만들어 반환합니다.
	FVector Normalized() const;


	// 이 벡터가 단위벡터임을 확인합니다.
	bool IsUnit(float errorTolerance = (1.e-8f)) const;

	// 해당 위치가 창 내부에 위치하는지 확인함
	bool InWnd() const;


	// 해당 위치가 창 내부에 위치하는지 확인함
	// cameraPosition : 연산시킬 카메라 위치
	bool InWnd(const FVector& cameraPosition, FVector padding = FVector(0.0f, 0.0f)) const;

	virtual tstring ToString() const override;


public :
	FORCEINLINE static FVector ZeroVector()
	{ return FVector(0.0f, 0.0f); }
	
	FORCEINLINE static FVector OneVector()
	{ return FVector(1.0f, 1.0f); }

	FORCEINLINE static FVector UpVector()
	{ return FVector(0.0f, -1.0f); }
	
	FORCEINLINE static FVector DownVector()
	{ return FVector(0.0f, 1.0f); }
	
	FORCEINLINE static FVector LeftVector()
	{ return FVector(-1.0f, 0.0f); }
	
	FORCEINLINE static FVector RightVector()
	{ return FVector(1.0f, 0.0f); }

	FORCEINLINE static FVector ScreenCenter()
	{ return FVector(WND_WIDTH * 0.5f, WND_HEIGHT * 0.5f); }

	FORCEINLINE static FVector ScreenSize()
	{
		return FVector(WND_WIDTH, WND_HEIGHT);
	}

	static FVector VRand(float _min = 0.0f, float _max = 1.0f);


public :
	// 산술 연산자 오버로딩
	FORCEINLINE FVector operator+(const FVector& value) const
	{ return FVector(X + value.X, Y + value.Y); }
	FORCEINLINE FVector operator-(const FVector& value) const
	{ return FVector(X - value.X, Y - value.Y); }
	FORCEINLINE FVector operator+(const float& value) const
	{ return FVector(X + value, Y + value); }
	FORCEINLINE FVector operator-(const float& value) const
	{ return FVector(X - value, Y - value); }
	FORCEINLINE FVector operator*(const float& value) const
	{ return FVector(X * value, Y * value); }
	FORCEINLINE FVector operator/(const float& value) const
	{ return FVector(X / value, Y / value); }
	
	FORCEINLINE FVector& operator+=(const FVector& point)
	{ return (*this = FVector(X + point.X, Y + point.Y) ); }
	FORCEINLINE FVector& operator-=(const FVector& point)
	{ return (*this = FVector(X - point.X, Y - point.Y) ); }
	FORCEINLINE FVector& operator+=(const float& value)
	{ return (*this = FVector(X + value, Y + value) ); }
	FORCEINLINE FVector& operator-=(const float& value)
	{ return (*this = FVector(X - value, Y - value) ); }
	FORCEINLINE FVector& operator*=(const float& value)
	{ return (*this = FVector(X * value, Y * value) ); }
	FORCEINLINE FVector& operator/=(const float& value)
	{ return (*this = FVector(X / value, Y / value) ); }

	// 전위 연산자
	FORCEINLINE const FVector operator++()
	{ return ((*this) = FVector(X + 1, Y + 1)); }
	FORCEINLINE const FVector operator--()
	{ return ((*this) = FVector(X - 1, Y - 1)); }
	
	// 후위 연산자
	FORCEINLINE const FVector operator++(int)
	{
		FVector temp = (*this);
		(*this) = FVector(X + 1, Y + 1);
		return temp;
	}

	FORCEINLINE const FVector operator--(int)
	{
		FVector temp = (*this);
		(*this) = FVector(X - 1, Y - 1);
		return temp;
	}

	FORCEINLINE float operator[](int index)
	{
		if (index == 0) return X;
		else return Y;
	}
	
	FORCEINLINE bool operator==(const FVector& vec) const
	{ return (X == vec.X) && (Y == vec.Y); }
	
	FORCEINLINE bool operator!=(const FVector& vec) const
	{ return (X != vec.X) || (Y != vec.Y); }
};

