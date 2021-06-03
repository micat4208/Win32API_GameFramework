#pragma once

#define _USE_MATH_DEFINES

#include "Include/DefaultInclude.h"
#include <cmath>

#define PI		M_PI

struct FMath
{
	// ���� ������ ������ ��ȯ�ϴ� �Լ�
	static FORCEINLINE int32 Rand()
	{ return rand(); }

	// �Ǽ� ������ ������ ��ȯ�ϴ� �Լ�
	static FORCEINLINE float FRand()
	{ return rand() / (float)RAND_MAX; }

	// Boolean ������ ������ ��ȯ�ϴ� �Լ�
	static FORCEINLINE bool BRand()
	{ return (rand() % 2 == 1) ? true : false; }

	// ���� ���� ���� ������ ������ ��ȯ�ϴ� �Լ�
	static FORCEINLINE int32 RandRange(int32 _min, int32 _max)
	{ return (rand() % ((_max + 1) - _min)) + _min; }

	static FORCEINLINE float RandRange(float _min, float _max)
	{ return FRandRange(_min, _max); }
	// ���� ���� �Ǽ� ������ ������ ��ȯ�ϴ� �Լ�
	static FORCEINLINE float FRandRange(float _min, float _max)
	{ return (_min + (_max - _min) * FRand()); }

	// x �� ����̰ų� 0 �̸�, 1 ��, ������� -1 �� ��ȯ�մϴ�. 
	static FORCEINLINE int32 Sign(int32 x)
	{ return (x < 0) ? -1 : 1; }
	static FORCEINLINE int32 Sign(float x)
	{ return (x < 0) ? -1 : 1; }


	// ���밪�� ��ȯ�ϴ� �Լ�
	static FORCEINLINE int32 Abs(int32 i)
	{ return abs(i); }
	static FORCEINLINE float Abs(float f)
	{ return fabs(f); }

	static FORCEINLINE int32 Distance(int32 a, int32 b)
	{ return Abs(a - b); }
	static FORCEINLINE float Distance(float a, float b)
	{ return Abs(a - b); }

	// �Ǽ� a, b �� ���� ����� ������ Ȯ���ϴ� �Լ�
	static FORCEINLINE bool Approximately(float a, float b,
		float errorTolenance = (1.e-8f))
	{ return (Abs(a) - Abs(b)) <= errorTolenance; }

	static FORCEINLINE int32 Min(int32 a, int32 b)
	{ return ((a <= b) ? a : b); }
	
	static FORCEINLINE int32 Max(int32 a, int32 b)
	{ return ((a >= b) ? a : b); }
	
	static FORCEINLINE float Min(float a, float b)
	{ return ((a <= b) ? a : b); }
	
	static FORCEINLINE float Max(float a, float b)
	{ return ((a >= b) ? a : b); }

	// value �� ���� _min �� _max ������ ������ ��ȯ�Ͽ� ��ȯ�ϴ� �Լ�
	static FORCEINLINE int32 Clamp(int32 value, int32 _min, int32 _max)
	{ return Min(_max, Max(value, _min)); }
	static FORCEINLINE float Clamp(float value, float _min, float _max)
	{ return Min(_max, Max(value, _min)); }

	// value �� ���� _min, _max ������ ������ Ȯ���ϴ� �Լ�
	static FORCEINLINE bool IsIn(int32 value, int32 _min, int32 _max, bool bUseAboveOrBelow = false)
	{ 
		return (bUseAboveOrBelow) ?
			(value >= _min && value <= _max) : 
			(value > _min && value < _max); 
	}
	static FORCEINLINE bool IsIn(float value, float _min, float _max, bool bUseAboveOrBelow = false)
	{
		return (bUseAboveOrBelow) ?
			(value >= _min && value <= _max) :
			(value > _min && value < _max);
	}

	// t �� �̿��Ͽ� a ���� b ���� ����������ŵ�ϴ�. (�)
	static FORCEINLINE float Lerp(float a, float b, float t)
	{ return (a + ((b - a)* t)); }
	// t �� �̿��Ͽ� a ���� b ���� ����������ŵ�ϴ�. (����)
	static FORCEINLINE float MoveToWards(float a, float b, float maxDistanceDelta)
	{ return (Abs(b - a) <= maxDistanceDelta) ? b : a + (Sign(b - a) * maxDistanceDelta); }






};