#include "PreCompile.h"
#include "MapUI.h"
#include "EngineCore/Image.h"
#include "Game_Core.h"
#include "Packets.h"

//float AMapUI::GameTimeCheck = 1.0f;

AMapUI::AMapUI()
{
	if (false == IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UGame_Core::Net)
		{
			InitNet(UGame_Core::Net);
		}
	}

	CreateTime();
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

	ColonUI = CreateWidget<UImage>(GetWorld(), "GameStartUI");
	ColonUI->AddToViewPort(3);
	ColonUI->SetSprite("Time.png");
	ColonUI->SetPosition(FVector(340.0f, 220.0f, 0.0f));
	ColonUI->SetAutoSize(1.1f, true);
	ColonUI->SetActive(true);

	DelayCallBack(2.0f, [this]() { GameStartUI->SetActive(true); });
	DelayCallBack(4.0f, [this]() { GameStartUI->SetActive(false); });

	for (size_t i = 0; i < GameTimeerUI.size(); ++i)
	{
		GameTimeerUI[i] = CreateWidget<UImage>(GetWorld(), "GameTimeerUI");
		GameTimeerUI[i]->AddToViewPort(3);
		GameTimeerUI[i]->SetPosition(FVector(315.0f + static_cast<float>((i * 17)), 220.0f, 0.0f));
		GameTimeerUI[i]->SetAutoSize(1.0f, true);
		//GameTimeerUI[i]->SetActive(true);
	}
	GameTimeerUI[0]->SetSprite("GameTimer.png", 0);
	GameTimeerUI[1]->SetSprite("GameTimer.png", 2);
	GameTimeerUI[2]->SetSprite("GameTimer.png", 5);
	GameTimeerUI[3]->SetSprite("GameTimer.png", 9);
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

	//클라에서 신호보냄 (나만듬)
	if (Client_Create == true)
	{
		ClientSend();
		Client_Create = false;
	}

	//클라에서 신호받은 서버가 시간차를 센드
	if (Client_Send == true)
	{
		ServerSend();
		Client_Send = false;
	}


	if (SerVer_Send == false)
	{
		if (0 <= GameTimeCheck)
		{
			GameTimeCheck -= _DeltaTime;
			if (0 == MinUI && 0 == SecondUI && 0 == SecondUI2)
			{
				return;
			}

			if (0 > GameTimeCheck)
			{
				GameTimeCheck = 1.0f;

				if (0 < SecondUI2)
				{
					--SecondUI2;
					GameTimeerUI[3]->SetSprite("GameTimer.png", SecondUI2);
				}
				else if (0 == SecondUI2 && 0 < SecondUI)
				{
					SecondUI -= 1;
					SecondUI2 = 9;

					if (0 == SecondUI && 0 < MinUI)
					{
						MinUI -= 1;
						SecondUI = 5;
						GameTimeerUI[1]->SetSprite("GameTimer.png", MinUI);
					}
					GameTimeerUI[2]->SetSprite("GameTimer.png", SecondUI);
					GameTimeerUI[3]->SetSprite("GameTimer.png", SecondUI2);
				}
			}
		}
		else
		{
			return;
		}
	}
	else
	{
		Sub_Second;
		SecondUI2 -= Sub_Second;		
		SerVer_Send = false;
	}
}

void AMapUI::ClientSend()
{

	if (false == IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UGame_Core::Net)
		{
			InitNet(UGame_Core::Net);
		}
	}
	std::shared_ptr<UUIUpdatePacket> Packet = std::make_shared<UUIUpdatePacket>();
	Packet->ClientCreate = true;
	Send(Packet);
}

void AMapUI::ServerSend()
{

	if (false == IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UGame_Core::Net)
		{
			InitNet(UGame_Core::Net);
		}
	}
	std::shared_ptr<UUIUpdatePacket> Packet = std::make_shared<UUIUpdatePacket>();
	Packet->SerVerSend = true;
	Packet->Second_Tens = GetCreateTime();
	Send(Packet);
}


void AMapUI::SetPlayItemUI(int _ItemNumber)
{
	PlayerItemUI->SetSprite("Item", _ItemNumber);
}

float AMapUI::CreateTime()
{
	UEngineTime Time;
	MapTime_MilliSecond = Time.GetCurTime().MilliSecond;
	MapTime_Second = Time.GetCurTime().Second;
	return 0.0f;
}