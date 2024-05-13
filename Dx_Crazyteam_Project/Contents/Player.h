#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/DefaultSceneComponent.h>

class APlayer : public AActor
{
	GENERATED_BODY(AActor)
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;
	
	UStateManager State;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;

private:
	void StateInit();

	void Idle();
	void Move();
	void Attack();
	void Die();


};


