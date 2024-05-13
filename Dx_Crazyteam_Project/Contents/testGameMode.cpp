#include "PreCompile.h"
#include "TestGameMode.h"
#include "Village.h"

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
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -400.0f));

	std::shared_ptr<AVillage> Village = GetWorld()->SpawnActor<AVillage>("Village");

	Player1 = GetWorld()->SpawnActor<APlayer>("Player1", 0);
	Player1->SetActorLocation(FVector(-80.f, 20.f, -100.f));
	Player1->SetActorScale3D(FVector(100, 100, 1));
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
