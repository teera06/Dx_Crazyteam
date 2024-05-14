#pragma once
#include <EngineBase/NetObject.h>
#include <EngineCore/Actor.h>

// Ό³Έν :
class UDefaultSceneComponent;
class USpriteRenderer;
class UNetInterface : public UNetObject, public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	UNetInterface();
	~UNetInterface();

	// delete Function
	UNetInterface(const UNetInterface& _Other) = delete;
	UNetInterface(UNetInterface&& _Other) noexcept = delete;
	UNetInterface& operator=(const UNetInterface& _Other) = delete;
	UNetInterface& operator=(UNetInterface&& _Other) noexcept = delete;

protected:
	USpriteRenderer* Renderer = nullptr;
	UDefaultSceneComponent* Root = nullptr;

	void PlayerSendPacket(float _DeltaTime);
	void PlayerShadowPacket(float _DeltaTime);
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void BaseNetInit(float _DeltaTime);
	float FrameTime = 1.0f / 60.0f;
	float CurTime = FrameTime;
};

