#include "PreCompile.h"
#include "IntroMainMode.h"
#include "Intro.h"
#include "TitleMenu.h"

#include "LobbyMainMode.h"

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

	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		GEngine->ChangeLevel("LobbyMainMode");
	}
}

void AIntroMainMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
	GEngine->DestroyLevel("IntroMainMode");
	//Intro->Destroy();
}

void AIntroMainMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	GEngine->CreateLevel<ALobbyMainMode>("LobbyMainMode");
}
