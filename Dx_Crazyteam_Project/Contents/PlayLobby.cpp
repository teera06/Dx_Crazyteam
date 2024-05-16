#include "PreCompile.h"
#include "PlayLobby.h"

#include "EngineCore/Image.h"

APlayLobby::APlayLobby()
{
	Collision0 = CreateDefaultSubObject<UCollision>("Collision");
	Collision0->SetScale({ 63.f,42.f });
	Collision0->SetPosition({ 122.0f,162.0f });
	Collision0->SetCollisionGroup(ECollisionOrder::Player);
	Collision0->SetCollisionType(ECollisionType::Rect);
}

APlayLobby::~APlayLobby()
{
}

void APlayLobby::BeginPlay()
{
	Super::BeginPlay();
	InputOn();
	LobbyPlayer.resize(9);

	PlayLobbyUI = CreateWidget<UImage>(GetWorld(), "PlayLobbyUI");
	PlayLobbyUI->AddToViewPort(10);
	PlayLobbyUI->SetSprite("Waiting.png");
	PlayLobbyUI->SetScale({ 800, 600 });
	PlayLobbyUI->SetActive(true);

	for (int i = 0; i < 4; i++)
	{
		UImage* Room = CreateWidget<UImage>(GetWorld(), "Room");
		Room->AddToViewPort(12);
		Room->SetSprite("Room_0.png");
		Room->SetAutoSize(1.0f, true);
		Room->SetPosition(FVector(-324.f + 106.f * i, 157.f));
		Room->SetActive(true);
		RoomVector.push_back(Room);
	}

	for (int i = 0; i < 4; i++)
	{
		UImage* Room = CreateWidget<UImage>(GetWorld(), "Room");
		Room->AddToViewPort(12);
		Room->SetSprite("Room_0.png");
		Room->SetAutoSize(1.0f, true);
		Room->SetPosition(FVector(-324.f + 106.f * i, 11.f));
		Room->SetActive(true);
		RoomVector.push_back(Room);
	}

	//시작 버튼
	GameStart = CreateWidget<UImage>(GetWorld(), "GameStart");
	GameStart->CreateAnimation("UnHover", "StartBt_1.png", 0.1f, false, 0, 0);
	GameStart->CreateAnimation("Hover", "StartBT", 0.1f, true, 0, 1);
	GameStart->CreateAnimation("Down", "StartBt_3.png", 0.1f, false, 0, 0);
	GameStart->AddToViewPort(10);
	GameStart->SetSprite("StartBt_1.png");
	GameStart->SetScale({ 190,52  });
	GameStart->SetPosition({ 209,-223 });
	GameStart->SetActive(true);
	GameStart->ChangeAnimation("UnHover");

	//캐릭터 선택창
	RandomBT = CreateWidget<UImage>(GetWorld(), "RandomBT");
	RandomBT->CreateAnimation("UnHover", "CharatorSelect_Button_Random_Normal.bmp", 0.1f, false, 0, 0);
	RandomBT->CreateAnimation("Hover", "CharatorSelect_Button_Random_Hover.bmp", 0.1f, false, 0, 0);
	RandomBT->CreateAnimation("Down", "CharatorSelect_Button_Random_Click.bmp", 0.1f, false, 0, 0);
	RandomBT->CreateAnimation("Up", "CharatorSelect_Button_Random_Pick.bmp", 0.1f, false, 0, 0);
	RandomBT->AddToViewPort(11);
	RandomBT->SetSprite("CharatorSelect_Button_Random_Normal.bmp");
	RandomBT->SetScale({ 65.f,43.f });
	RandomBT->SetPosition({ 122.0f,163.0f });
	RandomBT->SetActive(true);
	
	DaoBT = CreateWidget<UImage>(GetWorld(), "DaoBT");
	DaoBT->CreateAnimation("UnHover", "CharatorSelect_Button_Dao_Normal.bmp", 0.1f, false, 0, 0);
	DaoBT->CreateAnimation("Hover", "CharatorSelect_Button_Dao_Hover.bmp", 0.1f, false, 0, 0);
	DaoBT->CreateAnimation("Down", "CharatorSelect_Button_Dao_Click.bmp", 0.1f, false, 0, 0);
	DaoBT->CreateAnimation("Up", "CharatorSelect_Button_Dao_Pick.bmp", 0.1f, false, 0, 0);
	DaoBT->AddToViewPort(11);
	DaoBT->SetSprite("CharatorSelect_Button_Dao_Pick.bmp");
	DaoBT->SetScale({ 65.f,43.f });
	DaoBT->SetPosition({ 194.0f,163.0f });
	DaoBT->SetActive(true);

	DizniBT = CreateWidget<UImage>(GetWorld(), "DizniBT");
	DizniBT->CreateAnimation("UnHover", "CharatorSelect_Button_Dizni_Normal.bmp", 0.1f, false, 0, 0);
	DizniBT->CreateAnimation("Hover", "CharatorSelect_Button_Dizni_Hover.bmp", 0.1f, false, 0, 0);
	DizniBT->CreateAnimation("Down", "CharatorSelect_Button_Dizni_Click.bmp", 0.1f, false, 0, 0);
	DizniBT->AddToViewPort(11);
	DizniBT->SetSprite("CharatorSelect_Button_Dizni_Normal.bmp");
	DizniBT->SetScale({ 65.f,43.f });
	DizniBT->SetPosition({ 266.0f,163.0f });
	DizniBT->SetActive(true);

	MosBT = CreateWidget<UImage>(GetWorld(), "MosBT");
	MosBT->CreateAnimation("UnHover", "CharatorSelect_Button_Mos_Normal.bmp", 0.1f, false, 0, 0);
	MosBT->CreateAnimation("Hover", "CharatorSelect_Button_Mos_Hover.bmp", 0.1f, false, 0, 0);
	MosBT->CreateAnimation("Down", "CharatorSelect_Button_Mos_Click.bmp", 0.1f, false, 0, 0);
	MosBT->AddToViewPort(11);
	MosBT->SetSprite("CharatorSelect_Button_Mos_Normal.bmp");
	MosBT->SetScale({ 65.f,43.f });
	MosBT->SetPosition({ 338.0f,163.0f });
	MosBT->SetActive(true);

	EthiBT = CreateWidget<UImage>(GetWorld(), "EthiBT");
	EthiBT->CreateAnimation("UnHover", "CharatorSelect_Button_Ethi_Normal.bmp", 0.1f, false, 0, 0);
	EthiBT->CreateAnimation("Hover", "CharatorSelect_Button_Ethi_Hover.bmp", 0.1f, false, 0, 0);
	EthiBT->CreateAnimation("Down", "CharatorSelect_Button_Ethi_Click.bmp", 0.1f, false, 0, 0);
	EthiBT->AddToViewPort(11);
	EthiBT->SetSprite("CharatorSelect_Button_Ethi_Normal.bmp");
	EthiBT->SetScale({ 65.f,43.f });
	EthiBT->SetPosition({ 122.0f,114.0f });
	EthiBT->SetActive(true);

	MaridBT = CreateWidget<UImage>(GetWorld(), "MosBT");
	MaridBT->CreateAnimation("UnHover", "CharatorSelect_Button_Marid_Normal.bmp", 0.1f, false, 0, 0);
	MaridBT->CreateAnimation("Hover", "CharatorSelect_Button_Marid_Hover.bmp", 0.1f, false, 0, 0);
	MaridBT->CreateAnimation("Down", "CharatorSelect_Button_Marid_Click.bmp", 0.1f, false, 0, 0);
	MaridBT->CreateAnimation("Up", "CharatorSelect_Button_Marid_Pick.bmp", 0.1f, false, 0, 0);
	MaridBT->AddToViewPort(11);
	MaridBT->SetSprite("CharatorSelect_Button_Marid_Normal.bmp");
	MaridBT->SetScale({ 65.f,43.f });
	MaridBT->SetPosition({ 194.0f,114.0f });
	MaridBT->SetActive(true);

	BazziBT = CreateWidget<UImage>(GetWorld(), "MosBT");
	BazziBT->CreateAnimation("UnHover", "CharatorSelect_Button_Bazzi_Normal.bmp", 0.1f, false, 0, 0);
	BazziBT->CreateAnimation("Hover", "CharatorSelect_Button_Bazzi_Hover.bmp", 0.1f, false, 0, 0);
	BazziBT->CreateAnimation("Down", "CharatorSelect_Button_Bazzi_Click.bmp", 0.1f, false, 0, 0);
	BazziBT->CreateAnimation("Up", "CharatorSelect_Button_Bazzi_Pick.bmp", 0.1f, false, 0, 0);
	BazziBT->AddToViewPort(11);
	BazziBT->SetSprite("CharatorSelect_Button_Bazzi_Normal.bmp");
	BazziBT->SetScale({ 65.f,43.f });
	BazziBT->SetPosition({ 266.0f,114.0f });
	BazziBT->SetActive(true);

	UniBT = CreateWidget<UImage>(GetWorld(), "UniBT");
	UniBT->CreateAnimation("UnHover", "CharatorSelect_Button_Uni_Normal.bmp", 0.1f, false, 0, 0);
	UniBT->CreateAnimation("Hover", "CharatorSelect_Button_Uni_Hover.bmp", 0.1f, false, 0, 0);
	UniBT->CreateAnimation("Down", "CharatorSelect_Button_Uni_Click.bmp", 0.1f, false, 0, 0);
	UniBT->AddToViewPort(11);
	UniBT->SetSprite("CharatorSelect_Button_Uni_Normal.bmp");
	UniBT->SetScale({ 65.f,43.f });
	UniBT->SetPosition({ 338.0f,114.0f });
	UniBT->SetActive(true);

	KephiBT = CreateWidget<UImage>(GetWorld(), "MosBT");
	KephiBT->CreateAnimation("UnHover", "CharatorSelect_Button_Kephi_Normal.bmp", 0.1f, false, 0, 0);
	KephiBT->CreateAnimation("Hover", "CharatorSelect_Button_Kephi_Hover.bmp", 0.1f, false, 0, 0);
	KephiBT->CreateAnimation("Down", "CharatorSelect_Button_Kephi_Click.bmp", 0.1f, false, 0, 0);
	KephiBT->CreateAnimation("Up", "CharatorSelect_Button_Kephi_Pick.bmp", 0.1f, false, 0, 0);
	KephiBT->AddToViewPort(11);
	KephiBT->SetSprite("CharatorSelect_Button_Kephi_Normal.bmp");
	KephiBT->SetScale({ 65.f,43.f });
	KephiBT->SetPosition({ 122.0f,65.0f });
	KephiBT->SetActive(true);

	SuBT = CreateWidget<UImage>(GetWorld(), "SuBT");
	SuBT->CreateAnimation("UnHover", "CharatorSelect_Button_Su_Normal.bmp", 0.1f, false, 0, 0);
	SuBT->CreateAnimation("Hover", "CharatorSelect_Button_Su_Hover.bmp", 0.1f, false, 0, 0);
	SuBT->CreateAnimation("Down", "CharatorSelect_Button_Su_Click.bmp", 0.1f, false, 0, 0);
	SuBT->AddToViewPort(11);
	SuBT->SetSprite("CharatorSelect_Button_Su_Normal.bmp");
	SuBT->SetScale({ 65.f,43.f });
	SuBT->SetPosition({ 194.0f,65.0f });
	SuBT->SetActive(true);

	HooUBT = CreateWidget<UImage>(GetWorld(), "MosBT");
	HooUBT->CreateAnimation("UnHover", "CharatorSelect_Button_HooU_Normal.bmp", 0.1f, false, 0, 0);
	HooUBT->CreateAnimation("Hover", "CharatorSelect_Button_HooU_Hover.bmp", 0.1f, false, 0, 0);
	HooUBT->CreateAnimation("Down", "CharatorSelect_Button_HooU_Click.bmp", 0.1f, false, 0, 0);
	HooUBT->AddToViewPort(11);
	HooUBT->SetSprite("CharatorSelect_Button_HooU_Normal.bmp");
	HooUBT->SetScale({ 65.f,43.f });
	HooUBT->SetPosition({ 266.0f,65.0f });
	HooUBT->SetActive(true);

	RayBT = CreateWidget<UImage>(GetWorld(), "RayBT");
	RayBT->CreateAnimation("UnHover", "CharatorSelect_Button_Ray_Normal.bmp", 0.1f, false, 0, 0);
	RayBT->CreateAnimation("Hover", "CharatorSelect_Button_Ray_Hover.bmp", 0.1f, false, 0, 0);
	RayBT->CreateAnimation("Down", "CharatorSelect_Button_Ray_Click.bmp", 0.1f, false, 0, 0);
	RayBT->AddToViewPort(11);
	RayBT->SetSprite("CharatorSelect_Button_Ray_Normal.bmp");
	RayBT->SetScale({ 65.f,43.f });
	RayBT->SetPosition({ 338.0f,65.0f });
	RayBT->SetActive(true);

	Randomex = CreateWidget<UImage>(GetWorld(), "Randomex");
	Randomex->AddToViewPort(11);
	Randomex->SetSprite("CharatorSelect_Outline_Random.bmp");
	Randomex->SetScale({ 281.f, 80.f });
	Randomex->SetPosition({ 230.0f,237.0f });
	Randomex->SetActive(true);

	Daoex = CreateWidget<UImage>(GetWorld(), "Daoex");
	Daoex->AddToViewPort(11);
	Daoex->SetSprite("CharatorSelect_Outline_Dao.bmp");
	Daoex->SetScale({ 281.f, 80.f });
	Daoex->SetPosition({ 230.0f,237.0f });
	Daoex->SetActive(false);

	Maridex = CreateWidget<UImage>(GetWorld(), "Maridex");
	Maridex->AddToViewPort(11);
	Maridex->SetSprite("CharatorSelect_Outline_Marid.bmp");
	Maridex->SetScale({ 281.f, 80.f });
	Maridex->SetPosition({ 230.0f,237.0f });
	Maridex->SetActive(false);

	Kephiex = CreateWidget<UImage>(GetWorld(), "Kephiex");
	Kephiex->AddToViewPort(11);
	Kephiex->SetSprite("CharatorSelect_Outline_Kephi.bmp");
	Kephiex->SetScale({ 281.f, 80.f });
	Kephiex->SetPosition({ 230.0f,237.0f });
	Kephiex->SetActive(false);

	Bazziex = CreateWidget<UImage>(GetWorld(), "Bazziex");
	Bazziex->AddToViewPort(11);
	Bazziex->SetSprite("CharatorSelect_Outline_Bazzi.bmp");
	Bazziex->SetScale({ 281.f, 80.f });
	Bazziex->SetPosition({ 230.0f,237.0f });
	Bazziex->SetActive(false);

	// 선택한 캐릭터
	SelectCharacter = DaoBT;
}

