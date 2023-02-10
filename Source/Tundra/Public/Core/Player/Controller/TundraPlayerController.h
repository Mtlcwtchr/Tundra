// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TundraPlayerController.generated.h"

UCLASS()
class ATundraPlayerController : public APlayerController
{
	GENERATED_BODY()

	float PawnVelocity;
	float PawnVelocityZoomFactor;
	
	class FTundraPlayerPawnNavStrategyByScreenBorders* PawnNavStrategyByScreenBorders;
	class FTundraPlayerPawnNavStrategyByAnchor* PawnNavStrategyByAnchor;
	
	class FTundraPlayerPawnNavStrategy* PawnNavStrategy;
	
	uint8 bPawnForcedStatic : 1;
	float PawnStaticTime;
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


