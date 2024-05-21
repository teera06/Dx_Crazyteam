#include "PreCompile.h"
#include "VillageBlock1.h"

AVillageBlock1::AVillageBlock1() 
{
}

AVillageBlock1::~AVillageBlock1() 
{
}

void AVillageBlock1::BeginPlay()
{
	Super::BeginPlay();

	BreakSetOwner(this);

	Renderer->SetSprite("TownBlockRed.png");
}

void AVillageBlock1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

