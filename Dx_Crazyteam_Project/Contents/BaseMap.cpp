#include "PreCompile.h"
#include "BaseMap.h"
#include "Block.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <algorithm>

const FVector ABaseMap::TileSize = FVector(40.f, 40.f, 10.f);

const int ABaseMap::TileY = 13;
const int ABaseMap::TileX = 15;

std::vector<std::vector<std::shared_ptr<AMapObject>>> ABaseMap::MapStatus;


ABaseMap::ABaseMap()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	SetRoot(Root);
}

ABaseMap::~ABaseMap()
{
}

bool ABaseMap::IsMove(FVector _PlayerPos)
{
	if (_PlayerPos.X > TileSize.X / 2.f * TileX ||
		_PlayerPos.X < TileSize.X / 2.f * (-TileX))
	{
		return false;
	}

	if (_PlayerPos.Y > TileSize.Y / 2.f * TileY ||
		_PlayerPos.Y < TileSize.Y / 2.f * (-TileY))
	{
		return false;
	}


	return true;
}



void ABaseMap::BeginPlay()
{
	Super::BeginPlay();

	FVector FirstPos = FVector::Zero;

	int a = TileY / 2;
	FirstPos.X = -TileSize.X * static_cast<float>((TileX / 2));
	FirstPos.Y = TileSize.Y * static_cast<float>((TileY / 2));


	for (int y = 0; y < TileY; y++)
	{
		std::vector<std::shared_ptr<AMapObject>> Temp;
		MapStatus.push_back(Temp);
		for (int x = 0; x < TileX; x++)
		{
			std::shared_ptr<AMapObject> Default = GetWorld()->SpawnActor<AMapObject>("Block");
			FVector PushPos = FVector::Zero;
			PushPos.X = FirstPos.X + TileSize.X * x;
			PushPos.Y = FirstPos.Y - TileSize.Y * y - TileSize.hY();

			Default->SetActorLocation(PushPos);
			Default->SetActorScale3D(TileSize);

			MapStatus[y].push_back(Default);
		}
	}
}

void ABaseMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


void ABaseMap::AddMapObject(int _Y, int _X, EMapObjectType _MapObjectType)
{
	std::shared_ptr<AMapObject> MapObj = nullptr;

	switch (_MapObjectType)
	{
	case EMapObjectType::Block:
		MapObj = GetWorld()->SpawnActor<ABlock>("Block");
		break;
	case EMapObjectType::BrakableBlock:
		break;
	case EMapObjectType::MoveBlock:
		break;
	case EMapObjectType::Bush:
		break;
	case EMapObjectType::WaterBalloon:
		break;
	default:
		break;
	}

	MapObj->SetActorLocation(MapStatus[_Y][_X]->GetActorLocation());
	MapObj->SetActorScale3D(TileSize);

	MapStatus[_Y][_X]->Destroy();
	MapStatus[_Y][_X] = MapObj;
}

POINT ABaseMap::PlayerPosToPoint(FVector _PlayerPos)
{
	float MinDistance = 999999;
	POINT Result;

	FVector PlayerPos = _PlayerPos;
	PlayerPos.Z = 0.f;

	for (int y = 0; y < TileY - 1; y++)
	{
		for (int x = 0; x < TileX - 1; x++)
		{
			FVector TileLocation = MapStatus[y][x]->GetActorLocation();
			TileLocation.Z = 0.f;

			float Distance = (PlayerPos - TileLocation).Size3D();

			if (Distance < MinDistance)
			{
				MinDistance = min(Distance, MinDistance);
				Result = { y,x };
			}
		}
	}

	return Result;
}