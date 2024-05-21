#include "PreCompile.h"
#include "BlueHouse.h"

ABlueHouse::ABlueHouse() 
{
}

ABlueHouse::~ABlueHouse() 
{
}

void ABlueHouse::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("TownHouseBlue.png");
}

void ABlueHouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

