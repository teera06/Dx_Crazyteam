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
	FrontRenderer->SetActive(false);
	BackRenderer->SetActive(false);
}

void ADummyBlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

