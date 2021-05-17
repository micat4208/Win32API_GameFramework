#include "SpriteInfo.h"

#include "Framework/Bitmap/Bitmap.h"

FSpriteInfo::FSpriteInfo()
{
	LoadedBitmap = nullptr;
	SpriteDrawType = ESpriteDrawType::Hide;
	CRTransparent = RGB(0, 0, 0);
	DWRop = SRCCOPY;
	DrawPivot = FVector::OneVector() * 0.5f;
	LoadedSpriteImageSize = CropLT = SpriteImageSize = FVector::ZeroVector();
}

void FSpriteInfo::InitializeSpriteInfo(
	tstring imagePath, 
	ESpriteDrawType spriteDrawType, 
	FVector imageSize)
{
	// ��������Ʈ �̹��� �ε�
	LoadedBitmap = CBitmap::LoadBmp(NewObject<CBitmap>(), imagePath);

	// ��������Ʈ �̹��� ���� ������ ����
	if (LoadedBitmap)
		LoadedSpriteImageSize = LoadedBitmap->GetSize();

	// ��������Ʈ �׸��� ��� ����
	SpriteDrawType = spriteDrawType;

	// �׷��� �̹��� ������ ����
	SpriteImageSize = (imageSize == USE_LOADED_SIZE) ? LoadedSpriteImageSize : imageSize;
}

void FSpriteInfo::Release()
{
	super::Release();
	CObject::DeleteObject(LoadedBitmap);
}

HDC FSpriteInfo::GetDC() const
{
	return (IsValid() ? LoadedBitmap->GetDC() : nullptr);
}

bool FSpriteInfo::IsValid() const
{
	return (!LoadedBitmap ? false : LoadedBitmap->IsValid());
}
