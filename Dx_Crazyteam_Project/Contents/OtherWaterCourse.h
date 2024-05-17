#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "WaterCourse.h"
// Ό³Έν :
class USpriteRenderer;
class AOtherWaterCourse : public AWaterCourse
{
public:
	// constrcuter destructer
	AOtherWaterCourse();
	~AOtherWaterCourse();

	// delete Function
	AOtherWaterCourse(const AOtherWaterCourse& _Other) = delete;
	AOtherWaterCourse(AOtherWaterCourse&& _Other) noexcept = delete;
	AOtherWaterCourse& operator=(const AOtherWaterCourse& _Other) = delete;
	AOtherWaterCourse& operator=(AOtherWaterCourse&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int OherBomb_Second = 0;
	int OherBomb_MilliSecond = 0;
};

