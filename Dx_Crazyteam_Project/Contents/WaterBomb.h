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
		State.ChangeState("Create");
		return;
	}

	//inline bool IsBomb() const
	//{
	//	return b_Bomb;
	//}

	/// <summary>
	/// 물줄기에 닿으면,
	/// </summary>
	/// <param name="_Val"></param>
	inline void SetWaterToBomg(bool _Val)
	{
		b_WaterToBomb = _Val;
	}

	void SetToken(int _Set) { WaterBomb_Token = _Set; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	int Bomb_MilliSecond = 0;
	int Bomb_Second = 0;

	int Sub_MilliSecond = 0;
	int Sub_Second = 0;

	bool OtherCreate = false;
	
	float GetCreateTime();

	int WaterBomb_Token = 0;
	int WaterCourse_Token = 0;
	static bool SetWaterCourseToken;

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

	//USpriteRenderer* Renderer = nullptr;
	float LifeTime = 0.0f; // ++DeltaTime
	float BombTime = 2.0f; // 2.0
	float ServerBombTime = 0.0f;
	bool b_WaterToBomb = false;
	bool b_ServerBomb = false;


};

