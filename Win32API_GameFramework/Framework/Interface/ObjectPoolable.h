#pragma once

#include "Include/DefaultInclude.h"

// 풀링 시킬 객체에서 구현되어야 하는 인터페이스 클래스입니다.
interface IObjectPoolable
{
	// 재사용 가능 상태에 대한 접근자 설정자를 나타냅니다.
	virtual void SetCanRecyclable(bool bCanRecyclable) PURE;
	virtual bool GetCanRecyclable() const PURE;

	// 재활용이 되는 시점에 호출되는 메서드
	virtual void OnRecycleStarted() PURE;

	virtual ~IObjectPoolable() {}
};