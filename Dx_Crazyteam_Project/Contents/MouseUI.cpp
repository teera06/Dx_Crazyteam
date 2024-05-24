#include "PreCompile.h"
#include "MouseUI.h"
#include <EngineCore/Image.h>
#include "CAGameMode.h"

MouseUI::MouseUI()
{
	GEngine->EngineWindow.CursorOff(); //커서 끄기
	UDefaultSceneComponent* Default = CreateDefaultSubObject<UDefaultSceneComponent>("Default");

	SetRoot(Default);

}

MouseUI::~MouseUI()
{

}

void MouseUI::BeginPlay()
{
	Super::BeginPlay();

	MouseRender = CreateWidget<UImage>(GetWorld(), "MouseUI");
	MouseRender->SetSprite("MouseNormal.png");
	MouseRender->SetAutoSize(1.0f, true);
	MouseRender->AddToViewPort(17);

}

void MouseUI::SetMousePos()
{
	FVector CamPos = GetWorld()->GetMainCamera()->GetActorLocation();
	FVector MPos = GEngine->EngineWindow.GetScreenMousePos();
	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();
	FVector TargetPos = FVector(CamPos.X, CamPos.Y, 0.0f) + FVector(MPos.X + 10 - WindowScale.hX(), -(MPos.Y - WindowScale.hY() + 14), 0.0f);


	ACAGameMode* PlayLevel = dynamic_cast<ACAGameMode*>(GetWorld()->GetGameMode().get());

	if (nullptr != PlayLevel)
	{
		MouseRender->SetWidgetLocation(TargetPos - FVector{ 80.0f, 1.0f, 0.0f });
	}
	else
	{
		MouseRender->SetWidgetLocation(TargetPos);
	}
}


void MouseUI::Tick(float _DeltaTIme)
{
	Super::Tick(_DeltaTIme);
	SetMousePos(); // 따라다니기 

}
