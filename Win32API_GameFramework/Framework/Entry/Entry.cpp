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
* Game 을 위한 구조
* 
* 
		RPG
		뷰 : TopDown
		
		필요한 요소들
		던전
		몬스터
			AI
		
		상호작용 가능한 객체들
			Npc
		UI
			상점	인벤토리
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

	// GameInstance 생성
	GameInstance = CObject::NewObject<DEF_GAMEINSTANCECLASS>();

	// 목표 프레임이 나오기 위한 실 시간 간격
	float targetDS = 1.0f / TARGET_FPS;

	// 프레임 고정 전의 실행 시간 간격이 더해져 저장될 변수
	float totalDS = 0.0f;
	float functionCallDelta;

	// 시간을 구하기 위한 변수
	LARGE_INTEGER Second;
	LARGE_INTEGER Counter;
	/// - LARGE_INTEGER : 64 비트 정수 데이터형식을 저장하기 위한 형식
	/// - 만약 컴파일러가 64 비트를 지원한다면 QuardPart 에, 
	///   지원하지 않고 32비트만 지원한다면 LowPart, HighPart 에 64 비트 데이터를 나누어 저장합니다.

	QueryPerformanceFrequency(&Second);
	/// - QueryPerformanceFrequency(LARGE_INTEGER * lpFrequency) : 지원되는 타이머 해상도를 lpFrequency 에 저장합니다.
	
	QueryPerformanceCounter(&Counter);
	/// - QueryPerformanceCounter(LARGE_INTEGER * lpPerformanceCount) : 현재 CPU 클럭 수를 lpPerformanceCount 에 저장합니다.


	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT)
	{
		// GetMessage 는 메시지가 발생할 때까지 대기하므로 게임에서 사용하기에는 적합하지 않음.
		// 그러므로 PeekMessage 를 사용하여 처리할 메시지가 존재할 경우(true 반환) 발생한 메시지를 처리하고,
		// 처리할 메시지가 존재하지 않을 경우(false 반환) 다른 처리를 할수 있도록 합니다.
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 현재 CPU 클럭 수를 얻습니다.
			LARGE_INTEGER currentClock;
			QueryPerformanceCounter(&currentClock);

			functionCallDelta = (currentClock.QuadPart - Counter.QuadPart) / (float)Second.QuadPart;
			Counter = currentClock;

			if (totalDS >= targetDS)
			{
				CInputManager::Instance()->UpdateInputValue();

				// 충돌체 검사
				CCollisionManager::Instance()->DoCollisionTest();

				// Tick 메서드 호출
				CSceneManager::Instance()->Tick(totalDS);
				// Render 메서드 호출
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

		// GameInstance 해제
		CObject::DeleteObject(GameInstance);

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
