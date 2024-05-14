#include "PreCompile.h"
#include "PlayertestMode.h"


APlayerTestMode::APlayerTestMode()
{
}

APlayerTestMode::~APlayerTestMode()
{
}

void APlayerTestMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -200.0f));

	Village = GetWorld()->SpawnActor<AVillage>("Village");
	SetCurMap(Village);

	Player1 = GetWorld()->SpawnActor<APlayer>("Player1", 0);
	Player1->SetCurGameMode(this);
	SetMainPlayer(Player1);


}

void APlayerTestMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APlayerTestMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void APlayerTestMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
