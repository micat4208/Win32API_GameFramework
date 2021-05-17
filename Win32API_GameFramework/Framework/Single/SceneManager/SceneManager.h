#pragma once
#include "Framework/Single/ManagerClassBase/ManagerClassBase.h"
#include "Framework/Base/Scene/Scene.h"

// 씬을 관리할 클래스
class CSceneManager final :
    public CManagerClassBase<CSceneManager>
{
private :
    // 현재 씬
    CScene* CurrentScene;

    // 다음 씬
    CScene* NextScene;

public :
    CSceneManager();

public :
    virtual void ReleaseManagerClass() override;

public :
    void Tick(float deltaSeconds);
    void Render(HDC hdc);

public :
    template<typename SceneType>
    void LoadScene()
    {
        // 상속 관계 확인
        if (!IsA<CScene, SceneType>())
        {
            LOG(ToTString(typeid(SceneType).name()) << 
                TEXT(" 형식은 CScene 형식과 상속 관계가 아닌 형식입니다."));
            return;
        }

        // 만약 전에 할당시킨 씬이 존재할 경우 할당되었던 씬 객체 해제
        CObject::DeleteObject(NextScene);

        // 다음 씬을 설정합니다.
        NextScene = NewObject<SceneType>();
    }

    // 활설화중인 씬을 반환합니다.
    FORCEINLINE CScene* GetActiveScene() const
    { return CurrentScene; }
};

