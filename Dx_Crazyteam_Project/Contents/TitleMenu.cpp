#include "PreCompile.h"
#include "TitleMenu.h"
#include "EngineCore/Image.h"

ATitleMenu::ATitleMenu()
{
}

ATitleMenu::~ATitleMenu()
{
}

void ATitleMenu::BeginPlay()
{
	Super::BeginPlay();

	UImage* TitleBackGround = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	TitleBackGround->AddToViewPort(1);
	TitleBackGround->SetSprite("Logo.png");
	TitleBackGround->SetScale({ 1280, 720 });

}

void ATitleMenu::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
