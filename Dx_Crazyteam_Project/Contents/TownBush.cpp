#include "PreCompile.h"
#include "TownBush.h"

ATownBush::ATownBush() 
{
}

ATownBush::~ATownBush() 
{
}

void ATownBush::BeginPlay()
{
	Super::BeginPlay();

	BreakSetOwner(this);

	Renderer->SetSprite("TownBush.png");
}

void ATownBush::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

