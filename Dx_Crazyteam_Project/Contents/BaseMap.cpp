#include "PreCompile.h"
#include "BaseMap.h"
#include <EngineCore/DefaultSceneComponent.h>

const FVector ABaseMap::TileSize = FVector(40.f, 40.f, 10.f);

const int ABaseMap::TileY = 18;
const int ABaseMap::TileX = 20;


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

	if (_PlayerPos.Y > TileSize.Y / 2.f * TileX ||
		_PlayerPos.Y < TileSize.Y / 2.f * (-TileX))
	{
		return false;
	}




	return true;
}

void ABaseMap::BeginPlay()
{
	Super::BeginPlay();

	for (int y = 0; y < TileY; y++)
	{
		std::vector<AMapObject*> Temp;
		MapStatus.push_back(Temp);
		for (int x = 0; x < TileX; x++)
		{
			MapStatus[y].push_back(nullptr);
		}
	}

}

void ABaseMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}