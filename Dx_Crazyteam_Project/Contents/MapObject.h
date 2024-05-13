#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class MapObject : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	MapObject();
	~MapObject();

	// delete Function
	MapObject(const MapObject& _Other) = delete;
	MapObject(MapObject&& _Other) noexcept = delete;
	MapObject& operator=(const MapObject& _Other) = delete;
	MapObject& operator=(MapObject&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

