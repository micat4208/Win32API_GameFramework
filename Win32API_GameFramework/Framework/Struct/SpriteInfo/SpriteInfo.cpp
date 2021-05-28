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
	FVector imageSize,
	bool bUseFlip)
{
	// ��������Ʈ �̹��� �ε�
	LoadedBitmap = CBitmap::LoadBmp(NewObject<CBitmap>(), imagePath, bUseFlip);

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
	LoadedBitmap = nullptr;
}

void FSpriteInfo::MakeSpriteInfos(
	vector<FSpriteInfo*>&		outSpriteInfos, 
	const vector<tstring>&		imagePaths, 
	ESpriteDrawType				spriteDrawType, 
	FVector						pivot, 
	COLORREF					crTransparent, 
	DWORD						dwRop)
{
	for (int32 i = 0; i < imagePaths.size(); ++i)
	{
		FSpriteInfo* newSpriteInfo = CObject::NewObject<FSpriteInfo>();
		newSpriteInfo->InitializeSpriteInfo(imagePaths[i], spriteDrawType);
		newSpriteInfo->DrawPivot = pivot;
		newSpriteInfo->CRTransparent = crTransparent;
		newSpriteInfo->DWRop = dwRop;

		outSpriteInfos.push_back(newSpriteInfo);
	}
}

HDC FSpriteInfo::GetDC() const
{
	return (IsValid() ? LoadedBitmap->GetDC() : nullptr);
}

bool FSpriteInfo::IsValid() const
{
	return (!LoadedBitmap ? false : LoadedBitmap->IsValid());
}
