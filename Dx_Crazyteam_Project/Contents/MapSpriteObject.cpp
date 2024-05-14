#include "PreCompile.h"
#include "MapSpriteObject.h"
#include <EngineCore/DefaultSceneComponent.h>

AMapSpriteObject::AMapSpriteObject() 
{

	FrontRenderer = CreateDefaultSubObject<USpriteRenderer>("Front");
	FrontRenderer->SetupAttachment(Root);

	BackRenderer = CreateDefaultSubObject<USpriteRenderer>("Back");
	BackRenderer->SetupAttachment(Root);
}

AMapSpriteObject::~AMapSpriteObject() 
{
}

void AMapSpriteObject::BeginPlay()
{
	Super::BeginPlay();

	FrontRenderer->SetOrder(EObjectOrder::BlockFront);

	BackRenderer->SetOrder(EObjectOrder::BlockBack);
	BackRenderer->SetPivot(EPivot::BOT);
	BackRenderer->AddPosition(FVector(0.f, 20.f, 0.f));
}

void AMapSpriteObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

