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
}

void ABaseMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}