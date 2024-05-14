#pragma once
#include "Block.h"

class USpriteRenderer;
class AWaterBomb : public ABlock
{
	GENERATED_BODY(ABlock)

public:
	// constructor destructor
	AWaterBomb();
	~AWaterBomb();

	// delete Function
	AWaterBomb(const AWaterBomb& _Other) = delete;
	AWaterBomb(AWaterBomb&& _Other) noexcept = delete;
	AWaterBomb& operator=(const AWaterBomb& _Other) = delete;
	AWaterBomb& operator=(AWaterBomb&& _Other) noexcept = delete;

	inline void CreateWaterBomb()
	{
		State.ChangeState("Bomb");
		return;
	}

	inline bool IsBomb() const
	{
		return b_Bomb;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void StateInit();
	void CreateAnimation();

	void NoneBegin();
	void NoneTick(float _DeltaTime);
	void CreateBegin();
	void CreateTick(float _DeltaTime);
	void CreateExit();
	void BombBegin();
	void BombTick(float _DeltaTime);
	void BombExit();

	UStateManager State;
	USpriteRenderer* WaterCourseRender = nullptr;
	float LifeTime = 0.0f;
	bool b_Bomb = false;
};

