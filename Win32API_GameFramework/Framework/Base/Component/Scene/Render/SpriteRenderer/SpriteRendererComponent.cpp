#include "SpriteRendererComponent.h"

#include "Framework/Bitmap/Bitmap.h"

CSpriteRendererComponent::CSpriteRendererComponent()
{
	DrawSpriteInfo = nullptr;
	bIsFlippedX = bIsFlippedY = false;
}

void CSpriteRendererComponent::Render(HDC hdc)
{
	super::Render(hdc);

	if (DrawSpriteInfo == nullptr) return;
	if (!DrawSpriteInfo->IsValid()) return;
	if (DrawSpriteInfo->SpriteDrawType == ESpriteDrawType::Hide) return;

	// 그려질 이미지 크기를 얻습니다.
	/// - 컴포넌트의 크기를 적용시킵니다.
	FVector drawSpriteImageSize = FVector(
		DrawSpriteInfo->SpriteImageSize.X * RelativeScale.X,
		DrawSpriteInfo->SpriteImageSize.Y * RelativeScale.Y);


	// 피벗을 기준으로 나눈 좌측 상단 사각형 크기를 얻습니다.
	/// - (그리기 시작 위치를 얻기 위하여 사용됩니다.)
	/// ┌───┬───┐
	/// │ 1 │ 2 │ 이 사각형에서 1 번 사각형 크기를 얻습니다.
	/// ├─pivot─┤
	/// │ 3 │ 4 │
	/// └───┴───┘
	FVector ltOfPivotRectSize = FVector(
		drawSpriteImageSize.X * DrawSpriteInfo->DrawPivot.X,
		drawSpriteImageSize.Y * DrawSpriteInfo->DrawPivot.Y);

	// 스프라이트 이미지를 그릴 좌측 상단 위치를 얻습니다.
	/// - 컴포넌트 위치를 피벗의 위치이므로, 피벗을 기준으로 나눈 좌측 상단 사각형 크기를 빼서
	///   그리기 시작 위치를 얻습니다.
	FVector drawStartLT = GetComponentPosition() - ltOfPivotRectSize;

	// 카메라 위치를 적용시킵니다.
	drawStartLT = ToCameraPosition(drawStartLT);

	switch (DrawSpriteInfo->SpriteDrawType)
	{
		case ESpriteDrawType::UseTransparentBlt :
		{
			// 이미지를 그립니다.
			TransparentBlt(hdc,
				// 이미지를 그리기 시작할 위치
				drawStartLT.X, drawStartLT.Y,

				// 그려질 이미지 크기
				drawSpriteImageSize.X, drawSpriteImageSize.Y,

				// 이미지 핸들
				DrawSpriteInfo->GetDC(),

				// 원본 이미지의 자르기 시작할 X, Y 위치
				DrawSpriteInfo->CropLT.X, DrawSpriteInfo->CropLT.Y,

				// 원본 이미지에서 잘라낼 너비, 높이
				DrawSpriteInfo->SpriteImageSize.X, DrawSpriteInfo->SpriteImageSize.Y,

				DrawSpriteInfo->CRTransparent);
			break;
		}
		case ESpriteDrawType::UseStretchBlt :
		{
			// 이미지를 그립니다.
			StretchBlt(hdc,
				// 이미지를 그리기 시작할 위치
				drawStartLT.X, drawStartLT.Y,

				// 그려질 이미지 크기
				drawSpriteImageSize.X, drawSpriteImageSize.Y,

				// 이미지 핸들
				DrawSpriteInfo->GetDC(),

				// 원본 이미지의 자르기 시작할 X, Y 위치
				DrawSpriteInfo->CropLT.X, DrawSpriteInfo->CropLT.Y,

				// 원본 이미지에서 잘라낼 너비, 높이
				DrawSpriteInfo->SpriteImageSize.X, DrawSpriteInfo->SpriteImageSize.Y,

				DrawSpriteInfo->DWRop);

			break;
		}

	}


}

void CSpriteRendererComponent::FlipXY(bool flipX, bool flipY)
{
	if (!DrawSpriteInfo) return;
	if (!DrawSpriteInfo->IsValid()) return;

	bIsFlippedX = DrawSpriteInfo->GetLoadedBitmap()->bIsFlippedX = flipX;
	bIsFlippedY = DrawSpriteInfo->GetLoadedBitmap()->bIsFlippedY = flipY;

}
