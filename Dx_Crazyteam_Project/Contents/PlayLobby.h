#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>

class PlayLobby : public AActor, public UNetObject
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	PlayLobby();
	~PlayLobby();

	// delete Function
	PlayLobby(const PlayLobby& _Other) = delete;
	PlayLobby(PlayLobby&& _Other) noexcept = delete;
	PlayLobby& operator=(const PlayLobby& _Other) = delete;
	PlayLobby& operator=(PlayLobby&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

