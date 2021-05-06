#pragma once

#include "Include/DefaultInclude.h"

// Ǯ�� ��ų ��ü���� �����Ǿ�� �ϴ� �������̽� Ŭ�����Դϴ�.
interface IObjectPoolable
{
	// ���� ���� ���¿� ���� ������ �����ڸ� ��Ÿ���ϴ�.
	virtual void SetCanRecyclable(bool bCanRecyclable) PURE;
	virtual bool GetCanRecyclable() const PURE;

	// ��Ȱ���� �Ǵ� ������ ȣ��Ǵ� �޼���
	virtual void OnRecycleStarted() PURE;

	virtual ~IObjectPoolable() {}
};