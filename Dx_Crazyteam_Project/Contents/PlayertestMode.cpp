#include "PreCompile.h"
#include "PlayertestMode.h"
#include "Player.h"

APlayertestMode::APlayertestMode()
{
}

APlayertestMode::~APlayertestMode()
{
}

void APlayertestMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -200.0f));

	std::shared_ptr<APlayer> Player1 = GetWorld()->SpawnActor<APlayer>("Player1");
	Player1->SetActorScale3D(FVector(100, 100, 1));
}

void APlayertestMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APlayertestMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void APlayertestMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
