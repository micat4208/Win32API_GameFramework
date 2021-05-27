#include "MapEditorScene.h"

#include "Framework/Single/SceneManager/SceneManager.h"
#include "Framework/Single/InputManager/InputManager.h"

#include "Game/GameObject/TileMap/TileMap.h"

#include "resource.h"

void CMapEditorScene::Initialize()
{
	super::Initialize();

	TileMap = NewGameObject<CTileMap>();

	TileMapCountX = 0;
	TileMapCountY = 0;
	CameraSpeed = 1.0f;

}

void CMapEditorScene::Tick(float dt)
{
	super::Tick(dt);

	if (TileMapCountX == 0 || TileMapCountY == 0)
	{
		// 다이얼로그를 띄웁니다.
		if (DialogBox(HInstance, MAKEINTRESOURCE(IDD_DIALOG_MAP_SETTING),
			Hwnd, (DLGPROC)&CMapEditorScene::MapSettingDlgProc) == IDOK)
		{
			// 맵 크기 설정
			TileMap->SetTileMapXY(TileMapCountX, TileMapCountY);

			// 타일맵 스케일 설정
			TileMap->SetTileMapScale(TileMapScale);

			// 타일맵을 생성합니다.
			TileMap->MakeTileMap();

		}
	}

	InputKey(dt);
}

void CMapEditorScene::InputKey(float dt)
{
	float wheelAxis = CInput::GetAxis(TEXT("MouseWheel"));
	bool bIsWheelKeyInput = !FMath::Approximately(wheelAxis, 0.0f);

	if (bIsWheelKeyInput)
	{
		CameraSpeed += wheelAxis * 0.5f;
		CameraSpeed = FMath::Clamp(CameraSpeed, 0.1f, 50.0f);
	}

	FVector cameraVelocity = FVector(
		CInput::GetAxis(TEXT("Horizontal")),
		CInput::GetAxis(TEXT("Vertical")));
	cameraVelocity *= -100.0f * CameraSpeed * dt;



	MoveCamera(cameraVelocity);
}

BOOL CMapEditorScene::MapSettingDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CMapEditorScene* mapEditorScene = Cast<CMapEditorScene>(
		CSceneManager::Instance()->GetActiveScene());

	switch (msg)
	{
		case WM_INITDIALOG :
		{
			// 맵 크기 에디트 내용 설정
			SetDlgItemInt(hWnd, IDC_EDIT_MAPSIZEX, mapEditorScene->TileMapCountX, FALSE);
			SetDlgItemInt(hWnd, IDC_EDIT_MAPSIZEY, mapEditorScene->TileMapCountY, FALSE);
			SetDlgItemInt(hWnd, IDC_EDIT_MAP_SCALE, mapEditorScene->TileMapScale, FALSE);

			return FALSE;
		}


		case WM_COMMAND :
		{
			if (LOWORD(wParam) == IDC_BUTTON_SET)
			{
				mapEditorScene->TileMapCountX = GetDlgItemInt(hWnd, IDC_EDIT_MAPSIZEX, NULL, FALSE);
				mapEditorScene->TileMapCountY = GetDlgItemInt(hWnd, IDC_EDIT_MAPSIZEY, NULL, FALSE);
				mapEditorScene->TileMapScale = GetDlgItemInt(hWnd, IDC_EDIT_MAP_SCALE, NULL, FALSE);

				EndDialog(hWnd, IDOK);
			}

			return FALSE;
		}


		case WM_CLOSE :
			EndDialog(hWnd, IDCANCEL);
			return FALSE;
	}

	return FALSE;
}
