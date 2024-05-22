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

	inline ACAGameMode* GetWaterBombGameMode()
	{
		return WaterBombThisGameMode;
	}

	void SetWaterBombToken(int _Set) { WaterBomb_Token = _Set; }
	void SetWaterCourseToken(int _Set) { WaterCourse_Token = _Set; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	int Bomb_MilliSecond = 0;
	int Bomb_Second = 0;

	int Sub_MilliSecond = 0;
	int Sub_Second = 0;
	bool BombServer = false;

	bool OtherCreate = false;
	
	float GetCreateTime();

	int WaterBomb_Token = 0;
	static int WaterCourse_Token;
	static bool SetWater_CourseToken;

private :
	void StateInit();
	void CreateAnimation();
	
	void NoneBegin();
	void NoneTick(float _DeltaTime);
	void CreateBegin();
	void CreateTick(float _DeltaTime);
	void CreateExit();
	void KickBegin();
	void KickTick(float _DeltaTime);
	void KickExit();
	void BombBegin();
	void BombTick(float _DeltaTime);
	void BombExit();

	UStateManager State;

	USpriteRenderer* WaterBombRenderer = nullptr;
	ACAGameMode* CulGameMode = nullptr;
	ACAGameMode* WaterBombThisGameMode = nullptr;
	float LifeTime = 0.0f; // ++DeltaTime
	float BombTime = 2.0f; // 2.0
	float ServerBombTime = 0.0f;
	bool b_WaterToBomb = false;
	bool b_ServerBomb = false;

	float KickSpeed = 50.f;
	FVector MoveVector = FVector::Zero;


};

