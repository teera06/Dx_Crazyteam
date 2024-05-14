#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class USpriteRenderer;
class AOtherBomb : public AActor, public UNetObject
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
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
};

