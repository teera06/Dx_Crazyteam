#include "PreCompile.h"
#include "BaseMap.h"
#include "Block.h"
#include "CampBlock.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <algorithm>

std::vector<std::vector<std::shared_ptr<AMapObject>>> ABaseMap::MapStatus;


ABaseMap::ABaseMap()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	SetRoot(Root);
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
			case EMapObjectType::WaterBalloon:
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

			MapStatus[y].push_back(Default);
		}
	}
}

void ABaseMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


void ABaseMap::AddMapObject(int _Y, int _X, EMapObject _MapObjectType)
{
	std::shared_ptr<AMapObject> MapObj = nullptr;

	switch (_MapObjectType)
	{
	case EMapObject::NormalBlock:
		MapObj = GetWorld()->SpawnActor<ABlock>("Block");
		break;
	case EMapObject::CampBlock:
		MapObj = GetWorld()->SpawnActor<ACampBlock>("CampBlock");
		break;
	default:
		break;
	}

	MapObj->SetActorLocation(MapStatus[_Y][_X]->GetActorLocation());

	MapStatus[_Y][_X]->Destroy();
	MapStatus[_Y][_X] = MapObj;
}

POINT ABaseMap::PlayerPosToPoint(FVector _PlayerPos)
{
	float MinDistance = 999999;
	POINT Result;

	FVector PlayerPos = _PlayerPos;
	PlayerPos.Z = 0.f;

	for (int y = 0; y < ConstValue::TileY - 1; y++)
	{
		for (int x = 0; x < ConstValue::TileX - 1; x++)
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