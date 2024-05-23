#include "PreCompile.h"
#include "IntroMainMode.h"
#include "Intro.h"
#include "TitleMenu.h"

#include "LobbyMainMode.h"
#include "FontActor.h"
#include "ContentsMainDebugWin.h"

AIntroMainMode::AIntroMainMode()
{
}

AIntroMainMode::~AIntroMainMode()
{
}

void AIntroMainMode::BeginPlay()
{
	Super::BeginPlay();

	Intro = GetWorld()->SpawnActor<AIntro>("Intro");
}

void AIntroMainMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	/*if (true == UEngineInput::IsDown(VK_SPACE))
	{
		GEngine->ChangeLevel("LobbyMainMode");
	}*/
	// 스페이스바->로비 진입 막아둠 
	// [Start]클릭-> 로비 진입으로 변경
}

void AIntroMainMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
	UContentsMainDebugWin::SetIsLevel(true);

	GEngine->DestroyLevel("IntroMainMode");
	//Intro->Destroy();
}

void AIntroMainMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	//GEngine->CreateLevel<ALobbyMainMode>("LobbyMainMode");
}
