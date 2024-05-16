#include "PreCompile.h"
#include "CampBlock.h"

ACampBlock::ACampBlock() 
{
}

ACampBlock::~ACampBlock() 
{
}

void ACampBlock::BeginPlay()
{
	Super::BeginPlay();

	BreakSetOwner(this);

	FrontRenderer->SetSprite("CampBlockFront.png");
	BackRenderer->SetSprite("CampBlockBack.png");

	FrontRenderer->SetAutoSize(1.f, true);
	BackRenderer->SetAutoSize(1.f, true);
}

void ACampBlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

