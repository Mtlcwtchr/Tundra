// Copyright Epic Games, Inc. All Rights Reserved.

#include "TundraPlayerController.h"
#include "Engine/World.h"

ATundraPlayerController::ATundraPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	CameraMoveThreshold = FVector(100.0f, 100.0f, 0.0f);
	CameraMoveVelocity = 20.0f;
	CameraMoveVelocityAnchoredModifier = 10.0f;

	CameraUpdateStrategyFree = new FRTSCameraUpdateStrategyFree(this);
	CameraUpdateStrategyFree->SetMoveVelocity(CameraMoveVelocity);
	CameraUpdateStrategyFree->SetReactThresholdVector(CameraMoveThreshold);
	
	CameraUpdateStrategyAnchored = new FRTSCameraUpdateStrategyAnchored(this);
	CameraUpdateStrategyAnchored->SetMoveVelocity(CameraMoveVelocity);
	CameraUpdateStrategyAnchored->SetReactThresholdVector(CameraMoveThreshold);
	CameraUpdateStrategyAnchored->SetMoveVelocityModifier(CameraMoveVelocityAnchoredModifier);

	CameraUpdateStrategyCurrent = CameraUpdateStrategyFree;
}

void ATundraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CameraUpdateStrategyCurrent->UpdateCameraPosition(DeltaTime);
}

void ATundraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetCameraAnchor", IE_Pressed, this, &ATundraPlayerController::SetupCameraAnchor);
	InputComponent->BindAction("SetCameraAnchor", IE_Released, this, &ATundraPlayerController::ReleaseCameraAnchor);
}

void ATundraPlayerController::SetupCameraAnchor()
{
	FHitResult TraceHitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
	CameraAnchor = TraceHitResult.Location;
	CameraUpdateStrategyAnchored->SetAnchorWorldPosition(CameraAnchor);
	CameraUpdateStrategyCurrent = CameraUpdateStrategyAnchored;
}

void ATundraPlayerController::ReleaseCameraAnchor()
{
	CameraUpdateStrategyCurrent = CameraUpdateStrategyFree;
	CameraUpdateStrategyAnchored->SetAnchorWorldPosition(FVector::ZeroVector);
}
