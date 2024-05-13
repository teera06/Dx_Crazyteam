#include "PreCompile.h"
#include "TestGameMode.h"

#include "Player.h"

ATestGameMode::ATestGameMode()
{
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -200.0f));

	std::shared_ptr<APlayer> TestPlayer = GetWorld()->SpawnActor<APlayer>("TestPlayer");
	TestPlayer->AddActorScale3D(FVector(100, 100, 1));
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATestGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void ATestGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
