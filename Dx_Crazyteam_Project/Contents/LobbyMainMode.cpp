#include "PreCompile.h"
#include "LobbyMainMode.h"

ALobbyMainMode::ALobbyMainMode()
{
}

ALobbyMainMode::~ALobbyMainMode()
{
}

void ALobbyMainMode::BeginPlay()
{
	Super::BeginPlay();

}


void ALobbyMainMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void ALobbyMainMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ALobbyMainMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}
