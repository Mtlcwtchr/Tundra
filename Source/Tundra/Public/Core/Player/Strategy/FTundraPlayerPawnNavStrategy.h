#pragma once

class FTundraPlayerPawnNavStrategy
{
public:
	explicit FTundraPlayerPawnNavStrategy(APlayerController* PlayerController);
	
	virtual FVector GetNavVector() = 0;
	
protected:
	class APlayerController* PlayerController;
};

class FTundraPlayerPawnNavStrategyByScreenBorders : public FTundraPlayerPawnNavStrategy
{

	float XOffset = 0.f;
	float YOffset = 0.f;
	
public:
	using FTundraPlayerPawnNavStrategy::FTundraPlayerPawnNavStrategy;
	
	FVector GetNavVector() override;
	void SetOffsets(float NewXOffset, float NewYOffset);
};

class FTundraPlayerPawnNavStrategyByAnchor : public FTundraPlayerPawnNavStrategy
{

	FVector Anchor = FVector::ZeroVector;

public:
	using FTundraPlayerPawnNavStrategy::FTundraPlayerPawnNavStrategy;
	
	FVector GetNavVector() override;
	void SetAnchorVector(FVector NewAnchor);
};