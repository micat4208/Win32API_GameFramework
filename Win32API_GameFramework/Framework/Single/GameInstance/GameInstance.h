#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Interface/ManagerClass.h"

class CGameInstance :
    public CObject
{
protected :
    // IManagerClass 인터페이스를 구현하는 객체들을 저장합니다.
    map <string, IManagerClass*> ManagerClasses;

public :
    CGameInstance();

    virtual void Initialize() override;
    virtual void Release() override;

protected :
    template<typename ManagerClassType>
    FORCEINLINE void RegisterManagerClass()
    {
        // 상속 관계를 확인합니다.
        if (!IsA<IManagerClass, ManagerClassType>()) return;

        // SubManager 객체를 생성합니다.
        IManagerClass* newSubManagerInstance = NewObject<ManagerClassType>();

        // map 에 추가합니다.
        ManagerClasses.insert( make_pair(typeid(ManagerClassType).name(), newSubManagerInstance) );

        // 매니저 객체를 초기화시킵니다.
        newSubManagerInstance->InitializeManagerClass();
    }

public :
    template<typename ManagerClassType>
    FORCEINLINE ManagerClassType* GetManagerClass() const
    { return Cast<ManagerClassType>(ManagerClasses[string(typeid(ManagerClassType).name())]); }

};

