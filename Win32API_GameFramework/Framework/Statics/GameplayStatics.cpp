#include "GameplayStatics.h"

float CGameplayStatics::GetTime()
{
    return (GetTickCount64() - GameStartTime) * 0.001f;
}

FVector CGameplayStatics::GetMousePosition(bool translated)
{
    // Ŀ�� ��ġ�� ������ ����
    POINT position;

    // ��ũ�� ������ ���콺 ��ġ�� ����ϴ�.
    GetCursorPos(&position);
    if (!translated) return FVector(position.x, position.y);

    // â ������ ���콺 ��ġ�� ����ϴ�.
    ScreenToClient(Hwnd, &position);
    return FVector(position.x, position.y);
}
