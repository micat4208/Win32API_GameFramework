#include "Include/DefaultInclude.h"

#include "Framework/Single/GameInstance/GameInstance.h"
#include "Framework/Single/CollisionManager/CollisionManager.h"
#include "Framework/Single/SceneManager/SceneManager.h"
#include "Framework/Single/InputManager/InputManager.h"

/*
* TODO...
* SpriteRendererComponent
* AI - BehaviorControllerComponent, AIBehavior
* AudioComponent
* 
* Game �� ���� ����
* 
* 
		RPG
		�� : TopDown
		
		�ʿ��� ��ҵ�
		����
		����
			AI
		
		��ȣ�ۿ� ������ ��ü��
			Npc
		UI
			����	�κ��丮
*/


HWND Hwnd;

// GameInstance
DEF_GAMEINSTANCECLASS* GameInstance;
float GameStartTime;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPTSTR		lpszCmdParam,
	int			nCmdShow)
{
	srand(GameStartTime = GetTickCount64());

	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra = wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = TEXT("WndClass");
	wndClass.lpszMenuName = NULL;

	RegisterClass(&wndClass);
	Hwnd = CreateWindow(
		wndClass.lpszClassName,
		WND_DEFAULT_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WND_WIDTH, WND_HEIGHT,
		NULL, NULL,
		wndClass.hInstance,
		NULL);

	ShowWindow(Hwnd, nCmdShow);

	// GameInstance ����
	GameInstance = CObject::NewObject<DEF_GAMEINSTANCECLASS>();

	// ��ǥ �������� ������ ���� �� �ð� ����
	float targetDS = 1.0f / TARGET_FPS;

	// ������ ���� ���� ���� �ð� ������ ������ ����� ����
	float totalDS = 0.0f;
	float functionCallDelta;

	// �ð��� ���ϱ� ���� ����
	LARGE_INTEGER Second;
	LARGE_INTEGER Counter;
	/// - LARGE_INTEGER : 64 ��Ʈ ���� ������������ �����ϱ� ���� ����
	/// - ���� �����Ϸ��� 64 ��Ʈ�� �����Ѵٸ� QuardPart ��, 
	///   �������� �ʰ� 32��Ʈ�� �����Ѵٸ� LowPart, HighPart �� 64 ��Ʈ �����͸� ������ �����մϴ�.

	QueryPerformanceFrequency(&Second);
	/// - QueryPerformanceFrequency(LARGE_INTEGER * lpFrequency) : �����Ǵ� Ÿ�̸� �ػ󵵸� lpFrequency �� �����մϴ�.
	
	QueryPerformanceCounter(&Counter);
	/// - QueryPerformanceCounter(LARGE_INTEGER * lpPerformanceCount) : ���� CPU Ŭ�� ���� lpPerformanceCount �� �����մϴ�.


	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT)
	{
		// GetMessage �� �޽����� �߻��� ������ ����ϹǷ� ���ӿ��� ����ϱ⿡�� �������� ����.
		// �׷��Ƿ� PeekMessage �� ����Ͽ� ó���� �޽����� ������ ���(true ��ȯ) �߻��� �޽����� ó���ϰ�,
		// ó���� �޽����� �������� ���� ���(false ��ȯ) �ٸ� ó���� �Ҽ� �ֵ��� �մϴ�.
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ���� CPU Ŭ�� ���� ����ϴ�.
			LARGE_INTEGER currentClock;
			QueryPerformanceCounter(&currentClock);

			functionCallDelta = (currentClock.QuadPart - Counter.QuadPart) / (float)Second.QuadPart;
			Counter = currentClock;

			if (totalDS >= targetDS)
			{
				CInputManager::Instance()->UpdateInputValue();

				// �浹ü �˻�
				CCollisionManager::Instance()->DoCollisionTest();

				// Tick �޼��� ȣ��
				CSceneManager::Instance()->Tick(totalDS);
				// Render �޼��� ȣ��
				CSceneManager::Instance()->Render(GameInstance->GetDC());

				totalDS = 0.0f;
			}

			totalDS += functionCallDelta;

		}

	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		RECT wndRC = { 0, 0, WND_WIDTH, WND_HEIGHT };
		AdjustWindowRect(&wndRC, WS_OVERLAPPEDWINDOW, FALSE);

		float wndLeft = SCREEN_CENTER_X - (WND_WIDTH * 0.5f);
		float wndTop = SCREEN_CENTER_Y - (WND_HEIGHT * 0.5f);
		MoveWindow(hwnd, 
			wndLeft, wndTop, 
			wndRC.right - wndRC.left, 
			wndRC.bottom - wndRC.top, 
			false);

		return 0;
	}

	case WM_DESTROY:

		// GameInstance ����
		CObject::DeleteObject(GameInstance);

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
