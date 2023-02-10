// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tundra/Public/Core/Player/TundraPlayerPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ATundraPlayerPawn::ATundraPlayerPawn()
{
	ZoomSpeed = 100;
	ZoomRotationSpeed = 10;

	MinArmLength = 400.f;
	MaxArmLength = 2600.f;

	MinArmPitch = -90.f;
	MaxArmPitch = -30.f;
	
	DefaultArmLength = 800.f;
	DefaultCameraRotation = FRotator(-60.f, 0.f, 0.f);
	
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SetRootComponent(CollisionSphere);
	CollisionSphere->InitSphereRadius(32.0f);
	CollisionSphere->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = DefaultArmLength;
	CameraBoom->SetRelativeRotation(DefaultCameraRotation);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATundraPlayerPawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    const FVector InputVector = ConsumeMovementInputVector();
	AddActorLocalOffset(InputVector);

	float ZoomInput;
	if(ConsumeZoomInput(ZoomInput))
	{
		const float AddLength = ZoomSpeed * -ZoomInput;
		const float NewArmLength = GetCameraBoom()->TargetArmLength + AddLength;
		if(NewArmLength >= MinArmLength && NewArmLength <= MaxArmLength)
		{
			GetCameraBoom()->TargetArmLength = NewArmLength;
		}

		const float AddPitch = ZoomRotationSpeed * -ZoomInput;
		const float NewArmPitch = GetCameraBoom()->GetRelativeRotation().Pitch + AddPitch;
		if(NewArmPitch >= MinArmPitch && NewArmPitch <= MaxArmPitch)
		{
			GetCameraBoom()->GetRelativeRotation().Add(AddPitch, 0.0f, 0.0f);
		}
	}

	if (CursorToWorld != nullptr)
	{
		if (const APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			const FVector CursorFV = TraceHitResult.ImpactNormal;
			const FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void ATundraPlayerPawn::AddZoomInput(float Value)
{
	OrderedZoomInput = Value;
	bZoomInputConsumed = 0;
}

uint8 ATundraPlayerPawn::ConsumeZoomInput(float& Value)
{
	if(!bZoomInputConsumed)
	{
		Value = OrderedZoomInput;
		OrderedZoomInput = 0;
		bZoomInputConsumed = 1;
		return 1;
	}

	return 0;
}
