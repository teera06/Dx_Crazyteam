#include "PreCompile.h"
#include "PlayertestMode.h"

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
