#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class AOtherPlayer : public AActor, public UNetObject
{
public:
	// constrcuter destructer
	AOtherPlayer();
	~AOtherPlayer();

	// delete Function
	AOtherPlayer(const AOtherPlayer& _Other) = delete;
	AOtherPlayer(AOtherPlayer&& _Other) noexcept = delete;
	AOtherPlayer& operator=(const AOtherPlayer& _Other) = delete;
	AOtherPlayer& operator=(AOtherPlayer&& _Other) noexcept = delete;

	inline bool IsOtherPlayerDestroy() const
	{
		return IsOPDestroy;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);

private:
	UStateManager State;
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	bool IsOPDestroy = false;
};

