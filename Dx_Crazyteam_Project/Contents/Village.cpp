#include "PreCompile.h"
#include "Village.h"
#include <EngineCore/DefaultSceneComponent.h>

AVillage::AVillage()
{
	BackMap = CreateDefaultSubObject<USpriteRenderer>("BackMap");
	BackMap->SetupAttachment(Root);
}

AVillage::~AVillage()
{
}

void AVillage::BeginPlay()
{
	Super::BeginPlay();

	BackMap->SetOrder(EObjectOrder::Map);
	BackMap->SetSprite("BossStage_Back.png");
	BackMap->SetAutoSize(1.f, true);
}

void AVillage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

