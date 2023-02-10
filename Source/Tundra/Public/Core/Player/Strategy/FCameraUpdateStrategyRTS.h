#pragma once

class FCameraUpdateStrategyRTS
{
	class ATundraPlayerController* PlayerController;
	
public:
	explicit FCameraUpdateStrategyRTS(ATundraPlayerController* PlayerController);
	virtual ~FCameraUpdateStrategyRTS();
	
	virtual void UpdateCameraPosition(float DeltaTime) = 0;
	
	void SetReactThresholdVector(FVector Value);
	void SetMoveVelocity(float Value);

protected:
	FVector ReactThresholdVector;
	float MoveVelocity;

	class ATundraPlayerController* GetPlayerController() const { return PlayerController; }
};

class FCameraUpdateStrategyFreeRTS final : public FCameraUpdateStrategyRTS
{
public:
	explicit FCameraUpdateStrategyFreeRTS(ATundraPlayerController* PlayerController);
	
	virtual void UpdateCameraPosition(float DeltaTime) override;
};

class FCameraUpdateStrategyAnchoredRTS final : public FCameraUpdateStrategyRTS
{
	float MoveVelocityModifier;
	FVector AnchorWorldPosition;
	
public:
	explicit FCameraUpdateStrategyAnchoredRTS(ATundraPlayerController* PlayerController);
	
	virtual void UpdateCameraPosition(float DeltaTime) override;

	void SetMoveVelocityModifier(float Value);
	void SetAnchorWorldPosition(FVector Value);
};
