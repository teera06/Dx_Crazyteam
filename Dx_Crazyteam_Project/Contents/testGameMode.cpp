#include "PreCompile.h"
#include "testGameMode.h"

AtestGameMode::AtestGameMode()
{
}

AtestGameMode::~AtestGameMode()
{
}

void AtestGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AtestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AtestGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void AtestGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
