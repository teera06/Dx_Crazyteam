#include "PreCompile.h"
#include "StageUI.h"
#include "EngineCore/Image.h"

StageUI::StageUI()
{
}

StageUI::~StageUI()
{
}

void StageUI::BeginPlay()
{
	Super::BeginPlay();

	UImage* TitleBackGround = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	TitleBackGround->AddToViewPort(1);
	TitleBackGround->SetSprite("Logo.png");
	TitleBackGround->SetScale({ 1280, 720 });
}

void StageUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
