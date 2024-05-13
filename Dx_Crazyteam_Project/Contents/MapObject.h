#pragma once
#include <EngineCore/Actor.h>

// ���� :
class UDefaultSceneComponent;
class AMapObject : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AMapObject();
	~AMapObject();

	// delete Function
	AMapObject(const AMapObject& _Other) = delete;
	AMapObject(AMapObject&& _Other) noexcept = delete;
	AMapObject& operator=(const AMapObject& _Other) = delete;
	AMapObject& operator=(AMapObject&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	USpriteRenderer* FrontRenderer = nullptr;
	USpriteRenderer* BackRenderer = nullptr;

	UDefaultSceneComponent* Root = nullptr;

	FVector Pos = FVector::Zero;
	//FVector Scale = 

private:

};
