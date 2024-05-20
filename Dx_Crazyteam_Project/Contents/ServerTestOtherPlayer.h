#pragma once
#include "Player.h"

// Ό³Έν :
class AServerTestOtherPlayer : public APlayer
{
	GENERATED_BODY(APlayer)
public:
	// constrcuter destructer
	AServerTestOtherPlayer();
	~AServerTestOtherPlayer();

	// delete Function
	AServerTestOtherPlayer(const AServerTestOtherPlayer& _Other) = delete;
	AServerTestOtherPlayer(AServerTestOtherPlayer&& _Other) noexcept = delete;
	AServerTestOtherPlayer& operator=(const AServerTestOtherPlayer& _Other) = delete;
	AServerTestOtherPlayer& operator=(AServerTestOtherPlayer&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

