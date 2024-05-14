#include "PreCompile.h"
#include "MapObject.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "CAGameMode.h"
#include "Player.h"

AMapObject::AMapObject()
{

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

