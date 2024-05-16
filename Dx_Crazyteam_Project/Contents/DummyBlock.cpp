#include "PreCompile.h"
#include "DummyBlock.h"

ADummyBlock::ADummyBlock() 
{
}

ADummyBlock::~ADummyBlock() 
{
}

void ADummyBlock::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetActive(false);
}

void ADummyBlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

