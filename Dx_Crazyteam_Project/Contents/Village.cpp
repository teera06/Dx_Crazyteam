#include "PreCompile.h"
#include "Village.h"
#include <EngineCore/EngineTexture.h>
#include <EngineCore/DefaultSceneComponent.h>

AVillage::AVillage()
{
	BackMap = CreateDefaultSubObject<USpriteRenderer>("BackMap");
	BackMap->SetupAttachment(Root);

	ColMap = CreateDefaultSubObject<USpriteRenderer>("ColMap");
	ColMap->SetupAttachment(Root);
}

AVillage::~AVillage()
{
}

void AVillage::BeginPlay()
{
	Super::BeginPlay();

	BackMap->SetSprite("BossStage_Back.png");
	BackMap->SetAutoSize(1.f, true);
	BackMap->AddPosition(FVector(-80.f, 20.f, 0.f));

	ColMap->SetSprite("ColMapDefault.png");
	ColMap->SetAutoSize(1.f, true);
}

void AVillage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
