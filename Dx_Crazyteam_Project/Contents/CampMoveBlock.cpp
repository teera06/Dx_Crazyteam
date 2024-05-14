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
	FrontRenderer->SetSprite("CampMoveBlockFront.png");
	BackRenderer->SetSprite("CampMoveBlockBack");
}

void ACampMoveBlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
