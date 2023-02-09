// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Camera/RTSCameraUpdateStrategy.h"
#include "GameFramework/PlayerController.h"
#include "TundraPlayerController.generated.h"

UCLASS()
class ATundraPlayerController : public APlayerController
{
	GENERATED_BODY()

	FVector CameraAnchor;

	FVector CameraMoveThreshold;
	
	float CameraMoveVelocity;
	float CameraMoveVelocityAnchoredModifier;

	class FRTSCameraUpdateStrategyFree* CameraUpdateStrategyFree;
	class FRTSCameraUpdateStrategyAnchored* CameraUpdateStrategyAnchored;

	class RTSCameraUpdateStrategy* CameraUpdateStrategyCurrent;

public:
	ATundraPlayerController();

protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void SetupCameraAnchor();
	void ReleaseCameraAnchor();
};


