#include "PreCompile.h"
#include "MapObject.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "CAGameMode.h"
#include "Player.h"

AMapObject::AMapObject()
{
	FrontRenderer = CreateDefaultSubObject<USpriteRenderer>("Front");
	BackRenderer = CreateDefaultSubObject<USpriteRenderer>("Back");

	FrontRenderer->SetupAttachment(Root);
	BackRenderer->SetupAttachment(Root);
}

AMapObject::~AMapObject()
{
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
}

