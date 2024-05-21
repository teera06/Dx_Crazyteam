#include "PreCompile.h"
#include "CampBlock2.h"

ACampBlock2::ACampBlock2() 
{
}

ACampBlock2::~ACampBlock2() 
{
}

void ACampBlock2::BeginPlay()
{
	Super::BeginPlay();

	BreakSetOwner(this);

	Renderer->SetSprite("CampBlock2.png");
}

void ACampBlock2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

