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
}

void AMapSpriteObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

