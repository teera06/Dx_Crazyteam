#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>
#include <EngineCore/DefaultSceneComponent.h>

class APlayer;
class PlayerInfo
{
	friend APlayer;

public:
	float MoveSpeed = 100.f;
};

class APlayer : public AActor, public UNetObject
{
	GENERATED_BODY(AActor)
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;
	
protected:
	std::shared_ptr<PlayerInfo> Info = nullptr;
	UStateManager State;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;

private:
	void StateInit();

	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);

	//void Attack(float _DeltaTime);
	//void Die(float _DeltaTime);

	std::string GetAnimationName(std::string_view _StateName);

	FVector Dir = FVector::Down;
	float AnimationInter = 0.1f;
};


