#include "PreCompile.h"

#include "TestLobbyMode.h"

ATestLobbyMode::ATestLobbyMode()
{
}

ATestLobbyMode::~ATestLobbyMode()
{
}

void ATestLobbyMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATestLobbyMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATestLobbyMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void ATestLobbyMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}