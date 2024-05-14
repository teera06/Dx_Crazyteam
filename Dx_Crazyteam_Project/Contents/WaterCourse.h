#pragma once
#include <EngineCore/Actor.h>
#include "Block.h"

class USpriteRenderer;
class AWaterCourse : public ABlock
{
	GENERATED_BODY(ABlock)

public :
	// constructor destructor
	AWaterCourse();
	~AWaterCourse();

	// delete Function
	AWaterCourse(const AWaterCourse& _Other) = delete;
	AWaterCourse(AWaterCourse&& _Other) noexcept = delete;
	AWaterCourse& operator=(const AWaterCourse& _Other) = delete;
	AWaterCourse& operator=(AWaterCourse&& _Other) noexcept = delete;
	
	inline void SetPowerValue(size_t _Power)
	{
		PowerValue = _Power;
	}


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

	inline void SetBombPoint(POINT _Point)
	{
		BombPoint = _Point;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

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

	UStateManager State;
	USpriteRenderer* WaterCourseRender = nullptr;
	float LifeTime = 0.0f;
	float CreateTime = 0.0f;
	size_t PowerValue = 0;
	POINT BombPoint = POINT(0, 0);
};

