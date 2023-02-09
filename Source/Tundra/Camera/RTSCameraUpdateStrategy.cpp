#include "RTSCameraUpdateStrategy.h"

RTSCameraUpdateStrategy::RTSCameraUpdateStrategy(ATundraPlayerController* PlayerController)
{
	this->PlayerController = PlayerController;
	ReactThresholdVector = FVector::ZeroVector;
	MoveVelocity = 0.0f;
}

FRTSCameraUpdateStrategyFree::FRTSCameraUpdateStrategyFree(ATundraPlayerController* PlayerController) : RTSCameraUpdateStrategy(PlayerController)
{
}

FRTSCameraUpdateStrategyAnchored::FRTSCameraUpdateStrategyAnchored(ATundraPlayerController* PlayerController) : RTSCameraUpdateStrategy(PlayerController)
{
	MoveVelocityModifier = 0.0f;
}

RTSCameraUpdateStrategy::~RTSCameraUpdateStrategy()
{
	PlayerController = nullptr;
}

FRTSCameraUpdateStrategyFree::~FRTSCameraUpdateStrategyFree()
{
}

FRTSCameraUpdateStrategyAnchored::~FRTSCameraUpdateStrategyAnchored()
{
}

void RTSCameraUpdateStrategy::SetReactThresholdVector(FVector Value)
{
	ReactThresholdVector = Value;
}

void RTSCameraUpdateStrategy::SetMoveVelocity(float Value)
{
	MoveVelocity = Value;
}

void FRTSCameraUpdateStrategyFree::UpdateCameraPosition(float DeltaTime)
{
	float MouseX;
	float MouseY;
	if (GetPlayerController()->GetMousePosition(MouseX, MouseY))
	{
		const FVector2D ViewPortSize = GEngine->GameViewport->Viewport->GetSizeXY();
		const float YDir = FMath::Min(static_cast<float>(static_cast<int>((MouseX + ReactThresholdVector.X) / ViewPortSize.X)), 1.0f)  - FMath::Min(static_cast<float>(static_cast<int>(ReactThresholdVector.X / MouseX)), 1.0f);
		const float XDir = -FMath::Min(static_cast<float>(static_cast<int>((MouseY + ReactThresholdVector.Y) / ViewPortSize.Y)), 1.0f) + FMath::Min(static_cast<float>(static_cast<int>(ReactThresholdVector.Y / MouseY)), 1.0f);
		const FVector MovementDir = FVector(XDir, YDir, 0);
		GetPlayerController()->GetPawn()->AddMovementInput(MovementDir, MoveVelocity * DeltaTime);
	}
}

void FRTSCameraUpdateStrategyAnchored::UpdateCameraPosition(float DeltaTime)
{
	FHitResult TraceHitResult;
	GetPlayerController()->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
	const FVector MouseWorldLocation = TraceHitResult.Location;
	const FVector AnchoredOffset = MouseWorldLocation - AnchorWorldPosition;
	GetPlayerController()->GetPawn()->AddMovementInput(-AnchoredOffset.GetSafeNormal(FLT_EPSILON), MoveVelocity * MoveVelocityModifier * DeltaTime);
}

void FRTSCameraUpdateStrategyAnchored::SetMoveVelocityModifier(float Value)
{
	MoveVelocityModifier = Value;
}

void FRTSCameraUpdateStrategyAnchored::SetAnchorWorldPosition(FVector Value)
{
	AnchorWorldPosition = Value;
}
