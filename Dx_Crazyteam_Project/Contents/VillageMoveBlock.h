#pragma once
#include "Block.h"
#include "MoveObject.h"
#include "BreakObject.h"

// Ό³Έν :
class AVillageMoveBlock : public ABlock, public UMoveObject, public UBreakObject
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	AVillageMoveBlock();
	~AVillageMoveBlock();

	// delete Function
	AVillageMoveBlock(const AVillageMoveBlock& _Other) = delete;
	AVillageMoveBlock(AVillageMoveBlock&& _Other) noexcept = delete;
	AVillageMoveBlock& operator=(const AVillageMoveBlock& _Other) = delete;
	AVillageMoveBlock& operator=(AVillageMoveBlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

