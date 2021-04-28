#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"

#include "Framework/Base/Component/Component.h"

class CGameObject :
    public CObject
{
private :
	// 추가시킬 컴포넌트들을 나타냅니다.
	list<CComponent*> CreatedComponents;

	// 추가되어 사용되는 컴포넌트들을 나타냅니다.
	list<CComponent*> UsedComponents;

	// 제거될 컴포넌트들을 나타냅니다.
	list<CComponent*> DestroyedComponents;

public :
	// 이 게임 오브젝트를 소유하는 씬 객체를 나타냅니다.
	class CScene* OwnerScene;

	// 오브젝트의 이름
	tstring Name;

	// 이 오브젝트의 위치
	FVector Position;

	// 이 오브젝트의 Tick() 메서드를 호출할 것인지에 대한 여부를 나타냅니다.
	bool bCanEverTick;

	// 이 오브젝트의 Start() 메서드가 호출되었음을 나타냅니다.
	bool bIsStarted;

	// 이 오브젝트가 제거 대상임을 나타냅니다.
	bool bBeDestroy;

public :
	CGameObject();

public :
	// GameObject 가 생성되었을 경우 생성자 이후 한 번 호출되는 메서드
	virtual void Initialize() override;

	// GameObject 씬에 사용되는 GameObject 로 등록 되었을 경우 초기화 이후 한 번 호출되는 메서드
	virtual void Start();

	// 매 프레임마다 호출되는 메서드
	/// - DeltaSeconds : 프레임 사이 간격 시간이 전달됩니다.
	virtual void Tick(float DeltaSeconds);

	// GameObject 가 제거 대상이 되었을 경우 호출되는 메서드
	virtual void OnDestroy();

	// GameObject 가 메모리 해제될 때 호출되는 메서드
	virtual void Release() override;

public :
	template<typename T>
	FORCEINLINE static T* NewObject(class CScene * ownerScene, tstring objName)
	{
		T* newObject = new T();
		newObject->OwnerScene = ownerScene;
		newObject->Name = objName;

		newObject->Initialize();

		return newObject;
	}

};

