// Copyright Epic Games, Inc. All Rights Reserved.

#include "TundraGameMode.h"

#include "Public/Core/Player/TundraPlayerPawn.h"
#include "Public/Core/Player/Controller/TundraPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ATundraGameMode::ATundraGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATundraPlayerController::StaticClass();
	DefaultPawnClass = ATundraPlayerPawn::StaticClass();
}