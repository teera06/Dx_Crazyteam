#include "PreCompile.h"
#include "Village.h"
#include <EngineCore/DefaultSceneComponent.h>

AVillage::AVillage()
{

}

AVillage::~AVillage()
{
}

void AVillage::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetOrder(EObjectOrder::Map);
	Renderer->SetSprite("BossStage_Back.png");
	Renderer->SetAutoSize(1.f, true);
}

void AVillage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

