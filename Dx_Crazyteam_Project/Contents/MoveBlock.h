#pragma once
#include "Block.h"

// Ό³Έν :
class AMoveBlock : public ABlock
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	AMoveBlock();
	~AMoveBlock();

	// delete Function
	AMoveBlock(const AMoveBlock& _Other) = delete;
	AMoveBlock(AMoveBlock&& _Other) noexcept = delete;
	AMoveBlock& operator=(const AMoveBlock& _Other) = delete;
	AMoveBlock& operator=(AMoveBlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

