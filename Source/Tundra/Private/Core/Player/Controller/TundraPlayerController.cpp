// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tundra/Public/Core/Player/Controller/TundraPlayerController.h"
#include "Tundra/Public/Core/Player/Strategy/FCameraUpdateStrategyRTS.h"
#include "Engine/World.h"
#include "Tundra/Public/Core/Player/TundraPlayerPawn.h"

ATundraPlayerController::ATundraPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	CameraUpdateDelay = 2.4f;

	CameraMoveThreshold = FVector(100.0f, 100.0f, 0.0f);
	CameraMoveVelocity = 20.0f;
	CameraMoveVelocityAnchoredModifier = 10.0f;

	CameraUpdateStrategyFree = new FCameraUpdateStrategyFreeRTS(this);
	CameraUpdateStrategyFree->SetMoveVelocity(CameraMoveVelocity);
	CameraUpdateStrategyFree->SetReactThresholdVector(CameraMoveThreshold);
	
	CameraUpdateStrategyAnchored = new FCameraUpdateStrategyAnchoredRTS(this);
	CameraUpdateStrategyAnchored->SetMoveVelocity(CameraMoveVelocity);
	CameraUpdateStrategyAnchored->SetReactThresholdVector(CameraMoveThreshold);
	CameraUpdateStrategyAnchored->SetMoveVelocityModifier(CameraMoveVelocityAnchoredModifier);

	CameraUpdateStrategyCurrent = CameraUpdateStrategyFree;
}

void ATundraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if(!bCameraUpdateDelayed)
	{
		CameraUpdateStrategyCurrent->UpdateCameraPosition(DeltaTime);
	}
	else
	{
		TimePassed += DeltaTime;
		if(TimePassed >= CameraUpdateDelay)
		{
			bCameraUpdateDelayed = 0;
		}
	}
}

void ATundraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetCameraAnchor", IE_Pressed, this, &ATundraPlayerController::SetupCameraAnchor);
	InputComponent->BindAction("SetCameraAnchor", IE_Released, this, &ATundraPlayerController::ReleaseCameraAnchor);

	InputComponent->BindAxis("Zoom", this, &ATundraPlayerController::Zoom);
}

void ATundraPlayerController::SetupCameraAnchor()
{
	FHitResult TraceHitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
	const FVector CameraAnchor = TraceHitResult.Location;
	CameraUpdateStrategyAnchored->SetAnchorWorldPosition(CameraAnchor);
	CameraUpdateStrategyCurrent = CameraUpdateStrategyAnchored;
}

void ATundraPlayerController::ReleaseCameraAnchor()
{
	CameraUpdateStrategyCurrent = CameraUpdateStrategyFree;
	CameraUpdateStrategyAnchored->SetAnchorWorldPosition(FVector::ZeroVector);
	bCameraUpdateDelayed = 1;
}

void ATundraPlayerController::Zoom(float Value)
{
	Cast<ATundraPlayerPawn>(GetPawn())->AddZoomInput(Value);
}
