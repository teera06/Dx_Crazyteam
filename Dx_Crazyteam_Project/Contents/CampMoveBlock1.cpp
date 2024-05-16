#include "PreCompile.h"
#include "CampMoveBlock1.h"

ACampMoveBlock1::ACampMoveBlock1() 
{
}

ACampMoveBlock1::~ACampMoveBlock1() 
{
}

void ACampMoveBlock1::BeginPlay()
{
	Super::BeginPlay();

	BreakSetOwner(this);
	MoveSetOwner(this);

	Renderer->SetSprite("CampMoveBlock1.png");

}

void ACampMoveBlock1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

