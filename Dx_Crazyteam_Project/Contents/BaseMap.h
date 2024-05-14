#pragma once
#include "CAObject.h"


// Ό³Έν :
class UEngineTexture;
class UDefaultSceneComponent;
class AMapObject;
class ABaseMap : public ACAObject
{
	GENERATED_BODY(ACAObject)
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
	bool IsEmpty(FVector _PlayerPos);
	bool IsEmpty(int _Y, int _X);

	std::shared_ptr<AMapObject> AddMapObject(int _Y, int _X, EMapObject _MapObjectType);
	std::shared_ptr<AMapObject> AddWaterCourse(int _Y, int _X, bool _IsEnd, EEngineDir _Dir);
	std::shared_ptr<AMapObject> GetMapObject(int _Y, int _X)
	{
		return MapStatus[_Y][_X];
	}
	void PushMapObject(std::shared_ptr<AMapObject> _Obj, int _ny, int _nx);
	void SpawnWaterBomb(FVector _SpawnPos);
	void SpawnWaterBomb(int _Y, int _X);
	void DestroyMapObject(int _Y, int _X);

	POINT PlayerPosToPoint(FVector _PlayerPos);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UDefaultSceneComponent* Root = nullptr;

	std::vector<std::vector<std::shared_ptr<AMapObject>>> MapStatus;
private:

	void GetWaterWavePoint();
};

