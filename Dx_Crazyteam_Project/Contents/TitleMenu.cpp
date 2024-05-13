#include "PreCompile.h"
#include "TitleMenu.h"
#include "EngineCore/Image.h"

TitleMenu::TitleMenu()
{
}

TitleMenu::~TitleMenu()
{
}

void TitleMenu::BeginPlay()
{
	Super::BeginPlay();
	UImage* TitleBackGround = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	TitleBackGround->AddToViewPort(1);
	TitleBackGround->SetSprite("login_scene_bg_LYS.png");
	TitleBackGround->SetScale({ 1280, 720 });

}

void TitleMenu::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
