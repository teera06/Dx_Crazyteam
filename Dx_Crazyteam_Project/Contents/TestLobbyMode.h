#pragma once
#include "CAGameMode.h"

// Ό³Έν :
class ATestLobbyMode : public ACAGameMode
{
	GENERATED_BODY(ACAGameMode)
public:
	// constrcuter destructer
	ATestLobbyMode();
	~ATestLobbyMode();

	// delete Function
	ATestLobbyMode(const ATestLobbyMode& _Other) = delete;
	ATestLobbyMode(ATestLobbyMode&& _Other) noexcept = delete;
	ATestLobbyMode& operator=(const ATestLobbyMode& _Other) = delete;
	ATestLobbyMode& operator=(ATestLobbyMode&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _DeltaTime) override;
	void LevelEnd(ULevel* _DeltaTime) override;
};

