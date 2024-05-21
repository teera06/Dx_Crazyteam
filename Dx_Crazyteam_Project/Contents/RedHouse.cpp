#include "PreCompile.h"
#include "RedHouse.h"

RedHouse::RedHouse() 
{
}

RedHouse::~RedHouse() 
{
}

void RedHouse::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("TownHouseRed.png");
}

void RedHouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

