#pragma once
#include "Block.h"

const int dy[] = { -1,0,1,0 };
const int dx[] = { 0,1,0,-1 };

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

	void StateInit();
	void NoneBegin();
	void NoneTick(float _DeltaTime);
	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleExit();
	void PushBegin();
	void PushTick(float _DeltaTime);
	void PushExit();
	void EndBegin();
	void EndTick(float _DeltaTime);
	void EndExit();

	UStateManager State;

	bool IsPush = false;
	float MoveSpeed = 100.f;
	float MoveCompleteTime = 0.4f;
	float AccTime = 0.f;

	int ny = 0;
	int nx = 0;

	ECADir MoveDir = ECADir::None;
	POINT PlayerIndex = { 0,0 };

private:

};

