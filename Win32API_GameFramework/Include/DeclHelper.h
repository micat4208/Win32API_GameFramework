#pragma once

#include "TypeDefine.h"

// This:: or Super:: �� ����ϱ� ���� �ۼ�

// Ŭ���� ���� ��ܿ� �ۼ��ؾ� ��.
/*
    CLASS(MyClass, BaseClass)
	class MyClass : public BaseClass { ... }

	CLASS(MyClass, )
	class MyClass { ... }
*/
#define CLASS(_ThisClass, _BaseClass)        \
typedef class _ThisClass _This_##_ThisClass; \
typedef class _BaseClass _Base_##_ThisClass; 
											 
// Ŭ������ �������̽� ��ü ù �ٿ� �ۼ��ؾ� ��.
/*
    
    CLASS(MyClass, BaseClass)
	class MyClass : public BaseClass 
	{
		USE_CLASS(MyClass);
		...
	}

	interface IMyInterface 
	{
		USE_INTERFACE(IMyInterface);
		...
	}
*/
#define USE_CLASS(_ThisClass)                \
typedef _This_##_ThisClass This;             \
typedef _Base_##_ThisClass Super

#define USE_INTERFACE(_ThisInterfaceClass)   \
FORCEINLINE virtual ~_ThisInterfaceClass() {}


