#include "PreCompile.h"
#include "MapObject.h"
#include <EngineCore/DefaultSceneComponent.h>

AMapObject::AMapObject()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	FrontRenderer = CreateDefaultSubObject<USpriteRenderer>("Front");
	FrontRenderer->SetupAttachment(Root);

	BackRenderer = CreateDefaultSubObject<USpriteRenderer>("Back");
	BackRenderer->SetupAttachment(Root);

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

