#pragma once
#include "Block.h"

// Ό³Έν :
class BlueHouse : public ABlock
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	BlueHouse();
	~BlueHouse();

	// delete Function
	BlueHouse(const BlueHouse& _Other) = delete;
	BlueHouse(BlueHouse&& _Other) noexcept = delete;
	BlueHouse& operator=(const BlueHouse& _Other) = delete;
	BlueHouse& operator=(BlueHouse&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

