#include "PreCompile.h"
#include "MapObject.h"
#include <EngineCore/DefaultSceneComponent.h>

AMapObject::AMapObject()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);
}

AMapObject::~AMapObject()
{
}

void AMapObject::BeginPlay()
{
	Super::BeginPlay();
}

void AMapObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

