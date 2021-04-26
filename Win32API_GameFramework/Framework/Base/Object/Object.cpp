#include "Object.h"

CObject::CObject()  { }
CObject::~CObject() { }

tstring CObject::ToString() const
{
	tstring str;
	string typeString = typeid(*this).name();
	str.assign(typeString.begin(), typeString.end());

	return str;
}
