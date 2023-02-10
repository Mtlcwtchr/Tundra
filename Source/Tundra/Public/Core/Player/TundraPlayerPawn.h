// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TundraPlayerPawn.generated.h"

UCLASS(Blueprintable)
class ATundraPlayerPawn : public APawn
{
	GENERATED_BODY()

	float OrderedZoomInput;
	uint8 bZoomInputConsumed : 1;

	float MinArmLength;
	float MaxArmLength;

	float MinArmPitch;
	float MaxArmPitch;

public:
	ATundraPlayerPawn();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Getters)
	FORCEINLINE class USphereComponent* GetCollisionSphere() { return CollisionSphere; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Getters)
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Getters)
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Getters)
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Getters)
	FORCEINLINE float GetDefaultArmLength() const { return DefaultArmLength;}
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Getters)
	FORCEINLINE FRotator GetDefaultCameraRotation() const { return DefaultCameraRotation;}
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Getters)
	FORCEINLINE float GetZoomSpeed() const { return ZoomSpeed;}
	
	virtual void AddZoomInput(float Value);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Root, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionSphere;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float DefaultArmLength;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FRotator DefaultCameraRotation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float ZoomSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float ZoomRotationSpeed;

	virtual uint8 ConsumeZoomInput(float& Value);
};

