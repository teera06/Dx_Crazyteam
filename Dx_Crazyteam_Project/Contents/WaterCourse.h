#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class AWaterCourse : public AActor
{
	GENERATED_BODY(AActor)

public :
	// constructor destructor
	AWaterCourse();
	~AWaterCourse();

	// delete Function
	AWaterCourse(const AWaterCourse& _Other) = delete;
	AWaterCourse(AWaterCourse&& _Other) noexcept = delete;
	AWaterCourse& operator=(const AWaterCourse& _Other) = delete;
	AWaterCourse& operator=(AWaterCourse&& _Other) noexcept = delete;
	
	inline void SetTheEnd(bool _Val)
	{
		b_TheEnd = _Val;
	}

	inline void SetWaterCourseDir(EEngineDir _Dir)
	{
		Dir = _Dir;
	}

	inline void CreateWaterCourse()
	{
		State.ChangeState("Create");
		return;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void StateInit();
	void CreateAnimation();
	void ChangeAnimation(std::string_view _AniName ,bool _Val);

	void NoneBegin();
	void NoneTick(float _DeltaTime);
	void CreateBegin();
	void CreateTick(float _DeltaTime);
	void CreateExit();
	void DeleteBegin();
	void DeleteTick(float _DeltaTime);
	void DeleteExit();

	bool b_TheEnd = false;
	UStateManager State;
	USpriteRenderer* WaterCourseRender = nullptr;
	EEngineDir Dir = EEngineDir::MAX;
	float LifeTime = 0.0f;
};

