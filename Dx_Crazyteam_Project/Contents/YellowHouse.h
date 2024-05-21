#pragma once
#include "Block.h"

// Ό³Έν :
class YellowHouse : public ABlock
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	YellowHouse();
	~YellowHouse();

	// delete Function
	YellowHouse(const YellowHouse& _Other) = delete;
	YellowHouse(YellowHouse&& _Other) noexcept = delete;
	YellowHouse& operator=(const YellowHouse& _Other) = delete;
	YellowHouse& operator=(YellowHouse&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

