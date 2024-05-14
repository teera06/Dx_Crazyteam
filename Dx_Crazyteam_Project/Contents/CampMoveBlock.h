#pragma once
#include "MoveBlock.h"

// Ό³Έν :
class ACampMoveBlock : public AMoveBlock
{
	GENERATED_BODY(AMoveBlock)
public:
	// constructor destructor
	ACampMoveBlock();
	~ACampMoveBlock();

	// delete Function
	ACampMoveBlock(const ACampMoveBlock& _Other) = delete;
	ACampMoveBlock(ACampMoveBlock&& _Other) noexcept = delete;
	ACampMoveBlock& operator=(const ACampMoveBlock& _Other) = delete;
	ACampMoveBlock& operator=(ACampMoveBlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

