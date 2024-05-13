#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>

class UImage;
class APlayLobby : public AActor, public UNetObject
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APlayLobby();
	~APlayLobby();

	// delete Function
	APlayLobby(const APlayLobby& _Other) = delete;
	APlayLobby(APlayLobby&& _Other) noexcept = delete;
	APlayLobby& operator=(const APlayLobby& _Other) = delete;
	APlayLobby& operator=(APlayLobby&& _Other) noexcept = delete;

	void SetIsActive(bool _Active);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImage* PlayLobbyUI = nullptr;
};

