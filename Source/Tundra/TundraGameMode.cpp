// Copyright Epic Games, Inc. All Rights Reserved.

#include "TundraGameMode.h"
#include "TundraPlayerController.h"
#include "TundraCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATundraGameMode::ATundraGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATundraPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}