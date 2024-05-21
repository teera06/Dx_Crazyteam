#include "PreCompile.h"
#include "RedHouse.h"

ARedHouse::ARedHouse() 
{
}

ARedHouse::~ARedHouse() 
{
}

void ARedHouse::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("TownHouseRed.png");
}

void ARedHouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

