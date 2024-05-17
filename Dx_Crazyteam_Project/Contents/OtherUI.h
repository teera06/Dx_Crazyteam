#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "MapUI.h"

// Ό³Έν :
class USpriteRenderer;
class AOtherUI : public AMapUI
{
public:
	// constrcuter destructer
	AOtherUI();
	~AOtherUI();

	// delete Function
	AOtherUI(const AOtherUI& _Other) = delete;
	AOtherUI(AOtherUI&& _Other) noexcept = delete;
	AOtherUI& operator=(const AOtherUI& _Other) = delete;
	AOtherUI& operator=(AOtherUI&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int MapTime_Second = 0;
	int MapTime_MilliSecond = 0;
};

