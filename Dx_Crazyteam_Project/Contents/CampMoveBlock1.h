#pragma once
#include "Block.h"
#include "MoveObject.h"
#include "BreakObject.h"

// Ό³Έν :
class ACampMoveBlock1 : public ABlock, public UMoveObject, public UBreakObject
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	ACampMoveBlock1();
	~ACampMoveBlock1();

	// delete Function
	ACampMoveBlock1(const ACampMoveBlock1& _Other) = delete;
	ACampMoveBlock1(ACampMoveBlock1&& _Other) noexcept = delete;
	ACampMoveBlock1& operator=(const ACampMoveBlock1& _Other) = delete;
	ACampMoveBlock1& operator=(ACampMoveBlock1&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

