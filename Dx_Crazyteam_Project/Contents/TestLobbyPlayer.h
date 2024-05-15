#pragma once
#include "CAObject.h"

// Ό³Έν :
class ATestLobbyPlayer : public ACAObject
{
	GENERATED_BODY(ACAObject)

public:
	// constrcuter destructer
	ATestLobbyPlayer();
	~ATestLobbyPlayer();

	// delete Function
	ATestLobbyPlayer(const ATestLobbyPlayer& _Other) = delete;
	ATestLobbyPlayer(ATestLobbyPlayer&& _Other) noexcept = delete;
	ATestLobbyPlayer& operator=(const ATestLobbyPlayer& _Other) = delete;
	ATestLobbyPlayer& operator=(ATestLobbyPlayer&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void RendererInit();

};

