#pragma once
#include "Block.h"

// Ό³Έν :
class ABlueHouse : public ABlock
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	ABlueHouse();
	~ABlueHouse();

	// delete Function
	ABlueHouse(const ABlueHouse& _Other) = delete;
	ABlueHouse(ABlueHouse&& _Other) noexcept = delete;
	ABlueHouse& operator=(const ABlueHouse& _Other) = delete;
	ABlueHouse& operator=(ABlueHouse&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

