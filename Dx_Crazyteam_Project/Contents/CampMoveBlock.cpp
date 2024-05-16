#include "PreCompile.h"
#include "CampMoveBlock.h"

ACampMoveBlock::ACampMoveBlock() 
{
}

ACampMoveBlock::~ACampMoveBlock() 
{
}

void ACampMoveBlock::BeginPlay()
{
	Super::BeginPlay();

	BreakSetOwner(this);
	MoveSetOwner(this);

	FrontRenderer->SetSprite("CampMoveBlockFront.png");
	BackRenderer->SetSprite("CampMoveBlockBack.png");

	FrontRenderer->SetAutoSize(1.f, true);
	BackRenderer->SetAutoSize(1.f, true);
}

void ACampMoveBlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

