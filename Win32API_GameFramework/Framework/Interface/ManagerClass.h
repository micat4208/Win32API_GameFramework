#pragma once

#include "Include/DefaultInclude.h"

// ManagerClass ���� ��� ����
interface IManagerClass
{
	// �Ŵ��� ��ü�� ��ϵ� �� ȣ��� �޼���
	virtual void InitializeManagerClass() PURE;

	// �Ŵ��� ��ü�� �Ҹ�� �� ȣ��� �޼���
	virtual void ReleaseManagerClass() PURE;

	virtual ~IManagerClass() {}
};