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

	PlayerInfoUI = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	PlayerInfoUI->AddToViewPort(1);
	PlayerInfoUI->SetSprite("Logo.png");
	PlayerInfoUI->SetScale({ 1280, 720 });
}

void StageUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
