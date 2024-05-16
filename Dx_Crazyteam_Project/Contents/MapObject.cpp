#include "PreCompile.h"
#include "MapObject.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "CAGameMode.h"
#include "Player.h"
#include "BaseMap.h"

AMapObject::AMapObject()
{

}

AMapObject::~AMapObject()
{
}

void AMapObject::DepthUpdate()
{
	FVector Location = GetActorLocation();
	Location.Z = static_cast<float>(GetCurPos().y);
	//Location.Z *= -1.f;

	SetActorLocation(Location);
}

void AMapObject::BeginPlay()
{
	Super::BeginPlay();

	PlayerInteract = [](){};
	WaterInteract = [](){};
}

void AMapObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	DepthUpdate();
}

