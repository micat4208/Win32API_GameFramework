#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Interface/ManagerClass.h"

class CGameInstance :
    public CObject
{
protected :
    // IManagerClass �������̽��� �����ϴ� ��ü���� �����մϴ�.
    map <string, IManagerClass*> ManagerClasses;

public :
    CGameInstance();

    virtual void Initialize() override;
    virtual void Release() override;

protected :
    template<typename ManagerClassType>
    FORCEINLINE void RegisterManagerClass()
    {
        // ��� ���踦 Ȯ���մϴ�.
        if (!IsA<IManagerClass, ManagerClassType>()) return;

        // SubManager ��ü�� �����մϴ�.
        IManagerClass* newSubManagerInstance = NewObject<ManagerClassType>();

        // map �� �߰��մϴ�.
        ManagerClasses.insert( make_pair(typeid(ManagerClassType).name(), newSubManagerInstance) );

        // �Ŵ��� ��ü�� �ʱ�ȭ��ŵ�ϴ�.
        newSubManagerInstance->InitializeManagerClass();
    }

public :
    template<typename ManagerClassType>
    FORCEINLINE ManagerClassType* GetManagerClass() const
    { return Cast<ManagerClassType>(ManagerClasses[string(typeid(ManagerClassType).name())]); }

};

