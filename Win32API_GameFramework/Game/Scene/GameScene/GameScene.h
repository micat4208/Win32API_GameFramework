#pragma once
#include "Framework/Base/Scene/Scene.h"

class CGameScene final :
    public CScene
{
private :
    class CAudioObject* AudioObject;

public :
    virtual void Initialize() override;

public :
    FORCEINLINE class CAudioObject* GetAudioObject() const
    { return AudioObject; }
};

