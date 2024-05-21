#pragma once
#include "Block.h"

// Ό³Έν :
class AYellowHouse : public ABlock
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	AYellowHouse();
	~AYellowHouse();

	// delete Function
	AYellowHouse(const AYellowHouse& _Other) = delete;
	AYellowHouse(AYellowHouse&& _Other) noexcept = delete;
	AYellowHouse& operator=(const AYellowHouse& _Other) = delete;
	AYellowHouse& operator=(AYellowHouse&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

