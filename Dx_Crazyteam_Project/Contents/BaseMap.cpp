#include "PreCompile.h"
#include "BaseMap.h"
#include <EngineCore/DefaultSceneComponent.h>

ABaseMap::ABaseMap()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	SetRoot(Root);
}

ABaseMap::~ABaseMap()
{
}

void ABaseMap::BeginPlay()
{
	Super::BeginPlay();

	//for (int y = 0; y < TileY; y++)
	//{
	//	//MapStatus.push_back()
	//	for (int x = 0; x < TileX; x++)
	//	{
	//		MapStatus[y].push_back(nullptr);
	//	}
	//}

}

void ABaseMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}