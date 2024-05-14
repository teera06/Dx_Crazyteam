#include "PreCompile.h"
#include "BaseMap.h"
#include "Block.h"
#include "CampBlock.h"
#include "WaterBomb.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <algorithm>

ABaseMap::ABaseMap()
{

}

ABaseMap::~ABaseMap()
{
}

bool ABaseMap::IsMove(FVector _CheckPos)
{
	if (_CheckPos.X > ConstValue::TileSize.X / 2.f * ConstValue::TileX ||
		_CheckPos.X < ConstValue::TileSize.X / 2.f * (-ConstValue::TileX))
	{
		return false;
	}

	if (_CheckPos.Y > ConstValue::TileSize.Y / 2.f * (ConstValue::TileY-1) ||
		_CheckPos.Y < ConstValue::TileSize.Y / 2.f * (-(ConstValue::TileY-1)))
	{
		return false;
	}

	for (int y = 0; y < ConstValue::TileY-1; y++)
	{
		for (int x = 0 ; x < ConstValue::TileX; x++)
		{
			switch (MapStatus[y][x]->GetType())
			{
			case EMapObjectType::None:
				continue;
			case EMapObjectType::Block:
			case EMapObjectType::BrakableBlock:
			case EMapObjectType::MoveBlock:
			case EMapObjectType::Water:
			{
				FVector TilePosition = MapStatus[y][x]->GetActorLocation();

				if (TilePosition.X + ConstValue::TileSize.X / 2.f > _CheckPos.X &&
					TilePosition.X - ConstValue::TileSize.X / 2.f < _CheckPos.X &&
					TilePosition.Y + ConstValue::TileSize.Y / 2.f > _CheckPos.Y &&
					TilePosition.Y - ConstValue::TileSize.Y / 2.f < _CheckPos.Y)
				{
					return false;
				}
			}
			break;
			}
		}
	}


	return true;
}

bool ABaseMap::IsEmpty(FVector _PlayerPos)
{
	POINT PlayerPoint = PlayerPosToPoint(_PlayerPos);

	if (MapStatus[PlayerPoint.y][PlayerPoint.x]->GetType() == EMapObjectType::None)
	{
		return true;
	}

	return false;
}

bool ABaseMap::IsEmpty(int _Y, int _X)
{

	if (MapStatus[_Y][_X]->GetType() == EMapObjectType::None)
	{
		return true;
	}

	return false;
}



void ABaseMap::BeginPlay()
{
	Super::BeginPlay();

	AddActorLocation(FVector(0.f, ConstValue::TileSize.Y / 2.f, 0.f));

	FVector FirstPos = FVector::Zero;

	FirstPos.X = -ConstValue::TileSize.X * static_cast<float>((ConstValue::TileX / 2));
	FirstPos.Y = ConstValue::TileSize.Y * static_cast<float>((ConstValue::TileY-1) / 2);
	
	for (int y = 0; y < ConstValue::TileY-1; y++)
	{
		std::vector<std::shared_ptr<AMapObject>> Temp;
		MapStatus.push_back(Temp);
		for (int x = 0; x < ConstValue::TileX; x++)
		{
			std::shared_ptr<AMapObject> Default = GetWorld()->SpawnActor<AMapObject>("Block");
			FVector PushPos = FVector::Zero;
			PushPos.X = FirstPos.X + ConstValue::TileSize.X * x;
			PushPos.Y = FirstPos.Y - ConstValue::TileSize.Y * y;

			Default->SetActorLocation(PushPos);
			Default->SetCurPos(POINT(x, y));

			MapStatus[y].push_back(Default);
		}
	}
}

void ABaseMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


std::shared_ptr<AMapObject> ABaseMap::AddMapObject(int _Y, int _X, EMapObject _MapObjectType)
{
	std::shared_ptr<AMapObject> MapObj = nullptr;
	switch (_MapObjectType)
	{
	case EMapObject::Default:
	{
		MapObj = GetWorld()->SpawnActor<AMapObject>("Default");
		break;
	}
	case EMapObject::NormalBlock:
	{
		std::shared_ptr<ABlock> TempObj = GetWorld()->SpawnActor<ABlock>("Block");
		MapObj = TempObj;
		break;
	}
	case EMapObject::CampBlock:
	{
		std::shared_ptr<ACampBlock> TempObj = GetWorld()->SpawnActor<ACampBlock>("CampBlock");
		MapObj = TempObj;
		break;
	}
	case EMapObject::WaterBomb:
	{
		std::shared_ptr<AWaterBomb> TempObj = GetWorld()->SpawnActor<AWaterBomb>("CampBlock");
		TempObj->SetActorLocation(MapStatus[_Y][_X]->GetActorLocation());
		TempObj->CreateWaterBomb();
		MapObj = TempObj;
		break;
	}
	default:
		break;
	}

	MapObj->SetActorLocation(MapStatus[_Y][_X]->GetActorLocation());
	MapObj->SetCurPos(POINT(_X, _Y));
	MapObj->SetCurGameMode(GetGameMode());

	MapStatus[_Y][_X]->Destroy();
	MapStatus[_Y][_X] = MapObj;

	return MapObj;
}

void ABaseMap::SpawnWaterBomb(FVector _SpawnPos)
{
	POINT BombPoint = PlayerPosToPoint(_SpawnPos);

	AddMapObject(BombPoint.y, BombPoint.x, EMapObject::WaterBomb);
}

void ABaseMap::SpawnWaterBomb(int _Y, int _X)
{
	AddMapObject(_Y, _X, EMapObject::WaterBomb);
}

void ABaseMap::DestroyMapObject(int _Y, int _X)
{
	AddMapObject(_Y, _X, EMapObject::Default);
}

POINT ABaseMap::PlayerPosToPoint(FVector _PlayerPos)
{
	float MinDistance = 999999;
	POINT Result;

	FVector PlayerPos = _PlayerPos;
	PlayerPos.Z = 0.f;

	for (int y = 0; y < ConstValue::TileY - 1; y++)
	{
		for (int x = 0; x < ConstValue::TileX; x++)
		{
			FVector TileLocation = MapStatus[y][x]->GetActorLocation();
			TileLocation.Z = 0.f;

			float Distance = (PlayerPos - TileLocation).Size3D();

			if (Distance < MinDistance)
			{
				MinDistance = min(Distance, MinDistance);
				Result = { x,y };
			}
		}
	}

	return Result;
}