#include "PreCompile.h"
#include "BaseMap.h"
#include <EngineCore/DefaultSceneComponent.h>

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
	if (_PlayerPos.X > - 80.f + TileSize.X / 2.f * TileX ||
		_PlayerPos.X < -80.f + TileSize.X / 2.f * (-TileX))
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


//1.
// Plaery가 물풍선을 설치할 때,
// Power값을 물풍선에 주고,
// Map은 물풍선에 있는 Power값을 가져와 물줄기를 표시한다.
//2.
// Player가 물풍선을 설치할 때,
// Power값을 Map에 주고.
// Map은 그 값으로 물줄기를 표시한다.
void ABaseMap::GetWaterWavePoint()
{

}
