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
	GameTimeerUI.resize(4);

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

	GameStartUI = CreateWidget<UImage>(GetWorld(), "GameStartUI");
	GameStartUI->AddToViewPort(3);
	GameStartUI->SetSprite("GAMEStart.png");
	GameStartUI->SetPosition(FVector(-50.0f, 100.0f, 0.0f));
	GameStartUI->SetAutoSize(0.5f, true);
	GameStartUI->SetActive(false);

	DelayCallBack(2.0f, [this]() { GameStartUI->SetActive(true); });
	DelayCallBack(4.0f, [this]() { GameStartUI->SetActive(false); });

	for (size_t i = 0; i < GameTimeerUI.size(); ++i)
	{
		GameTimeerUI[i] = CreateWidget<UImage>(GetWorld(), "GameTimeerUI");
		GameTimeerUI[i]->AddToViewPort(3);
		GameTimeerUI[i]->SetPosition(FVector(310.0f + static_cast<float>((i * 20)), 255.0f, 0.0f));
		GameTimeerUI[i]->SetAutoSize(1.0f, true);
		//GameTimeerUI[i]->SetActive(true);
	}
	GameTimeerUI[0]->SetSprite("GameTimer.png", 0);
	GameTimeerUI[1]->SetSprite("GameTimer.png", 3);
	GameTimeerUI[2]->SetSprite("GameTimer.png", 0);
	GameTimeerUI[3]->SetSprite("GameTimer.png", 0);
}

void AMapUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (IsDown('P'))
	{
		for (size_t i = 0; i < PlayerUI.size(); ++i)
		{
			PlayerUI[i] = CreateWidget<UImage>(GetWorld(), "PlayerUI");
			PlayerUI[i]->SetSprite("CharatorSelect_Button_Bazzi_Click.bmp");
			PlayerUI[i]->AddToViewPort(20);
			PlayerUI[i]->SetAutoSize(0.7f, true);
			PlayerUI[i]->AddPosition(FVector(280.0f, 180 - static_cast<float>((i * 43)), 100.0f));
		}
	}

	if (0 <= GameTimerCheck)
	{
		GameTimerCheck -= _DeltaTime;
		switch (static_cast<int>(GameTimerCheck))
		{
		case 179:
			GameTimeerUI[1]->SetSprite("GameTimer.png", MinUI);
			//GameTimeerUI[2]->SetSprite("GameTimer.png", 5);
			//GameTimeerUI[3]->SetSprite("GameTimer.png", 9);
			break;
		case 119:
			GameTimeerUI[1]->SetSprite("GameTimer.png", MinUI);
			MinUI = 0;
			break;
		case 59:
			GameTimeerUI[1]->SetSprite("GameTimer.png", MinUI);
			break;
		default:
			if (0 < SecondUI2)
			{
				--SecondUI2;
			}
			break;
		}

		if (0 == SecondUI2)
		{
			if (0 < SecondUI)
			{
				if (0 == MinUI && 0 == SecondUI && 0 == SecondUI2)
				{
					return;
				}
				else
				{
					SecondUI2 = 9;
					GameTimeerUI[3]->SetSprite("GameTimer.png", SecondUI2);
				}
			}
			else if (0 == SecondUI)
			{
				SecondUI -= 1;
				GameTimeerUI[2]->SetSprite("GameTimer.png", SecondUI);
			}
			else
			{
				return;
			}
		}
	}
	else
	{
		return;
	}
}


void AMapUI::SetPlayItemUI(int _ItemNumber)
{
	PlayerItemUI->SetSprite("Item", _ItemNumber);
}