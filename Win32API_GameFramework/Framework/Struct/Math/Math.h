#pragma once

#define _USE_MATH_DEFINES

#include "Include/DefaultInclude.h"
#include <cmath>

#define PI		M_PI

struct FMath
{
	// 정수 형식의 난수를 반환하는 함수
	static FORCEINLINE int32 Rand()
	{ return rand(); }

	// 실수 형식의 난수를 반환하는 함수
	static FORCEINLINE float FRand()
	{ return rand() / (float)RAND_MAX; }

	// Boolean 형식의 난수를 반환하는 함수
	static FORCEINLINE bool BRand()
	{ return (rand() % 2 == 1) ? true : false; }

	// 범위 내의 정수 형식의 난수를 반환하는 함수
	static FORCEINLINE int32 RandRange(int32 _min, int32 _max)
	{ return (rand() % ((_max + 1) - _min)) + _min; }

	static FORCEINLINE float RandRange(float _min, float _max)
	{ return FRandRange(_min, _max); }
	// 범위 내의 실수 형식의 난수를 반환하는 함수
	static FORCEINLINE float FRandRange(float _min, float _max)
	{ return (_min + (_max - _min) * FRand()); }

	// x 가 양수이거나 0 이면, 1 을, 음수라면 -1 을 반환합니다. 
	static FORCEINLINE int32 Sign(int32 x)
	{ return (x < 0) ? -1 : 1; }
	static FORCEINLINE int32 Sign(float x)
	{ return (x < 0) ? -1 : 1; }


	// 절대값을 반환하는 함수
	static FORCEINLINE int32 Abs(int32 i)
	{ return abs(i); }
	static FORCEINLINE float Abs(float f)
	{ return fabs(f); }

	static FORCEINLINE int32 Distance(int32 a, int32 b)
	{ return Abs(a - b); }
	static FORCEINLINE float Distance(float a, float b)
	{ return Abs(a - b); }

	// 실수 a, b 가 서로 비슷한 값임을 확인하는 함수
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

	// value 의 값을 _min 과 _max 사이의 값으로 변환하여 반환하는 함수
	static FORCEINLINE int32 Clamp(int32 value, int32 _min, int32 _max)
	{ return Min(_max, Max(value, _min)); }
	static FORCEINLINE float Clamp(float value, float _min, float _max)
	{ return Min(_max, Max(value, _min)); }

	// value 의 값이 _min, _max 사이의 값임을 확인하는 함수
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

	// t 를 이용하여 a 부터 b 까지 선형보간시킵니다. (곡선)
	static FORCEINLINE float Lerp(float a, float b, float t)
	{ return (a + ((b - a)* t)); }
	// t 를 이용하여 a 부터 b 까지 선형보간시킵니다. (직선)
	static FORCEINLINE float MoveToWards(float a, float b, float maxDistanceDelta)
	{ return (Abs(b - a) <= maxDistanceDelta) ? b : a + (Sign(b - a) * maxDistanceDelta); }






};