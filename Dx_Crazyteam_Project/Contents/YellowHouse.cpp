#include "PreCompile.h"
#include "YellowHouse.h"

AYellowHouse::AYellowHouse() 
{
}

AYellowHouse::~AYellowHouse() 
{
}

void AYellowHouse::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("TownHouseYellow.png");
}

void AYellowHouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

