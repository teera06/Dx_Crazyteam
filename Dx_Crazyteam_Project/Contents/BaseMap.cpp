#include "PreCompile.h"
#include "BaseMap.h"
#include "Block.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <algorithm>

const FVector ABaseMap::TileSize = FVector(40.f, 40.f, 10.f);

const int ABaseMap::TileY = 13;
const int ABaseMap::TileX = 15;


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

	FirstPos.X = TileSize.X * (TileX / 2);
	FirstPos.Y = TileSize.Y * (TileY / 2);

	for (int y = 0; y < TileY; y++)
	{
		std::vector<std::shared_ptr<AMapObject>> Temp;
		MapStatus.push_back(Temp);
		for (int x = 0; x < TileX; x++)
		{
			std::shared_ptr<AMapObject> Default = GetWorld()->SpawnActor<AMapObject>("Block");
			FVector PushPos = FVector::Zero;
			PushPos.X = FirstPos.X + TileSize.X * x;
			PushPos.Y = FirstPos.Y - TileSize.Y * y;

			Default->SetPos(PushPos);
			Default->SetScale(TileSize);

			MapStatus[y].push_back(Default);
		}
	}

	AddMapObject(0, 0, EMapObjectType::Block);

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

	MapObj->SetActorLocation(MapStatus[_Y][_X]->GetPos());
	MapObj->SetActorScale3D(TileSize);
	MapObj->SetOrder(100);

	MapStatus[_Y][_X]->Destroy();
	MapStatus[_Y][_X] = MapObj;
}

std::pair<int,int> ABaseMap::PlayerPosToPoint(FVector _PlayerPos)
{
	float MinDistance = 999999;
	std::pair<int, int> Result;

	for (int y = 0; y < TileY - 1; y++)
	{
		for (int x = 0; x < TileX - 1; x++)
		{
			
		}
	}

	return Result;
}