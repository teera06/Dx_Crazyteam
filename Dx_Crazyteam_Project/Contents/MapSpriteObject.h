#pragma once
#include "MapObject.h"

// Ό³Έν :
class AMapSpriteObject : public AMapObject
{
	GENERATED_BODY(AMapObject)
public:
	// constructor destructor
	AMapSpriteObject();
	~AMapSpriteObject();

	// delete Function
	AMapSpriteObject(const AMapSpriteObject& _Other) = delete;
	AMapSpriteObject(AMapSpriteObject&& _Other) noexcept = delete;
	AMapSpriteObject& operator=(const AMapSpriteObject& _Other) = delete;
	AMapSpriteObject& operator=(AMapSpriteObject&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	USpriteRenderer* FrontRenderer = nullptr;
	USpriteRenderer* BackRenderer = nullptr;

private:

};

