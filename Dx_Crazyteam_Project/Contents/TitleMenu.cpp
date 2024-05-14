#include "PreCompile.h"
#include "TitleMenu.h"
#include "UitestMonde.h"
#include "PlayLobby.h"

#include "EngineCore/Image.h"
#include "EngineCore/TextWidget.h"

ATitleMenu::ATitleMenu()
{

}

ATitleMenu::~ATitleMenu()
{
}

void ATitleMenu::BeginPlay()
{
	Super::BeginPlay();
	InputOn();
	UIGameMode = dynamic_cast<AUitestMonde*>(GetWorld()->GetGameMode().get());

	UImage* TitleBackGround = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	TitleBackGround->AddToViewPort(1);
	TitleBackGround->SetSprite("Logo.png");
	TitleBackGround->SetScale({ 1280, 720 });
	TitleBackGround->SetActive(true);

	UImage* GameStartButton = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	GameStartButton->AddToViewPort(1);
	GameStartButton->SetSprite("map_village_object5.png");
	GameStartButton->SetScale({ 150, 150 });
	GameStartButton->SetActive(true);

	GameStartButton->SetHover([=]
		{
			if (IsDown(VK_LBUTTON))
			{
				TitleBackGround->SetActive(false);
				GameStartButton->SetActive(false);
				UIGameMode->GetPlayLobby()->SetIsActive(true);
			}
		});

	TestText = CreateWidget<UTextWidget>(GetWorld(), "Text");
	TestText->AddToViewPort(2);
	TestText->SetText("Test");
	TestText->SetFont("±Ã¼­");
	
}

void ATitleMenu::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
