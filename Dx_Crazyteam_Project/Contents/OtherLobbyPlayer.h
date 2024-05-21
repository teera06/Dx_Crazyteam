#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class AOtherLobbyPlayer : public AActor, public UNetObject
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AOtherLobbyPlayer();
	~AOtherLobbyPlayer();

	// delete Function
	AOtherLobbyPlayer(const AOtherLobbyPlayer& _Other) = delete;
	AOtherLobbyPlayer(AOtherLobbyPlayer&& _Other) noexcept = delete;
	AOtherLobbyPlayer& operator=(const AOtherLobbyPlayer& _Other) = delete;
	AOtherLobbyPlayer& operator=(AOtherLobbyPlayer&& _Other) noexcept = delete;

protected:

private:
	UStateManager State;
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

