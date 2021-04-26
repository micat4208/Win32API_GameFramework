#pragma once

#include "Include/DefaultInclude.h"

// ManagerClass 들의 기반 형식
interface IManagerClass
{
	// 매니저 객체가 등록될 때 호출될 메서드
	virtual void InitializeManagerClass() PURE;

	// 매니저 객체가 소멸될 때 호출될 메서드
	virtual void ReleaseManagerClass() PURE;

	virtual ~IManagerClass() {}
};