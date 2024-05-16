#include "PreCompile.h"
#include "IntroMainMode.h"

AIntroMainMode::AIntroMainMode()
{
}

AIntroMainMode::~AIntroMainMode()
{
}

void AIntroMainMode::BeginPlay()
{
	Super::BeginPlay();

}

void AIntroMainMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AIntroMainMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AIntroMainMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}
