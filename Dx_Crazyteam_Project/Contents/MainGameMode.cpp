#include "PreCompile.h"
#include "MainGameMode.h"


#include "Village.h"
#include <EngineCore/EngineEditorGUI.h>
#include "MapDebugGUI.h"
#include "Player.h"
#include "Camp.h"
#include "WaterCourse.h"

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

	std::shared_ptr<ACamp> Camp = GetWorld()->SpawnActor<ACamp>("Camp");
	SetCurMap(Camp);
	Camp->SetCurGameMode(this);

	Player1 = GetWorld()->SpawnActor<APlayer>("Player1", 0);
	Player1->SetCurGameMode(this);
	SetMainPlayer(Player1);

#ifdef _DEBUG
	InputOn();
#endif
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
