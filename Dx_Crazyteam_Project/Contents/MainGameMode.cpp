#include "PreCompile.h"
#include "MainGameMode.h"


#include "Village.h"
#include <EngineCore/EngineEditorGUI.h>
#include "MapDebugGUI.h"
#include "Player.h"

AMainGameMode::AMainGameMode()
{
}

AMainGameMode::~AMainGameMode()
{
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -400.0f));

	std::shared_ptr<AVillage> Village = GetWorld()->SpawnActor<AVillage>("Village");

	Player1 = GetWorld()->SpawnActor<APlayer>("Player1", 0);
	Player1->SetActorLocation(FVector(-80.f, 20.f, -100.f));
}

void AMainGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMainGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void AMainGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