void APlayLobby::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	PlayLobbyUI->SetActive(true);


	{
		GameStart->SetUnHover([=] {
			GameStart->ChangeAnimation("UnHover");
			SwitchON = false;
			});
		GameStart->SetHover([=] {
			if (GameStart->IsCurAnimationEnd() == true)
			{
				GameStart->ChangeAnimation("Hover");
			}
			});
		GameStart->SetDown([=] {
			GameStart->ChangeAnimation("Down");
			});

	}

	{
		RandomBT->SetUnHover([=] {
			if ("UP" != RandomBT->GetUiAniName())
			{
				RandomBT->ChangeAnimation("UnHover");
			}
				SwitchON = false;
			});
		RandomBT->SetHover([=] {
			{
				if (false == SwitchON && "UP" != RandomBT->GetUiAniName())
				{
					RandomBT->ChangeAnimation("Hover");
					Randomex->SetActive(true);
					SwitchON = true;
				}
				else if (IsDown(VK_LBUTTON) && true == SwitchON)
				{
					RandomBT->ChangeAnimation("Down");
				}
				else if (IsUp(VK_LBUTTON))
				{
					SwapSelectCharacter(RandomBT);
					//RandomBT->ChangeAnimation("Up");
				}
			}
			});
	}

	{
		DaoBT->SetUnHover([=] {
			if ("UP" != DaoBT->GetUiAniName())
			{
				DaoBT->ChangeAnimation("UnHover");
				Daoex->SetActive(false);
			}
				SwitchON = false;
			});
		DaoBT->SetHover([=] {
			{
				if (false == SwitchON && "UP" != DaoBT->GetUiAniName())
				{
					DaoBT->ChangeAnimation("Hover");
					Daoex->SetActive(true);
					SwitchON = true;

				}
				else if (IsDown(VK_LBUTTON) && true == SwitchON)
				{
					DaoBT->ChangeAnimation("Down");
				}
				else if (IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = true;
					SwapSelectCharacter(DaoBT);
					//DaoBT->ChangeAnimation("Up");
				}

			}
			});
	}
	//{
	//	DizniBT->SetUnHover([=] {
	//		DizniBT->ChangeAnimation("UnHover");
	//		SwitchON = false;
	//		});
	//	DizniBT->SetHover([=] {
	//		{
	//			if (false == SwitchON)
	//			{
	//				DizniBT->ChangeAnimation("Hover");
	//				SwitchON = true;

	//			}
	//			else if (IsDown(VK_LBUTTON) && true == SwitchON)
	//			{
	//				DizniBT->ChangeAnimation("Down");

	//			}
	//		}
	//		});
	//}
	//{
	//	MosBT->SetUnHover([=] {
	//		MosBT->ChangeAnimation("UnHover");
	//		SwitchON = false;
	//		});
	//	MosBT->SetHover([=] {
	//		{
	//			if (false == SwitchON)
	//			{
	//				MosBT->ChangeAnimation("Hover");
	//				SwitchON = true;

	//			}
	//			else if (IsDown(VK_LBUTTON) && true == SwitchON)
	//			{
	//				MosBT->ChangeAnimation("Down");

	//			}
	//		}
	//		});
	//}
	//{
	//	EthiBT->SetUnHover([=] {
	//		EthiBT->ChangeAnimation("UnHover");
	//		SwitchON = false;
	//		});
	//	EthiBT->SetHover([=] {
	//		{
	//			if (false == SwitchON)
	//			{
	//				EthiBT->ChangeAnimation("Hover");
	//				SwitchON = true;

	//			}
	//			else if (IsDown(VK_LBUTTON) && true == SwitchON)
	//			{
	//				EthiBT->ChangeAnimation("Down");

	//			}
	//		}
	//		});
	//}
	//{
	//	MaridBT->SetUnHover([=] {
	//		MaridBT->ChangeAnimation("UnHover");
	//		SwitchON = false;
	//		Maridex->SetActive(false);
	//		});
	//	MaridBT->SetHover([=] {
	//		{
	//			if (false == SwitchON)
	//			{
	//				MaridBT->ChangeAnimation("Hover");
	//				Maridex->SetActive(true);
	//				SwitchON = true;

	//			}
	//			else if (IsDown(VK_LBUTTON) && true == SwitchON)
	//			{
	//				MaridBT->ChangeAnimation("Down");

	//			}
	//			else if (IsUp(VK_LBUTTON))
	//			{
	//				MaridBT->ChangeAnimation("Up");
	//			}

	//		}
	//		});
	//}
	//{
	//	BazziBT->SetUnHover([=] {
	//		BazziBT->ChangeAnimation("UnHover");
	//		SwitchON = false;
	//		Bazziex->SetActive(false);
	//		});
	//	BazziBT->SetHover([=] {
	//		{
	//			if (false == SwitchON)
	//			{
	//				BazziBT->ChangeAnimation("Hover");
	//				Bazziex->SetActive(true);
	//				SwitchON = true;

	//			}
	//			else if (IsDown(VK_LBUTTON) && true == SwitchON)
	//			{
	//				BazziBT->ChangeAnimation("Down");

	//			}
	//			else if (IsUp(VK_LBUTTON))
	//			{
	//				BazziBT->ChangeAnimation("Up");
	//			}
	//		}
	//		});
	//}
	//{
	//	UniBT->SetUnHover([=] {
	//		UniBT->ChangeAnimation("UnHover");
	//		SwitchON = false;
	//		});
	//	UniBT->SetHover([=] {
	//		{
	//			if (false == SwitchON)
	//			{
	//				UniBT->ChangeAnimation("Hover");
	//				SwitchON = true;

	//			}
	//			else if (IsDown(VK_LBUTTON) && true == SwitchON)
	//			{
	//				UniBT->ChangeAnimation("Down");

	//			}
	//		}
	//		});
	//}
	//{
	//	KephiBT->SetUnHover([=] {
	//		KephiBT->ChangeAnimation("UnHover");
	//		SwitchON = false;
	//		Kephiex->SetActive(false);
	//		});
	//	KephiBT->SetHover([=] {
	//		{
	//			if (false == SwitchON)
	//			{
	//				KephiBT->ChangeAnimation("Hover");
	//				Kephiex->SetActive(true);
	//				SwitchON = true;

	//			}
	//			else if (IsDown(VK_LBUTTON) && true == SwitchON)
	//			{
	//				KephiBT->ChangeAnimation("Down");

	//			}
	//	
	//			else if (IsUp(VK_LBUTTON))
	//			{
	//				KephiBT->ChangeAnimation("Up");
	//			}
	//		}
	//		});
	//}
	//{
	//	SuBT->SetUnHover([=] {
	//		SuBT->ChangeAnimation("UnHover");
	//		SwitchON = false;
	//		});
	//	SuBT->SetHover([=] {
	//		{
	//			if (false == SwitchON)
	//			{
	//				SuBT->ChangeAnimation("Hover");
	//				SwitchON = true;

	//			}
	//			else if (IsDown(VK_LBUTTON) && true == SwitchON)
	//			{
	//				SuBT->ChangeAnimation("Down");

	//			}
	//		}
	//		});
	//}
	//{
	//	HooUBT->SetUnHover([=] {
	//		HooUBT->ChangeAnimation("UnHover");
	//		SwitchON = false;
	//		});
	//	HooUBT->SetHover([=] {
	//		{
	//			if (false == SwitchON)
	//			{
	//				HooUBT->ChangeAnimation("Hover");
	//				SwitchON = true;

	//			}
	//			else if (IsDown(VK_LBUTTON) && true == SwitchON)
	//			{
	//				HooUBT->ChangeAnimation("Down");

	//			}
	//		}
	//		});
	//}
	//{
	//	RayBT->SetUnHover([=] {
	//		RayBT->ChangeAnimation("UnHover");
	//		SwitchON = false;
	//		});
	//	RayBT->SetHover([=] {
	//		{
	//			if (false == SwitchON)
	//			{
	//				RayBT->ChangeAnimation("Hover");
	//				SwitchON = true;

	//			}
	//			else if (IsDown(VK_LBUTTON) && true == SwitchON)
	//			{
	//				RayBT->ChangeAnimation("Down");

	//			}
	//		}
	//		});
	//}

	for (int i = 1; i < 8; i++)
	{
		{
			RoomVector[i]->SetUnHover([=] {
				RoomVector[i]->SetSprite("Room_0.png");
				SwitchON = false;
				});
			RoomVector[i]->SetHover([=] {
				{
					if (false == SwitchON)
					{
						RoomVector[i]->SetSprite("Room_1.png");
						SwitchON = true;

					}
					else if (IsDown(VK_LBUTTON) && true == SwitchON)
					{
						RoomVector[i]->SetSprite("Room_2.png");
					}
					else if (IsUp(VK_LBUTTON))
					{
						RoomVector[i]->SetSprite("RoomX_0.png");
					}
				}
				});
		}
	}

	if (IsDown('P'))
	{
		LobbyPlayer[PlayerCount] = CreateWidget<UImage>(GetWorld(), "LobbyPlayer");;
		LobbyPlayer[PlayerCount]->AddToViewPort(15);
		LobbyPlayer[PlayerCount]->SetSprite("bazzi_idle.png", 1);
		LobbyPlayer[PlayerCount]->SetScale({ 150, 150 });
		LobbyPlayer[PlayerCount]->AddPosition(FVector(static_cast<float>(-325 + PlayerCount * 105), 125.0f, 100.0f ));

		if (8 > PlayerCount)
		{
			++PlayerCount;
		}
	}

}

void APlayLobby::SwapSelectCharacter(UImage* _SelectCharacter)
{
	SelectCharacter->ChangeAnimation("UnHover");
	_SelectCharacter->ChangeAnimation("Up");
	SelectCharacter = _SelectCharacter;
}

void APlayLobby::SetIsActive(bool _Active)
{
	PlayLobbyUI->SetActive(_Active);
}