#pragma once
#include "Block.h"

// Ό³Έν :
class ADummyBlock : public ABlock
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	ADummyBlock();
	~ADummyBlock();

	// delete Function
	ADummyBlock(const ADummyBlock& _Other) = delete;
	ADummyBlock(ADummyBlock&& _Other) noexcept = delete;
	ADummyBlock& operator=(const ADummyBlock& _Other) = delete;
	ADummyBlock& operator=(ADummyBlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

