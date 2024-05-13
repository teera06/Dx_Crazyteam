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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	USpriteRenderer* BackMap = nullptr;
	USpriteRenderer* ColMap = nullptr;
	UDefaultSceneComponent* Root = nullptr;

	std::vector<std::vector<AMapObject*>> MapStatus;

	int TileY = 18;
	int TileX = 20;
private:

};

