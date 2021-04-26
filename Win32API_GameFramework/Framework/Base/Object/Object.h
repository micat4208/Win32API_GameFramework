#pragma once

#include "Include/DefaultInclude.h"

#define super __super

// ��� Ŭ������ ��� ������ �� �����Դϴ�.
class CObject
{
public :
	CObject();
	FORCEINLINE virtual void Initialize() {}
	FORCEINLINE virtual void Release() {}
	virtual ~CObject();

public :
	virtual tstring ToString() const;

	// ParentType ���İ� ChildType ������ ��� ���迡 �����ִ��� Ȯ���մϴ�.
	template<typename ParentType, typename ChildType>
	FORCEINLINE static bool IsA(const ChildType* childInstance)
	{ return is_base_of<ParentType, ChildType>(); }

	template<typename ParentType, typename ChildType>
	FORCEINLINE static bool IsA()
	{ return is_base_of<ParentType, ChildType>(); }

	// T * ������ ��ü�� TargetType * �������� ��ȯ�Ͽ� ��ȯ�մϴ�.
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



