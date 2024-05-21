#include "PreCompile.h"
#include "VillageMoveBlock.h"

VillageMoveBlock::VillageMoveBlock() 
{
}

VillageMoveBlock::~VillageMoveBlock() 
{
}

void VillageMoveBlock::BeginPlay()
{
	Super::BeginPlay();

	BreakSetOwner(this);
	MoveSetOwner(this);

	Renderer->SetSprite("TownBox.png");
}

void VillageMoveBlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

