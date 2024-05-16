#pragma once
#include "Block.h"
#include "MoveObject.h"
#include "BreakObject.h"

// Ό³Έν :
class ACampMoveBlock : public ABlock, public UMoveObject, public UBreakObject
{
	GENERATED_BODY(ABlock)
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

