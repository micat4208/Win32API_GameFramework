#include "MapEditorScene.h"

#include "Framework/Single/SceneManager/SceneManager.h"

#include "Game/GameObject/TileMap/TileMap.h"

#include "resource.h"

void CMapEditorScene::Initialize()
{
	super::Initialize();

	TileMap = NewGameObject<CTileMap>();

	TileMapCountX = 0;
	TileMapCountY = 0;

}

void CMapEditorScene::Tick(float dt)
{
	super::Tick(dt);

	if (TileMapCountX == 0 || TileMapCountY == 0)
	{
		// ���̾�α׸� ���ϴ�.
		if (DialogBox(HInstance, MAKEINTRESOURCE(IDD_DIALOG_MAP_SETTING),
			Hwnd, (DLGPROC)&CMapEditorScene::MapSettingDlgProc) == IDOK)
		{
			// �� ũ�� ����
			TileMap->SetTileMapXY(TileMapCountX, TileMapCountY);

			// Ÿ�ϸ� ������ ����
			TileMap->SetTileMapScale(TileMapScale);

			// Ÿ�ϸ��� �����մϴ�.
			TileMap->MakeTileMap();

		}
	}

}

BOOL CMapEditorScene::MapSettingDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CMapEditorScene* mapEditorScene = Cast<CMapEditorScene>(
		CSceneManager::Instance()->GetActiveScene());

	switch (msg)
	{
		case WM_INITDIALOG :
		{
			// �� ũ�� ����Ʈ ���� ����
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
