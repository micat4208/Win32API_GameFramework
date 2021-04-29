#include "Bitmap.h"

CBitmap::CBitmap()
{
	Hdc = MemDC = NULL;
	Bmp = OldBmp = NULL;
}

CBitmap* CBitmap::LoadBmp(CBitmap*& bitmap, tstring path)
{
	bitmap->Hdc = ::GetDC(Hwnd);
	bitmap->MemDC = ::CreateCompatibleDC(bitmap->Hdc);

	bitmap->Bmp = (HBITMAP)(LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
	/// - LoadImage(hInstance, lpszName, uType, cx, cy, fuLoad) : �̹����� �ε��մϴ�.
	/// - hInstance : �̹��� ���ҽ��� ���� ����� �ڵ�, ���� ��θ� �����Ͽ� �ε��ϴ� ��� NULL �� �����մϴ�.
	/// - lpszName : ���� ��θ� �����մϴ�.
	/// - uType : �а��� �ϴ� Ÿ���� �����մϴ�.
	/// - cx, cy : ������ / Ŀ���� �ʺ� ���̸� �����մϴ�.
	/// - fuLoad : �̹����� �о�� ����� �����մϴ�.
	
	// �̹��� �ε忡 ������ ���
	if (bitmap->Bmp == NULL)
	{
		tstring title = TEXT("Bitmap Image Load Failed!");
		tstring msg = TEXT("path : ") + path;

		LOG(TEXT("[WARNING] ") << title << TEXT(" : ") << msg);
		MessageBox(Hwnd, msg.c_str(), title.c_str(), MB_OK | MB_ICONWARNING);

		return bitmap;
	}

	BITMAP bitmapInfo;
	GetObject(bitmap->Bmp, sizeof(bitmapInfo), &bitmapInfo);

	bitmap->Size = FVector(bitmapInfo.bmWidth, bitmapInfo.bmHeight);

	bitmap->OldBmp = (HBITMAP)SelectObject(bitmap->MemDC, bitmap->Bmp);
	ReleaseDC(Hwnd, bitmap->Hdc);

	return bitmap;
}

void CBitmap::Release()
{
	super::Release();

	::DeleteObject(SelectObject(MemDC, OldBmp));
	::DeleteDC(MemDC);
}
