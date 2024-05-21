#include "PreCompile.h"
#include "YellowHouse.h"

YellowHouse::YellowHouse() 
{
}

YellowHouse::~YellowHouse() 
{
}

void YellowHouse::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("TownHouseYellow.png");
}

void YellowHouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

