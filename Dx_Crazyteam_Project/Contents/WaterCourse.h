#pragma once
#include <EngineCore/Actor.h>
#include "Block.h"

class USpriteRenderer;
class AWaterCourse : public AMapObject
{
	GENERATED_BODY(AMapObject)

public :
	// constructor destructor
	AWaterCourse();
	~AWaterCourse();

	// delete Function
	AWaterCourse(const AWaterCourse& _Other) = delete;
	AWaterCourse(AWaterCourse&& _Other) noexcept = delete;
	AWaterCourse& operator=(const AWaterCourse& _Other) = delete;
	AWaterCourse& operator=(AWaterCourse&& _Other) noexcept = delete;
	
	/// <summary>
	/// 물줄기 중간 생성.
	/// </summary>
	inline void CreateWaterCenter()
	{
		State.ChangeState("CreateCenter");
		return;
	}

	/// <summary>
	/// 물줄기 생성.
	/// </summary>
	inline void CreateWaterStream()
	{
		State.ChangeState("CreateStream");
		return;
	}
	/// <summary>
	/// 물줄기 끝 생성.
	/// </summary>
	inline void CreateWaterEndStem()
	{
		State.ChangeState("CreateEndStem");
		return;
	}

	inline void SetDir(EEngineDir _Dir)
	{
		WaterCourseDir = _Dir;
	}

	void WaterSend(std::shared_ptr<AWaterCourse> _SET);
	 
	static int WaterCourseToken;
	static bool SetToken;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	int Bomb_MilliSecond = 0;
	int Bomb_Second = 0;

	int Sub_MilliSecond = 0;
	int Sub_Second = 0;

	bool OtherCreate = false;



private :
	void StateInit();
	void CreateAnimation();

	void NoneBegin();
	void NoneTick(float _DeltaTime);

	void CreateCenterBegin();
	void CreateCenterTick(float _DeltaTime);
	void CreateCenterExit();
	void CreateStreamBegin();
	void CreateStreamTick(float _DeltaTime);
	void CreateStreamExit();
	void CreateEndStemBegin();
	void CreateEndStemTick(float _DeltaTime);
	void CreateEndStemExit();
	void DeleteBegin();
	void DeleteTick(float _DeltaTime);
	void DeleteExit();

	
	void CreateWaterStream(float _DeltaTime);


	UStateManager State;
	//USpriteRenderer* Renderer = nullptr; // 수정해야 함. TODO
	bool CreateStart = false;
	bool b_BombCountUpdateOne = false;
	bool UpEnd = false;
	bool DownEnd = false;
	bool LeftEnd = false;
	bool RightEnd = false;
	float CenterLifeTime = 0.0f;
	float LifeTime = 2.0f;
	float CreateDeltaTime = 0.0f;
	float CreateTime = 0.125f; // 0.125f
	const size_t MaxPowerValue = 7;
	int DefaultPowerValue = 1;
	std::string PreAniName = "";
	EEngineDir WaterCourseDir = EEngineDir::MAX;
};

