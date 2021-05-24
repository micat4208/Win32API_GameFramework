#pragma once

#include <Windows.h>
#include <iostream>

#include <combaseapi.h>
#include <functional>

#include <vector>
#include <map>
#include <list>

#include "TypeDefine.h"
#include "GameDefine.h"
#include "GameDebug.h"

#pragma comment (lib, "msimg32.lib")

using namespace std;






#define WND_DEFAULT_TITLE		TEXT("Win32Api GameFramework")

#define WND_WIDTH				800
#define WND_HEIGHT				600

#define SCREEN_CENTER_X			(1920 * 0.5f)
#define SCREEN_CENTER_Y			(1080 * 0.5f)


extern HWND Hwnd;
extern float GameStartTime;
extern HINSTANCE HInstance;



/*
	Framework: ���� ���߿� �ʿ��� ���
	Object
	GameInstance : ���� ��ü�� �����ϴ� ��ü
		SubManager : ��ü���� ī�װ����� ���� ������ �� ���� Ŭ����
		PlayerManager : �÷��̾�� ���õ� �����͸� �����ϰ� �� ��ü
		SceneManager : ���� ���õ� �����͵��� �����ϰ� �� ��ü
		CollisionManager : �浹ü�� ���õ� �����͵��� �����ϰ� �� ��ü
	Scene : �ϳ��� ���������� ��Ÿ�� �� ���� Ŭ����
	GameObject : �ϳ��� ���������� �����ϴ� ��ü�� ������ ���� Ŭ����
	
	Component : GameObject ��ü�� ���ȭ ��ų �� ���� Ŭ����
	RenderComponent : ȭ�鿡 �׸��� ����� �����ϰ� �� ������Ʈ
	AudioComponent : �Ҹ� ����� ���õ� ����� �����ϰ� �� ������Ʈ
	[FMOD �ܺ� ���̺귯�� ���]
	
	Bitmap : �̹����� ����ϴ� ����� �����ϴ� Ŭ����
	
	
	Game : ���� ���߿� �ʿ��� ����


	��Ģ
	��� Ŭ����, ����ü, ���� ����, �������̽� �̸� �տ��� ���ξ ����� ��
	/// - Ŭ���� : C
	/// - ����ü : F
	/// - �������̽� : I
	/// - ���� ���� : E
	/// - �̷��� ���ξ�� ���ϸ��� ������� �ʽ��ϴ�.

*/