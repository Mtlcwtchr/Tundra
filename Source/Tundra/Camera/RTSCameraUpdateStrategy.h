#pragma once
#include "Tundra/TundraPlayerController.h"

class RTSCameraUpdateStrategy
{
	class ATundraPlayerController* PlayerController;
	
public:
	explicit RTSCameraUpdateStrategy(ATundraPlayerController* PlayerController);
	virtual ~RTSCameraUpdateStrategy();
	
	virtual void UpdateCameraPosition(float DeltaTime) = 0;
	
	void SetReactThresholdVector(FVector Value);
	void SetMoveVelocity(float Value);

protected:
	FVector ReactThresholdVector;
	float MoveVelocity;

	class ATundraPlayerController* GetPlayerController() const { return PlayerController; }
};

class FRTSCameraUpdateStrategyFree final : public RTSCameraUpdateStrategy
{
public:
	explicit FRTSCameraUpdateStrategyFree(ATundraPlayerController* PlayerController);
	~FRTSCameraUpdateStrategyFree();
	
	virtual void UpdateCameraPosition(float DeltaTime) override;
};

class FRTSCameraUpdateStrategyAnchored final : public RTSCameraUpdateStrategy
{
	float MoveVelocityModifier;
	FVector AnchorWorldPosition;
	
public:
	explicit FRTSCameraUpdateStrategyAnchored(ATundraPlayerController* PlayerController);
	~FRTSCameraUpdateStrategyAnchored();
	
	virtual void UpdateCameraPosition(float DeltaTime) override;

	void SetMoveVelocityModifier(float Value);
	void SetAnchorWorldPosition(FVector Value);
};
