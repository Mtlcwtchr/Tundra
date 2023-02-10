// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tundra/Public/Core/Player/Controller/TundraPlayerController.h"
#include "Tundra/Public/Core/Player/TundraPlayerPawn.h"
#include "Tundra/Public/Core/Player/Strategy/FTundraPlayerPawnNavStrategy.h"
#include "Engine/World.h"

ATundraPlayerController::ATundraPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	PawnStaticTime = 0.6f;

	PawnVelocity = 1.0f;
	PawnVelocityZoomFactor = 0.01f;

	PawnNavStrategyByScreenBorders = new FTundraPlayerPawnNavStrategyByScreenBorders(this);
	PawnNavStrategyByScreenBorders->SetOffsets(100.0f, 100.0f);
	
	PawnNavStrategyByAnchor = new FTundraPlayerPawnNavStrategyByAnchor(this);

	PawnNavStrategy = PawnNavStrategyByScreenBorders;
}

void ATundraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	if(!bPawnForcedStatic)
	{
		GetPawn()->AddMovementInput(
			PawnNavStrategy->GetNavVector(),
			PawnVelocity * Cast<ATundraPlayerPawn>(GetPawn())->GetArmLength()  * PawnVelocityZoomFactor);
	}
	else
	{
		TimePassed += DeltaTime;
		if(TimePassed >= PawnStaticTime)
		{
			TimePassed = 0;
			bPawnForcedStatic = 0;
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
	PawnNavStrategyByAnchor->SetAnchorVector(CameraAnchor);
	PawnNavStrategy = PawnNavStrategyByAnchor;
}

void ATundraPlayerController::ReleaseCameraAnchor()
{
	PawnNavStrategy = PawnNavStrategyByScreenBorders;
	PawnNavStrategyByAnchor->SetAnchorVector(FVector::ZeroVector);
	bPawnForcedStatic = 1;
}

void ATundraPlayerController::Zoom(float Value)
{
	Cast<ATundraPlayerPawn>(GetPawn())->AddZoomInput(Value);
}
