#include "Vector.h"


FVector::FVector() : FVector(0.0f, 0.0f) { }
FVector::FVector(float x, float y) : X(x), Y(y) { }

float FVector::Distance(const FVector& v1, const FVector& v2)
{ return sqrt(pow(v2.X - v1.X, 2) + pow(v2.Y - v1.Y, 2)); }

FVector FVector::Direction(const FVector& from, const FVector& to)
{ return FVector((to.X - from.X), (to.Y - from.Y)).Normalized(); }

float FVector::Length() const
{ return sqrt(pow(X, 2) + pow(Y, 2)); }

void FVector::Normalize()
{
	float length = Length();
	if (!FMath::Approximately(length, 0.0f))
	{
		X /= length;
		Y /= length;
	}
}

FVector FVector::Normalized() const
{
	float length = Length();
	return FMath::Approximately(length, 0.0f) ? 
		FVector::ZeroVector() :
		FVector(X / length, Y / length);
}

bool FVector::IsUnit(float errorTolerance) const
{
	return FMath::Abs(1.0f - SizeSquared()) < errorTolerance;
}

tstring FVector::ToString() const
{
	tstring str = TEXT("X = ");
	str += to_tstring(X);
	str += TEXT(", Y = ");
	str += to_tstring(Y);

	return str;
}

FVector FVector::VRand(float _min, float _max)
{ return FVector( FMath::RandRange(_min, _max), FMath::RandRange(_min, _max) ); }