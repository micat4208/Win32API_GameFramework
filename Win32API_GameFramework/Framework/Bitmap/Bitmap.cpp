#include "Bitmap.h"

CBitmap::CBitmap()
{
	Hdc = MemDC = NULL;
	Bmp = OldBmp = NULL;
	BitmapInfo = nullptr;
}

CBitmap* CBitmap::LoadBmp(CBitmap* bitmap, tstring path)
{
	bitmap->Hdc = ::GetDC(Hwnd);
	bitmap->MemDC = ::CreateCompatibleDC(bitmap->Hdc);

	bitmap->Bmp = (HBITMAP)(LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
	/// - LoadImage(hInstance, lpszName, uType, cx, cy, fuLoad) : 이미지를 로드합니다.
	/// - hInstance : 이미지 리소스를 가질 모듈의 핸들, 파일 경로를 대입하여 로드하는 경우 NULL 을 전달합니다.
	/// - lpszName : 파일 경로를 전달합니다.
	/// - uType : 읽고자 하는 타입을 전달합니다.
	/// - cx, cy : 아이콘 / 커서의 너비 높이를 전달합니다.
	/// - fuLoad : 이미지를 읽어올 방법을 전달합니다.
	
	// 이미지 로드에 실패한 경우
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

	// 비트맵 정보 초기화
	{
		int32 bmpWidth = bitmapInfo.bmWidth;
		int32 bmpHeight = bitmapInfo.bmHeight;

		COLORREF** pixelColor = new COLORREF*[bmpHeight];

		// 픽셀 색상을 얻습니다.
		for (int32 y = 0; y < bmpHeight; ++y)
		{
			pixelColor[y] = new COLORREF[bmpWidth];
			for (int32 x = 0; x < bmpWidth; ++x)
				pixelColor[y][x] = GetPixel(bitmap->GetDC(), x, y);
		}

		bitmap->BitmapInfo = NewObject<FBitmapInfo>();
		bitmap->BitmapInfo->InitializeBitmapInfo(pixelColor, bmpWidth, bmpHeight);
	}

	return bitmap;
}

void CBitmap::Release()
{
	super::Release();

	::DeleteObject(SelectObject(MemDC, OldBmp));
	::DeleteDC(MemDC);

	CObject::DeleteObject(BitmapInfo);
}

void CBitmap::FlipXY(bool flipX, bool flipY)
{
	if (!BitmapInfo) return;

	// DC 의 변경할 픽셀 위치를 나타내는 변수
	int32 targetPixelX = 0, targetPixelY = 0;

	if (flipX && flipY)	// Flip X, Y
	{
		for (int32 y = BitmapInfo->PixelYCount - 1; y > 0; (--y, ++targetPixelY))
		{
			for (int32 x = BitmapInfo->PixelXCount - 1; x > 0; (--x, ++targetPixelX))
				SetPixel(GetDC(), targetPixelX, targetPixelY, BitmapInfo->PixelColors[y][x]);
			targetPixelX = 0;
		}
	}
	else if (flipX)	// Flip X
	{
		for (int32 y = 0; y < BitmapInfo->PixelYCount; ++y)
		{
			for (int32 x = BitmapInfo->PixelXCount - 1; x > 0; (--x, ++targetPixelX))
				SetPixel(GetDC(), targetPixelX, y, BitmapInfo->PixelColors[y][x]);
			targetPixelX = 0;
		}

	}
	else if (flipY)	// Flip Y
	{
		for (int32 y = BitmapInfo->PixelYCount - 1; y > 0; (--y, ++targetPixelY))
		{
			for (int32 x = 0; x < BitmapInfo->PixelXCount; ++x)
				SetPixel(GetDC(), x, targetPixelY, BitmapInfo->PixelColors[y][x]);
		}
	}
}
