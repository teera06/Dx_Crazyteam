#pragma once
#include "Block.h"
#include "BreakObject.h"
#include "MoveObject.h"

// Ό³Έν :
class ACampHpBlock : public ABlock, public UBreakObject, public UMoveObject
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	ACampHpBlock();
	~ACampHpBlock();

	// delete Function
	ACampHpBlock(const ACampHpBlock& _Other) = delete;
	ACampHpBlock(ACampHpBlock&& _Other) noexcept = delete;
	ACampHpBlock& operator=(const ACampHpBlock& _Other) = delete;
	ACampHpBlock& operator=(ACampHpBlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

