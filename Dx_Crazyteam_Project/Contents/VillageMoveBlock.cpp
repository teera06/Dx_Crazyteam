#include "PreCompile.h"
#include "VillageMoveBlock.h"

AVillageMoveBlock::AVillageMoveBlock() 
{
}

AVillageMoveBlock::~AVillageMoveBlock() 
{
}

void AVillageMoveBlock::BeginPlay()
{
	Super::BeginPlay();

	BreakSetOwner(this);
	MoveSetOwner(this);

	Renderer->SetSprite("TownBox.png");
}

void AVillageMoveBlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

