#include "PreCompile.h"
#include "BlueHouse.h"

BlueHouse::BlueHouse() 
{
}

BlueHouse::~BlueHouse() 
{
}

void BlueHouse::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("TownHouseBlue.png");
}

void BlueHouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

