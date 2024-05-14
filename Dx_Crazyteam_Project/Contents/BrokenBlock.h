#pragma once
#include "Block.h"
class ABrokenBlock : public ABlock
{
	GENERATED_BODY(ABlock)

public:
	// constructor destructor
	ABrokenBlock();
	~ABrokenBlock();

	// delete Function
	ABrokenBlock(const ABrokenBlock& _Other) = delete;
	ABrokenBlock(ABrokenBlock&& _Other) noexcept = delete;
	ABrokenBlock& operator=(const ABrokenBlock& _Other) = delete;
	ABrokenBlock& operator=(ABrokenBlock&& _Other) noexcept = delete;

	void CreateBlock()
	{
		State.ChangeState("Idle");
		return;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void StateInit();
	void CreateAnimation();

	void NoneBegin();
	void NoneTick(float _DeltaTime);
	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleExit();
	void BreakBegin();
	void BreakTick(float _DeltaTime);
	void BreakExit();
	void EndBegin();
	void EndTick(float _DeltaTime);
	void EndExit();

	UStateManager State;

	bool IsBreak = false;

	float BreakBlockTime = 0.25f;
	float AccTime = 0.f;

	bool BlinkOn = false;

	float BlinkTime = 0.05f;
	float AccBlinkTime = 0.f;
};

