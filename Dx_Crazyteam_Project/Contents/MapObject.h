#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
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

	inline void SetPos(FVector _Pos)
	{
		Pos = _Pos;
	}

	inline void SetScale(FVector _Scale)
	{
		Scale = _Scale;
	}

	inline FVector GetPos() const
	{
		return Pos;
	}

	inline FVector GetScale() const
	{
		return Scale;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UDefaultSceneComponent* Root = nullptr;

	FVector Pos = FVector::Zero;
	FVector Scale = FVector::Zero;

private:

};

