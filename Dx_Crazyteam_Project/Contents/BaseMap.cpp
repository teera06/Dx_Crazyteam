#include "PreCompile.h"
#include "BaseMap.h"
#include "Block.h"
#include "CampBlock.h"
#include "WaterBomb.h"
#include "WaterCourse.h"
#include "DummyBlock.h"
#include "CampMoveBlock.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <algorithm>
#include "CAGameMode.h"
#include "Player.h"

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

	POINT CheckPoint = PosToPoint(_CheckPos);

	if (MapStatus[CheckPoint.y][CheckPoint.x] == nullptr) return true;

	switch (MapStatus[CheckPoint.y][CheckPoint.x]->GetType())
	{
		case EMapObjectType::None:
		case EMapObjectType::Water:
		{
			return true;
		}
		break;

		case EMapObjectType::WaterBalloon:
		{
			std::shared_ptr<APlayer> Player = GetGameMode()->GetPlayer();
			POINT PlayerPoint = Player->GetPlayerInfo()->CurIndex;
			POINT CheckPoint = PosToPoint(_CheckPos);
			if (CheckPoint.x != PlayerPoint.x ||
				CheckPoint.y != PlayerPoint.y)
			{
				return false;
			}
			else return true;
		}
		case EMapObjectType::Block:
		case EMapObjectType::BrakableBlock:
		case EMapObjectType::MoveBlock:
		{
			FVector TilePosition = MapStatus[CheckPoint.y][CheckPoint.x]->GetActorLocation();

			if (TilePosition.X + ConstValue::TileSize.X / 2.f > _CheckPos.X &&
				TilePosition.X - ConstValue::TileSize.X / 2.f < _CheckPos.X &&
				TilePosition.Y + ConstValue::TileSize.Y / 2.f > _CheckPos.Y &&
				TilePosition.Y - ConstValue::TileSize.Y / 2.f < _CheckPos.Y)
			{
				POINT CheckPoint = PosToPoint(_CheckPos);

				if (MapStatus[CheckPoint.y][CheckPoint.x] == nullptr) return true;

				MapStatus[CheckPoint.y][CheckPoint.x]->PlayerInteract();
				return false;
			}

			return true;
		}
		break;
		case EMapObjectType::Item:
		{
			POINT CheckPoint = PosToPoint(_CheckPos);
			MapStatus[CheckPoint.y][CheckPoint.x]->PlayerInteract();
			return true;
		}
		break;
		default:
			return true;
			break;
	}
}

bool ABaseMap::IsEmpty(FVector _PlayerPos)
{
	POINT PlayerPoint = PosToPoint(_PlayerPos);

	if (MapStatus[PlayerPoint.y][PlayerPoint.x] = nullptr)
	{
		return true;
	}

	return false;
}

bool ABaseMap::IsEmpty(int _Y, int _X)
{

	if (MapStatus[_Y][_X] == nullptr)
	{
		return true;
	}

	return false;
}



void ABaseMap::BeginPlay()
{
	Super::BeginPlay();

	AddActorLocation(FVector(0.f, ConstValue::TileSize.Y / 2.f, 0.f));

	
	for (int y = 0; y < ConstValue::TileY-1; y++)
	{
		std::vector<std::shared_ptr<AMapObject>> Temp;
		MapStatus.push_back(Temp);
		for (int x = 0; x < ConstValue::TileX; x++)
		{
			MapStatus[y].push_back(nullptr);
		}
	}
}

void ABaseMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


std::shared_ptr<AMapObject> ABaseMap::AddMapObject(int _Y, int _X, EMapObject _MapObjectType)
{
	FVector PushPos = PointToPos(_Y, _X);


	std::shared_ptr<AMapObject> MapObj = nullptr;
	switch (_MapObjectType)
	{
	case EMapObject::Default:
	{
		MapObj = GetWorld()->SpawnActor<AMapObject>("Default");
		break;
	}
	case EMapObject::DummyBlock:
	{
		MapObj = GetWorld()->SpawnActor<ADummyBlock>("Block");
		break;
	}
	case EMapObject::CampMoveBlock:
	{
		MapObj = GetWorld()->SpawnActor<ACampMoveBlock>("Block");
		break;
	}
	case EMapObject::NormalBlock:
	{
		MapObj = GetWorld()->SpawnActor<ABlock>("Block");
		break;
	}
	case EMapObject::CampBlock:
	{
		MapObj = GetWorld()->SpawnActor<ACampBlock>("CampBlock");
		break;
	}
	case EMapObject::WaterBomb:
	{
		std::shared_ptr<AWaterBomb> TempObj = GetWorld()->SpawnActor<AWaterBomb>("CampBlock");
		TempObj->SetActorLocation(PushPos);
		TempObj->CreateWaterBomb();
		MapObj = TempObj;
		break;
	}
	case EMapObject::Water:
	{
		std::shared_ptr<AWaterCourse> TempObj = GetWorld()->SpawnActor<AWaterCourse>("CampBlock");
		TempObj->SetActorLocation(PushPos);
		TempObj->CreateWaterCenter();
		MapObj = TempObj;
		break;
	}
	default:
		break;
	}

	MapObj->SetActorLocation(PushPos);
	MapObj->SetCurPos(POINT(_X, _Y));
	MapObj->SetCurGameMode(GetGameMode());

	if (MapStatus[_Y][_X] != nullptr)
	{
		MapStatus[_Y][_X]->Destroy();
	}

	MapStatus[_Y][_X] = MapObj;

	return MapObj;
}

