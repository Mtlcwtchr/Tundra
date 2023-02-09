// Copyright Epic Games, Inc. All Rights Reserved.

#include "TundraGameMode.h"
#include "TundraPlayerController.h"
#include "TundraPlayerPawn.h"
#include "UObject/ConstructorHelpers.h"

ATundraGameMode::ATundraGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATundraPlayerController::StaticClass();

	DefaultPawnClass = ATundraPlayerPawn::StaticClass();
}