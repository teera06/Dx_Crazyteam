#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UEngineTexture;
class UDefaultSceneComponent;
class AMapObject;
class ABaseMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ABaseMap();
	~ABaseMap();

	// delete Function
	ABaseMap(const ABaseMap& _Other) = delete;
	ABaseMap(ABaseMap&& _Other) noexcept = delete;
	ABaseMap& operator=(const ABaseMap& _Other) = delete;
	ABaseMap& operator=(ABaseMap&& _Other) noexcept = delete;

	bool IsMove(FVector _PlayerPos);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	USpriteRenderer* BackMap = nullptr;
	USpriteRenderer* ColMap = nullptr;
	UDefaultSceneComponent* Root = nullptr;

	std::vector<std::vector<AMapObject*>> MapStatus;

	const FVector TileSize = FVector(20.f, 20.f, 10.f);

	const int TileY = 18;
	const int TileX = 20;
private:

};

