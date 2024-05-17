#pragma once
#include "Player.h"

// Ό³Έν :
class AItem;
class AServerTestPlayer : public APlayer
{
	GENERATED_BODY(APlayer)
public:
	// constrcuter destructer
	AServerTestPlayer();
	~AServerTestPlayer();

	// delete Function
	AServerTestPlayer(const AServerTestPlayer& _Other) = delete;
	AServerTestPlayer(AServerTestPlayer&& _Other) noexcept = delete;
	AServerTestPlayer& operator=(const AServerTestPlayer& _Other) = delete;
	AServerTestPlayer& operator=(AServerTestPlayer&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<AItem> Item = nullptr;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void SpawnItem();

};

