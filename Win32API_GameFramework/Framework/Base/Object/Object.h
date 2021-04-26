#pragma once

#include "Include/DefaultInclude.h"

#define super __super

// 모든 클래스의 기반 형식이 될 형식입니다.
class CObject
{
public :
	CObject();
	FORCEINLINE virtual void Initialize() {}
	FORCEINLINE virtual void Release() {}
	virtual ~CObject();

public :
	virtual tstring ToString() const;

	// ParentType 형식과 ChildType 형식이 상속 관계에 속해있는지 확인합니다.
	template<typename ParentType, typename ChildType>
	FORCEINLINE static bool IsA(const ChildType* childInstance)
	{ return is_base_of<ParentType, ChildType>(); }

	template<typename ParentType, typename ChildType>
	FORCEINLINE static bool IsA()
	{ return is_base_of<ParentType, ChildType>(); }

	// T * 형식의 객체를 TargetType * 형식으로 변환하여 반환합니다.
	template<typename TargetType, typename T>
	FORCEINLINE static TargetType* Cast(const T* instance)
	{ return dynamic_cast<TargetType*>(instance); }

	template<typename T>
	FORCEINLINE static T* NewObject()
	{
		T* newObject = new T();
		newObject->Initialize();

		return newObject;
	}

	template<typename T>
	FORCEINLINE static void DeleteObject(T*& object)
	{
		object->Release();
		delete object;
		object = nullptr;
	}

};



