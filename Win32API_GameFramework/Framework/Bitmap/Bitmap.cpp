#include "Bitmap.h"

map<tstring, CBitmap*> CBitmap::LoadedBitmaps;

CBitmap::CBitmap()
{
	Hdc = MemDC = XFlippedHDC = YFlippedHDC = XYFlippedHDC = NULL;

	Bmp = OldBmp = XFlippedBmp = YFlippedBmp = XYFlippedBmp =
		OldXFlippedBmp = OldYFlippedBmp = OldXYFlippedBmp = NULL;

	BitmapInfo = nullptr;
	bUseFlippedBmp = bIsFlippedX = bIsFlippedY = false;
}

CBitmap* CBitmap::LoadBmp(CBitmap* bitmap, tstring path, bool bUseFlippedBmp, tstring key)
{
	if (key == TEXT("USE_PATH"))
		key = path;

	// �̹� �ε�� ��Ʈ���̶�� �̹� ������ ��ü ����
	auto iter = CBitmap::LoadedBitmaps.find(key);
	if (iter != CBitmap::LoadedBitmaps.end())
		return iter->second;

	bitmap->bUseFlippedBmp = bUseFlippedBmp;

	bitmap->Hdc = ::GetDC(Hwnd);
	bitmap->MemDC = ::CreateCompatibleDC(bitmap->Hdc);
	

	bitmap->Bmp = (HBITMAP)(LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
	/// - LoadImage(hInstance, lpszName, uType, cx, cy, fuLoad) : �̹����� �ε��մϴ�.
	/// - hInstance : �̹��� ���ҽ��� ���� ����� �ڵ�, ���� ��θ� �����Ͽ� �ε��ϴ� ��� NULL �� �����մϴ�.
	/// - lpszName : ���� ��θ� �����մϴ�.
	/// - uType : �а��� �ϴ� Ÿ���� �����մϴ�.
	/// - cx, cy : ������ / Ŀ���� �ʺ� ���̸� �����մϴ�.
	/// - fuLoad : �̹����� �о�� ����� �����մϴ�.
	
	if (bUseFlippedBmp)
	{
		FThread t1([bitmap, path]()
			{
				bitmap->XFlippedHDC = ::CreateCompatibleDC(bitmap->Hdc);
				bitmap->XFlippedBmp = (HBITMAP)(LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
			});

		FThread t2([bitmap, path]()
			{
				bitmap->YFlippedHDC = ::CreateCompatibleDC(bitmap->Hdc);				
				bitmap->YFlippedBmp = (HBITMAP)(LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
			});

		FThread t3([bitmap, path]()
			{				
				bitmap->XYFlippedHDC = ::CreateCompatibleDC(bitmap->Hdc);
				bitmap->XYFlippedBmp = (HBITMAP)(LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
			});

		
		t1.join();
		t2.join();
		t3.join();
		
	}
	
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

	if (bUseFlippedBmp)
	{
		bitmap->OldXFlippedBmp = (HBITMAP)SelectObject(bitmap->XFlippedHDC, bitmap->XFlippedBmp);
		bitmap->OldYFlippedBmp = (HBITMAP)SelectObject(bitmap->YFlippedHDC, bitmap->YFlippedBmp);
		bitmap->OldXYFlippedBmp = (HBITMAP)SelectObject(bitmap->XYFlippedHDC, bitmap->XYFlippedBmp);
	}

	ReleaseDC(Hwnd, bitmap->Hdc);

	// ��Ʈ�� ���� �ʱ�ȭ
	{
		int32 bmpWidth = bitmapInfo.bmWidth;
		int32 bmpHeight = bitmapInfo.bmHeight;

		COLORREF** pixelColor = new COLORREF*[bmpHeight];

		// �ȼ� ������ ����ϴ�.
		for (int32 y = 0; y < bmpHeight; ++y)
		{
			pixelColor[y] = new COLORREF[bmpWidth];
			for (int32 x = 0; x < bmpWidth; ++x)
				pixelColor[y][x] = GetPixel(bitmap->GetDC(), x, y);
		}

		bitmap->BitmapInfo = NewObject<FBitmapInfo>();
		bitmap->BitmapInfo->InitializeBitmapInfo(pixelColor, bmpWidth, bmpHeight);
	}


	if (bUseFlippedBmp)
	{
		// Flip X
		bitmap->FlipXY(true, false);
		bitmap->bIsFlippedX = false;

		// Flip Y
		bitmap->FlipXY(false, true);
		bitmap->bIsFlippedY = false;

		// Flip XY
		bitmap->FlipXY(true, true);
		bitmap->bIsFlippedX = bitmap->bIsFlippedY = false;
	}

	CBitmap::LoadedBitmaps.insert(make_pair(key, bitmap));

	return bitmap;
}

void CBitmap::ReleaseAllBmp()
{
	for (auto iter = CBitmap::LoadedBitmaps.begin();
		iter != CBitmap::LoadedBitmaps.end();
		iter++)
	{
		::CObject::DeleteObject(iter->second);
		// iter->second->Release();
	}
	CBitmap::LoadedBitmaps.clear();
}

void CBitmap::Release()
{
	super::Release();
	
	CObject::DeleteObject(BitmapInfo);

	::DeleteObject(SelectObject(MemDC, OldBmp));
	::DeleteDC(MemDC);

	if (bUseFlippedBmp)
	{
		::DeleteObject(SelectObject(XFlippedHDC, OldXFlippedBmp));
		::DeleteObject(SelectObject(YFlippedHDC, OldYFlippedBmp));
		::DeleteObject(SelectObject(XYFlippedHDC, OldXYFlippedBmp));

		::DeleteDC(XFlippedHDC);
		::DeleteDC(YFlippedHDC);
		::DeleteDC(XYFlippedHDC);
	}

}

void CBitmap::FlipXY(bool flipX, bool flipY)
{
	if (!IsValid()) return;
	if (!BitmapInfo) return;

	// DC �� ������ �ȼ� ��ġ�� ��Ÿ���� ����
	int32 targetPixelX = 0, targetPixelY = 0;

	bIsFlippedX = flipX;
	bIsFlippedY = flipY;

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
