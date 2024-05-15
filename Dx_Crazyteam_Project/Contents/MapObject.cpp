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

	FrontRenderer->SetOrder(ERenderOrder::BlockFront);
	BackRenderer->SetOrder(ERenderOrder::BlockBack);

	BackRenderer->SetPivot(EPivot::BOT);
	BackRenderer->AddPosition(FVector::Up * 20.f);
}

void AMapObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

