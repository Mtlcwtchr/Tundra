#include "Tundra/Public/Core/Player/Strategy/FTundraPlayerPawnNavStrategy.h"

FTundraPlayerPawnNavStrategy::FTundraPlayerPawnNavStrategy(APlayerController* PlayerController)
{
	this->PlayerController = PlayerController;
}

FVector FTundraPlayerPawnNavStrategyByScreenBorders::GetNavVector()
{
	float MouseX;
	float MouseY;
	if (PlayerController->GetMousePosition(MouseX, MouseY))
	{
		const FVector2D ViewPortSize = GEngine->GameViewport->Viewport->GetSizeXY();
		const float YDir = FMath::Min(static_cast<float>(static_cast<int>((MouseX + XOffset) / ViewPortSize.X)), 1.0f)  - FMath::Min(static_cast<float>(static_cast<int>(XOffset / MouseX)), 1.0f);
		const float XDir = -FMath::Min(static_cast<float>(static_cast<int>((MouseY + YOffset) / ViewPortSize.Y)), 1.0f) + FMath::Min(static_cast<float>(static_cast<int>(YOffset / MouseY)), 1.0f);
		const FVector NavVector = FVector(XDir, YDir, 0);
		return NavVector;
	}
	
	return FVector::ZeroVector;
}

void FTundraPlayerPawnNavStrategyByScreenBorders::SetOffsets(float NewXOffset, float NewYOffset)
{
	this->XOffset = NewXOffset;
	this->YOffset = NewYOffset;
}

FVector FTundraPlayerPawnNavStrategyByAnchor::GetNavVector()
{
	FHitResult TraceHitResult;
	if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult))
	{
		const FVector MouseWorldLocation = TraceHitResult.Location;
		const FVector AnchoredOffset = MouseWorldLocation - Anchor;
		return -FVector(AnchoredOffset.X, AnchoredOffset.Y, 0.f).GetSafeNormal(FLT_EPSILON);
	}
	return FVector::ZeroVector;
}

void FTundraPlayerPawnNavStrategyByAnchor::SetAnchorVector(FVector NewAnchor)
{
	this->Anchor = NewAnchor;
}
