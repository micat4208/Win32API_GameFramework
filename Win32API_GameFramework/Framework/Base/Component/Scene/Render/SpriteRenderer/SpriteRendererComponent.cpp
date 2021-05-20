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

	// �׷��� �̹��� ũ�⸦ ����ϴ�.
	/// - ������Ʈ�� ũ�⸦ �����ŵ�ϴ�.
	FVector drawSpriteImageSize = FVector(
		DrawSpriteInfo->SpriteImageSize.X * RelativeScale.X,
		DrawSpriteInfo->SpriteImageSize.Y * RelativeScale.Y);


	// �ǹ��� �������� ���� ���� ��� �簢�� ũ�⸦ ����ϴ�.
	/// - (�׸��� ���� ��ġ�� ��� ���Ͽ� ���˴ϴ�.)
	/// ������������������
	/// �� 1 �� 2 �� �� �簢������ 1 �� �簢�� ũ�⸦ ����ϴ�.
	/// ����pivot����
	/// �� 3 �� 4 ��
	/// ������������������
	FVector ltOfPivotRectSize = FVector(
		drawSpriteImageSize.X * DrawSpriteInfo->DrawPivot.X,
		drawSpriteImageSize.Y * DrawSpriteInfo->DrawPivot.Y);

	// ��������Ʈ �̹����� �׸� ���� ��� ��ġ�� ����ϴ�.
	/// - ������Ʈ ��ġ�� �ǹ��� ��ġ�̹Ƿ�, �ǹ��� �������� ���� ���� ��� �簢�� ũ�⸦ ����
	///   �׸��� ���� ��ġ�� ����ϴ�.
	FVector drawStartLT = GetComponentPosition() - ltOfPivotRectSize;

	// ī�޶� ��ġ�� �����ŵ�ϴ�.
	drawStartLT = ToCameraPosition(drawStartLT);

	switch (DrawSpriteInfo->SpriteDrawType)
	{
		case ESpriteDrawType::UseTransparentBlt :
		{
			// �̹����� �׸��ϴ�.
			TransparentBlt(hdc,
				// �̹����� �׸��� ������ ��ġ
				drawStartLT.X, drawStartLT.Y,

				// �׷��� �̹��� ũ��
				drawSpriteImageSize.X, drawSpriteImageSize.Y,

				// �̹��� �ڵ�
				DrawSpriteInfo->GetDC(),

				// ���� �̹����� �ڸ��� ������ X, Y ��ġ
				DrawSpriteInfo->CropLT.X, DrawSpriteInfo->CropLT.Y,

				// ���� �̹������� �߶� �ʺ�, ����
				DrawSpriteInfo->SpriteImageSize.X, DrawSpriteInfo->SpriteImageSize.Y,

				DrawSpriteInfo->CRTransparent);
			break;
		}
		case ESpriteDrawType::UseStretchBlt :
		{
			// �̹����� �׸��ϴ�.
			StretchBlt(hdc,
				// �̹����� �׸��� ������ ��ġ
				drawStartLT.X, drawStartLT.Y,

				// �׷��� �̹��� ũ��
				drawSpriteImageSize.X, drawSpriteImageSize.Y,

				// �̹��� �ڵ�
				DrawSpriteInfo->GetDC(),

				// ���� �̹����� �ڸ��� ������ X, Y ��ġ
				DrawSpriteInfo->CropLT.X, DrawSpriteInfo->CropLT.Y,

				// ���� �̹������� �߶� �ʺ�, ����
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
