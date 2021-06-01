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
	// v1 �� v2 �� �Ÿ��� ��ȯ�ϴ� �Լ�
	static float Distance(const FVector& v1, const FVector& v2);

	// from ���� to ���� ������ ��ȯ�մϴ�.
	static FVector Direction(const FVector& from, const FVector& to);

public :
	// Vector �� ���̸� ��ȯ�մϴ�.
	float Length() const;

	// X*X + Y*Y �� ���� ��ȯ�մϴ�.
	FORCEINLINE float SizeSquared() const
	{ return X * X + Y * Y; }

	// �� ���͸� �������ͷ� ����ϴ�.
	void Normalize();

	// �� ���͸� �̿��Ͽ� �������͸� ����� ��ȯ�մϴ�.
	FVector Normalized() const;


	// �� ���Ͱ� ������������ Ȯ���մϴ�.
	bool IsUnit(float errorTolerance = (1.e-8f)) const;

	// �ش� ��ġ�� â ���ο� ��ġ�ϴ��� Ȯ����
	bool InWnd() const;


	// �ش� ��ġ�� â ���ο� ��ġ�ϴ��� Ȯ����
	// cameraPosition : �����ų ī�޶� ��ġ
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
	// ��� ������ �����ε�
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

	// ���� ������
	FORCEINLINE const FVector operator++()
	{ return ((*this) = FVector(X + 1, Y + 1)); }
	FORCEINLINE const FVector operator--()
	{ return ((*this) = FVector(X - 1, Y - 1)); }
	
	// ���� ������
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

