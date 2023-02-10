// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TundraPlayerController.generated.h"

UCLASS()
class ATundraPlayerController : public APlayerController
{
	GENERATED_BODY()

	FVector CameraMoveThreshold;

	float CameraMoveVelocity;
	float CameraMoveVelocityAnchoredModifier;

	class FCameraUpdateStrategyFreeRTS* CameraUpdateStrategyFree;
	class FCameraUpdateStrategyAnchoredRTS* CameraUpdateStrategyAnchored;

	class FCameraUpdateStrategyRTS* CameraUpdateStrategyCurrent;

	
	uint8 bCameraUpdateDelayed : 1;
	float CameraUpdateDelay;
	float TimePassed;

public:
	ATundraPlayerController();

protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void SetupCameraAnchor();
	void ReleaseCameraAnchor();

	void Zoom(float Value);;
};


