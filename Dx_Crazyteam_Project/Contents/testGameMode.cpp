#include "PreCompile.h"
#include "TestGameMode.h"
#include "Village.h"
#include <EngineCore/EngineEditorGUI.h>
#include "MapDebugGUI.h"

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

#ifdef _DEBUG
	FVector MousePos = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(GEngine->EngineWindow.GetScreenMousePos());
	std::string Msgs = std::format("Mouse Position : {}", MousePos.ToString());
	UMapDebugGUI::PushMsg(Msgs);
	Msgs = std::format("y : {}, x : {}", AVillage::PlayerPosToPoint(MousePos).y, AVillage::PlayerPosToPoint(MousePos).x);
	UMapDebugGUI::PushMsg(Msgs);
#endif // _DEBUG
}

void ATestGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

#ifdef _DEBUG
	if (nullptr == MapDebugWindow)
	{
		MapDebugWindow = UEngineEditorGUI::CreateEditorWindow<UMapDebugGUI>("MapObject");
	}
	MapDebugWindow->On();
#endif // _DEBUG
}

void ATestGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
