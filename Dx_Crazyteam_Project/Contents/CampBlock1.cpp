#include "PreCompile.h"
#include "CampBlock1.h"

ACampBlock1::ACampBlock1() 
{
}

ACampBlock1::~ACampBlock1() 
{
}

void ACampBlock1::BeginPlay()
{
	Super::BeginPlay();

	BreakSetOwner(this);

	Renderer->SetSprite("CampBlock1.png");
}

void ACampBlock1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

