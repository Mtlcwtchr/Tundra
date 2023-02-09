// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TundraPlayerController.generated.h"

UCLASS()
class ATundraPlayerController : public APlayerController
{
	GENERATED_BODY()

	FVector CameraAnchor;

	FVector2D CameraMoveThreshold;
	
	float CameraMoveVelocity;

public:
	ATundraPlayerController();

protected:
	uint32 bCameraAnchored : 1;

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void SetCameraAnchor();
	void ReleaseCameraAnchor();
	
	void UpdateCameraPosition(float DeltaTime) const;
	void UpdateCameraPositionAnchored(float DeltaTime) const;
};


