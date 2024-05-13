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

	void NoneBegin();
	void NoneTick(float _DeltaTime);
	void CreateBegin();
	void CreateTick(float _DeltaTime);
	void CreateExit();
	void DeleteBegin();
	void DeleteTick(float _DeltaTime);
	void DeleteExit();

	UStateManager State;
	USpriteRenderer* WaterCourseRender = nullptr;
	float LifeTime = 0.0f;
};

