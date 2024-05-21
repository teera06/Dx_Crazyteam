#include "PreCompile.h"
#include "CampBlock3.h"

ACampBlock3::ACampBlock3() 
{
}

ACampBlock3::~ACampBlock3() 
{
}

void ACampBlock3::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("CampBlock5.png");
}

void ACampBlock3::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

