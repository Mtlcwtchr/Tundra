// Copyright Epic Games, Inc. All Rights Reserved.

#include "TundraPlayerController.h"
#include "Engine/World.h"

ATundraPlayerController::ATundraPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	CameraMoveThreshold = FVector2D(100, 100);
	CameraMoveVelocity = 20.0f;
}

void ATundraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if(bCameraAnchored)
	{
		UpdateCameraPositionAnchored(DeltaTime);
	}
	else
	{
		UpdateCameraPosition(DeltaTime);
	}
}

void ATundraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetCameraAnchor", IE_Pressed, this, &ATundraPlayerController::SetCameraAnchor);
	InputComponent->BindAction("SetCameraAnchor", IE_Released, this, &ATundraPlayerController::ReleaseCameraAnchor);
}

void ATundraPlayerController::SetCameraAnchor()
{
	FHitResult TraceHitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
	CameraAnchor = TraceHitResult.Location;
	bCameraAnchored = 1;
}

void ATundraPlayerController::ReleaseCameraAnchor()
{
	CameraAnchor = FVector::ZeroVector;
	bCameraAnchored = 0;
}

void ATundraPlayerController::UpdateCameraPosition(float DeltaTime) const
{
	float MouseX;
	float MouseY;
	if (GetMousePosition(MouseX, MouseY))
	{
		const FVector2D ViewPortSize = GEngine->GameViewport->Viewport->GetSizeXY();
		const float YDir = FMath::Min(static_cast<float>(static_cast<int>((MouseX + CameraMoveThreshold.X) / ViewPortSize.X)), 1.0f)  - FMath::Min(static_cast<float>(static_cast<int>(CameraMoveThreshold.X / MouseX)), 1.0f);
		const float XDir = -FMath::Min(static_cast<float>(static_cast<int>((MouseY + CameraMoveThreshold.Y) / ViewPortSize.Y)), 1.0f) + FMath::Min(static_cast<float>(static_cast<int>(CameraMoveThreshold.Y / MouseY)), 1.0f);
		const FVector MovementDir = FVector(XDir, YDir, 0);
		GetPawn()->AddMovementInput(MovementDir, CameraMoveVelocity * DeltaTime);
	}
}

void ATundraPlayerController::UpdateCameraPositionAnchored(float DeltaTime) const
{
	if(!bCameraAnchored ||
		CameraAnchor == FVector::ZeroVector)
	{
		return;
	}

	FHitResult TraceHitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
	const FVector MouseWorldLocation = TraceHitResult.Location;
	const FVector AnchoredOffset = MouseWorldLocation - CameraAnchor;
	GetPawn()->AddMovementInput(-AnchoredOffset.GetSafeNormal(0.001), CameraMoveVelocity * DeltaTime);
}

