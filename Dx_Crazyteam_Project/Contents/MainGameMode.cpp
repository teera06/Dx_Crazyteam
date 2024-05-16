#include "PreCompile.h"
#include "MainGameMode.h"

#include <EngineCore/TextWidget.h>
#include <EnginePlatform/TextimeInput.h>

#include "Village.h"
#include "Player.h"

#include "ItemBubble.h"
#include "ItemRoller.h"

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


	{//Item

		std::shared_ptr<AItemBubble> Bubble = GetWorld()->SpawnActor<AItemBubble>("ItemTest");
		Bubble->SetActorLocation(Player1->GetActorLocation());

		std::shared_ptr<AItemRoller> Roller = GetWorld()->SpawnActor<AItemRoller>("ItemTest");
		Roller->SetActorLocation(FVector(100.0f, 100.0f, 0.0f));


	}

	ShowText = CreateWidget<UTextWidget>(GetWorld(), "ShowText");
	ShowText->SetFont("¸¼Àº °íµñ");
	ShowText->SetScale(30.0f);
	ShowText->SetColor(Color8Bit::Black);
	ShowText->SetPosition({ 0.0f ,0.0f });
	ShowText->SetFlag(FW1_LEFT);
	ShowText->AddToViewPort(11);


#ifdef _DEBUG
	InputOn();
#endif
}

void AMainGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	UTextimeInput::IMEInput();
	std::string Text = UTextimeInput::GetReadText();
	if (Text.size() > 0)
	{
		ShowText->SetText(Text);
	}
	else
	{
		ShowText->SetText(" ");
	}
}

void AMainGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void AMainGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