std::shared_ptr<AMapObject> ABaseMap::AddWaterCourse(int _Y, int _X, bool _IsEnd, EEngineDir _Dir)
{
	std::shared_ptr<AMapObject> MapObj = nullptr;

	FVector PushPos = PointToPos(_Y, _X);

	std::shared_ptr<AWaterCourse> TempObj = GetWorld()->SpawnActor<AWaterCourse>("CampBlock");
	TempObj->SetActorLocation(PushPos);
	TempObj->SetDir(_Dir);
	if (false == _IsEnd)
	{
		TempObj->CreateWaterStream();
	}
	else
	{
		TempObj->CreateWaterEndStem();
	}
	MapObj = TempObj;


	MapObj->SetActorLocation(PushPos);
	MapObj->SetCurPos(POINT(_X, _Y));
	MapObj->SetCurGameMode(GetGameMode());

	if (MapStatus[_Y][_X] != nullptr)
	{
		MapStatus[_Y][_X]->Destroy();
	}

	MapStatus[_Y][_X] = MapObj;

	return MapObj;
}

void ABaseMap::PushMapObject(std::shared_ptr<AMapObject> _Obj, int _Y, int _X)
{
	if (MapStatus[_Y][_X] != nullptr)
	{
		MapStatus[_Y][_X]->Destroy();
	}

	FVector PushPos = PointToPos(_Y, _X);

	_Obj->SetActorLocation(PushPos);
	_Obj->SetCurPos(POINT(_X, _Y));
	_Obj->SetCurGameMode(GetGameMode());

	MapStatus[_Y][_X] = _Obj;
}

void ABaseMap::MoveMapObject(std::shared_ptr<AMapObject> _Obj, int _NY, int _NX, int _PY, int _PX)
{
	PushMapObject(_Obj, _NY, _NX);
	MapStatus[_PY][_PX] = nullptr;
}

std::shared_ptr<AMapObject> ABaseMap::SpawnWaterBomb(FVector _SpawnPos)
{
	POINT BombPoint = PosToPoint(_SpawnPos);

	return AddMapObject(BombPoint.y, BombPoint.x, EMapObject::WaterBomb);
}

std::shared_ptr<AMapObject> ABaseMap::SpawnWaterBomb(int _Y, int _X)
{
	return AddMapObject(_Y, _X, EMapObject::WaterBomb);
}

void ABaseMap::DestroyMapObject(int _Y, int _X)
{
	MapStatus[_Y][_X]->Destroy();
	MapStatus[_Y][_X] = nullptr;
}

POINT ABaseMap::PosToPoint(FVector _PlayerPos)
{
	float MinDistance = 999999;
	POINT Result = { 0,0 };

	FVector PlayerPos = _PlayerPos;
	PlayerPos.Z = 0.f;


	for (int y = 0; y < ConstValue::TileY - 1; y++)
	{
		for (int x = 0; x < ConstValue::TileX; x++)
		{
			FVector TileLocation = PointToPos(y,x);
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

FVector ABaseMap::PointToPos(int _Y, int _X)
{
	FVector FirstPos = FVector::Zero;

	FirstPos.X = -ConstValue::TileSize.X * static_cast<float>((ConstValue::TileX / 2));
	FirstPos.Y = ConstValue::TileSize.Y * static_cast<float>((ConstValue::TileY - 1) / 2);

	FVector PushPos = FVector::Zero;

	PushPos.X = FirstPos.X + ConstValue::TileSize.X * _X;
	PushPos.Y = FirstPos.Y - ConstValue::TileSize.Y * _Y;

	return PushPos;
}
