#pragma once
#include "Block.h"

// Ό³Έν :
class ARedHouse : public ABlock
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	ARedHouse();
	~ARedHouse();

	// delete Function
	ARedHouse(const ARedHouse& _Other) = delete;
	ARedHouse(ARedHouse&& _Other) noexcept = delete;
	ARedHouse& operator=(const ARedHouse& _Other) = delete;
	ARedHouse& operator=(ARedHouse&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

