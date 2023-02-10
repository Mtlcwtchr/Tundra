#include "Tundra/Public/Core/Player/Strategy/FCameraUpdateStrategyRTS.h"
#include "Tundra/Public/Core/Player/Controller/TundraPlayerController.h"

FCameraUpdateStrategyRTS::FCameraUpdateStrategyRTS(ATundraPlayerController* PlayerController)
{
	this->PlayerController = PlayerController;
	ReactThresholdVector = FVector::ZeroVector;
	MoveVelocity = 0.0f;
}

FCameraUpdateStrategyFreeRTS::FCameraUpdateStrategyFreeRTS(ATundraPlayerController* PlayerController) : FCameraUpdateStrategyRTS(PlayerController)
{
}

FCameraUpdateStrategyAnchoredRTS::FCameraUpdateStrategyAnchoredRTS(ATundraPlayerController* PlayerController) : FCameraUpdateStrategyRTS(PlayerController)
{
	MoveVelocityModifier = 0.0f;
}

FCameraUpdateStrategyRTS::~FCameraUpdateStrategyRTS()
{
	PlayerController = nullptr;
}

void FCameraUpdateStrategyRTS::SetReactThresholdVector(FVector Value)
{
	ReactThresholdVector = Value;
}

void FCameraUpdateStrategyRTS::SetMoveVelocity(float Value)
{
	MoveVelocity = Value;
}

void FCameraUpdateStrategyFreeRTS::UpdateCameraPosition(float DeltaTime)
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

void FCameraUpdateStrategyAnchoredRTS::UpdateCameraPosition(float DeltaTime)
{
	FHitResult TraceHitResult;
	GetPlayerController()->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
	const FVector MouseWorldLocation = TraceHitResult.Location;
	const FVector AnchoredOffset = MouseWorldLocation - AnchorWorldPosition;
	GetPlayerController()->GetPawn()->AddMovementInput(-AnchoredOffset.GetSafeNormal(FLT_EPSILON), MoveVelocity * MoveVelocityModifier * DeltaTime);
}

void FCameraUpdateStrategyAnchoredRTS::SetMoveVelocityModifier(float Value)
{
	MoveVelocityModifier = Value;
}

void FCameraUpdateStrategyAnchoredRTS::SetAnchorWorldPosition(FVector Value)
{
	AnchorWorldPosition = Value;
}
