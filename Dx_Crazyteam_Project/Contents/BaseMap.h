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
	bool IsOnWater(FVector _PlayerPos);
	bool IsOnBush(FVector _PlayerPos);
	bool IsOnBush(int _Y, int _X);

	std::shared_ptr<AMapObject> AddMapObject(int _Y, int _X, EMapObject _MapObjectType, EItemType _Item = EItemType::None);
	std::shared_ptr<AMapObject> SpawnMapObject(int _Y, int _X, EMapObject _MapObjectType, EItemType _Item = EItemType::None);
	std::shared_ptr<AMapObject> SpawnItemObject(int _Y, int _X, EItemType _Item);
	std::shared_ptr<AMapObject> AddWaterCourse(int _Y, int _X, bool _IsEnd, EEngineDir _Dir);

	std::shared_ptr<AMapObject> GetMapObject(int _Y, int _X)
	{
		return MapStatus[_Y][_X];
	}
	void PushMapObject(std::shared_ptr<AMapObject> _Obj, int _Y, int _X);
	void MoveMapObject(std::shared_ptr<AMapObject> _Obj, int _NY, int _NX, int _PY, int _PX);

	EGimmickType GetGimmickType(int _Y, int _X)
	{
		return GimmickStatus[_Y][_X];
	}

	void SetGimickType(int _Y, int _X, EGimmickType _Type)
	{
		GimmickStatus[_Y][_X] = _Type;
	}

	std::shared_ptr<AMapObject> SpawnWaterBomb(FVector _SpawnPos);
	std::shared_ptr<AMapObject> SpawnWaterBomb(int _Y, int _X);
	void DestroyMapObject(int _Y, int _X);

	POINT PosToPoint(FVector _PlayerPos);
	FVector PointToPos(int _Y, int _X);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UDefaultSceneComponent* Root = nullptr;

	std::vector<std::vector<std::shared_ptr<AMapObject>>> MapStatus;
	std::vector<std::vector<EGimmickType>> GimmickStatus;
private:
};

