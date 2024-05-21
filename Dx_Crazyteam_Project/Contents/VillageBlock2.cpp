#include "PreCompile.h"
#include "VillageBlock2.h"

AVillageBlock2::AVillageBlock2() 
{
}

AVillageBlock2::~AVillageBlock2() 
{
}

void AVillageBlock2::BeginPlay()
{
	Super::BeginPlay();

	BreakSetOwner(this);

	Renderer->SetSprite("TownBlockYellow.png");
}

void AVillageBlock2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

