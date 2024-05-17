#include "PreCompile.h"
#include "MapUI.h"
#include "EngineCore/Image.h"

AMapUI::AMapUI()
{
}

AMapUI::~AMapUI()
{
}

void AMapUI::BeginPlay()
{
	Super::BeginPlay();
	InputOn();
	PlayerUI.resize(8);

	MapPlayUI = CreateWidget<UImage>(GetWorld(), "MapPlayUI");
	MapPlayUI->AddToViewPort(3);
	MapPlayUI->SetSprite("MapPlayUI.png");
	MapPlayUI->SetPosition(FVector(0.0f, 0.0f, 0.0f));
	MapPlayUI->SetAutoSize(1.0f, true);

	PlayerItemUI = CreateWidget<UImage>(GetWorld(), "PlayerItemUI");
	PlayerItemUI->AddToViewPort(3);
	PlayerItemUI->SetAutoSize(1.0f, true);
	PlayerItemUI->SetSprite("Niddle.png", 2);
	PlayerItemUI->SetPosition(FVector(290.0f, -230.0f, 0.0f));
	PlayerItemUI->SetActive(true);
}

void AMapUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (IsDown('P'))
	{
		for (size_t i = 0; i < PlayerUI.size(); i++)
		{
			PlayerUI[i] = CreateWidget<UImage>(GetWorld(), "PlayerUI");
			PlayerUI[i]->SetSprite("CharatorSelect_Button_Bazzi_Click.bmp");
			PlayerUI[i]->AddToViewPort(20);
			PlayerUI[i]->SetAutoSize(0.7f, true);
			PlayerUI[i]->AddPosition(FVector(280.0f, 180 - static_cast<float>((i * 43)), 100.0f));
		}
	}
}


void AMapUI::SetPlayItemUI(int _ItemNumber)
{
	PlayerItemUI->SetSprite("Item", _ItemNumber);
}