#include "PreCompile.h"
#include "CAGameMode.h"

ACAGameMode::ACAGameMode() 
{
}

ACAGameMode::~ACAGameMode() 
{
}

void ACAGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->DepthOn();
}

void ACAGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACAGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void ACAGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
