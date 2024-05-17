#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "WaterBomb.h"

// Ό³Έν :
class USpriteRenderer;
class AOtherBomb : public AWaterBomb/*,public AActor, public UNetObject*/
{
public:
	// constrcuter destructer
	AOtherBomb();
	~AOtherBomb();

	// delete Function
	AOtherBomb(const AOtherBomb& _Other) = delete;
	AOtherBomb(AOtherBomb&& _Other) noexcept = delete;
	AOtherBomb& operator=(const AOtherBomb& _Other) = delete;
	AOtherBomb& operator=(AOtherBomb&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int OherBomb_Second = 0;
	int OherBomb_MilliSecond = 0;

	//UDefaultSceneComponent* Root = nullptr;
	//USpriteRenderer* Renderer = nullptr;
};

