#pragma once
#include "Block.h"
#include "MoveObject.h"
#include "BreakObject.h"

// Ό³Έν :
class VillageMoveBlock : public ABlock, public UMoveObject, public UBreakObject
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	VillageMoveBlock();
	~VillageMoveBlock();

	// delete Function
	VillageMoveBlock(const VillageMoveBlock& _Other) = delete;
	VillageMoveBlock(VillageMoveBlock&& _Other) noexcept = delete;
	VillageMoveBlock& operator=(const VillageMoveBlock& _Other) = delete;
	VillageMoveBlock& operator=(VillageMoveBlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

