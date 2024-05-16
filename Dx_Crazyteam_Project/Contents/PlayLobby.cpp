#include "PreCompile.h"
#include "PlayLobby.h"

#include "EngineCore/Image.h"

APlayLobby::APlayLobby()
{

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
	GameStart->CreateAnimation("Hover", "StartBT", 0.1f, true, 6, 7);
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

	LobbyCharacterBanner = CreateWidget<UImage>(GetWorld(), "Randomex");
	LobbyCharacterBanner->AddToViewPort(11);
	LobbyCharacterBanner->SetSprite("CharatorSelect_Outline_Random.bmp");
	LobbyCharacterBanner->SetScale({ 281.f, 80.f });
	LobbyCharacterBanner->SetPosition({ 230.0f,237.0f });
	LobbyCharacterBanner->SetActive(true);

	//팀 선택
	
	TeamA = CreateWidget<UImage>(GetWorld(), "TeamA");
	TeamA->CreateAnimation("UnHover", "ATeam.png", 0.1f, false, 0, 0);
	TeamA->CreateAnimation("Hover", "ATeam.png", 0.1f, false, 0, 0);
	TeamA->CreateAnimation("Down", "ATeam_Down.png", 0.1f, false, 0, 0);
	TeamA->CreateAnimation("UP", "ATeam_Pick.png", 0.1f, false, 0, 0);
	TeamA->AddToViewPort(12);
	TeamA->SetSprite("ATeam.png");
	TeamA->SetScale({ 100.f, 50.f });
	TeamA->SetPosition({ 160.0f,0.0f });
	TeamA->SetActive(true);

	TeamB = CreateWidget<UImage>(GetWorld(), "TeamB");
	TeamB->CreateAnimation("UnHover", "BTeam.png", 0.1f, false, 0, 0);
	TeamB->CreateAnimation("Hover", "BTeam.png", 0.1f, false, 0, 0);
	TeamB->CreateAnimation("Down", "BTeam_Down.png", 0.1f, false, 0, 0);
	TeamB->CreateAnimation("UP", "BTeam_Pick.png", 0.1f, false, 0, 0);
	TeamB->AddToViewPort(12);
	TeamB->SetSprite("BTeam.png");
	TeamB->SetScale({ 100.f, 50.f });
	TeamB->SetPosition({ 300.0f,0.0f });
	TeamB->SetActive(true);


	// 선택한 캐릭터
	SelectCharacter = RandomBT;

	checkUI = CreateWidget<UImage>(GetWorld(), "checkUI");
	checkUI->AddToViewPort(13);
	checkUI->SetSprite("check.png");
	checkUI->SetAutoSize(1.0f, true);
	checkUI->SetPosition({ 222.0f,183.0f });
	checkUI->SetActive(false);
	
}

void APlayLobby::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	PlayLobbyUI->SetActive(true);


	//팀 선택
	{
		TeamA->SetUnHover([=] {
			if ("UP" != TeamA->GetUiAniName())
			{
				TeamA->ChangeAnimation("UnHover");
			}
			TeamSwitchON = false;
			});
		TeamA->SetHover([=] {
			{
				if (false == TeamSwitchON && "UP" != TeamA->GetUiAniName())
				{
					TeamA->ChangeAnimation("Hover");
					TeamSwitchON = true;
				}
				else if (IsDown(VK_LBUTTON) && true == TeamSwitchON)
				{
					TeamA->ChangeAnimation("Down");
				}
				else if (IsUp(VK_LBUTTON))
				{
					TeamA->ChangeAnimation("UP");
					IsTeamSelectSharacter = true;
					SwapSelectCharacter(TeamA);
				}
			}
			});

	}
	{
		TeamB->SetUnHover([=] {
			if ("UP" != TeamB->GetUiAniName())
			{
				TeamB->ChangeAnimation("UnHover");
			}
			TeamSwitchON = false;
			});
		TeamB->SetHover([=] {
			{
				if (false == TeamSwitchON && "UP" != TeamB->GetUiAniName())
				{
					TeamB->ChangeAnimation("Hover");
					TeamSwitchON = true;
				}
				else if (IsDown(VK_LBUTTON) && true == TeamSwitchON)
				{
					TeamB->ChangeAnimation("Down");
				}

				else if (IsUp(VK_LBUTTON))
				{
					TeamB->ChangeAnimation("UP");
					IsTeamSelectSharacter = true;
					SwapSelectCharacter(TeamB);
				}
			}
			});
	}



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
					SwitchON = true;
				}
				else if (IsDown(VK_LBUTTON) && true == SwitchON)
				{
					RandomBT->ChangeAnimation("Down");
				}
				else if (IsUp(VK_LBUTTON))
				{
					LobbyCharacterBanner->SetSprite("CharatorSelect_Outline_Random.bmp");
					SwapSelectCharacter(RandomBT);
					checkUI->SetPosition({ 152.0f,183.0f });
					checkUI->SetActive(true);
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
			}
				SwitchON = false;
			});
		DaoBT->SetHover([=] {
			{
				if (false == SwitchON && "UP" != DaoBT->GetUiAniName())
				{
					DaoBT->ChangeAnimation("Hover");
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
					LobbyCharacterBanner->SetSprite("CharatorSelect_Outline_Dao.bmp");
					checkUI->SetPosition({ 222.0f,183.0f });
					checkUI->SetActive(true);
					//DaoBT->ChangeAnimation("Up");
				}

			}
			});
	}
	{
		MaridBT->SetUnHover([=] {
			if ("UP" != MaridBT->GetUiAniName())
			{
				MaridBT->ChangeAnimation("UnHover");
			}
			SwitchON = false;
			});
		MaridBT->SetHover([=] {
			{
				if (false == SwitchON && "UP" != MaridBT->GetUiAniName())
				{
					MaridBT->ChangeAnimation("Hover");
					SwitchON = true;

				}
				else if (IsDown(VK_LBUTTON) && true == SwitchON)
				{
					MaridBT->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = true;
					SwapSelectCharacter(MaridBT);
					LobbyCharacterBanner->SetSprite("CharatorSelect_Outline_Marid.bmp");
					checkUI->SetPosition({ 222.0f,133.0f });
					checkUI->SetActive(true);
				}

			}
			});

	}
	{
		BazziBT->SetUnHover([=] {
			if ("UP" != BazziBT->GetUiAniName())
			{
				BazziBT->ChangeAnimation("UnHover");
			}
			SwitchON = false;
			});
		BazziBT->SetHover([=] {
			{
				if (false == SwitchON && "UP" != BazziBT->GetUiAniName())
				{
					BazziBT->ChangeAnimation("Hover");
					SwitchON = true;

				}
				else if (IsDown(VK_LBUTTON) && true == SwitchON)
				{
					BazziBT->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = true;
					SwapSelectCharacter(BazziBT);
					LobbyCharacterBanner->SetSprite("CharatorSelect_Outline_Bazzi.bmp");
					checkUI->SetPosition({ 292.0f,133.0f });
					checkUI->SetActive(true);
				}

			}
			});
	}


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

	if (IsDown('P') && 3 >= PlayerCount)
	{
		LobbyPlayer[PlayerCount] = CreateWidget<UImage>(GetWorld(), "LobbyPlayer");;
		LobbyPlayer[PlayerCount]->AddToViewPort(15);
		LobbyPlayer[PlayerCount]->SetSprite("bazzi_idle.png", 1);
		LobbyPlayer[PlayerCount]->SetScale({ 150, 150 });
		LobbyPlayer[PlayerCount]->AddPosition(FVector(static_cast<float>(-330 + PlayerCount * 105), 125.0f, 100.0f ));
		++PlayerCount;
	}
	else if (IsDown('P') && 3 < PlayerCount)
	{
		if (8 < PlayerCount)
		{
			return;
		}

		LobbyPlayer[PlayerCount] = CreateWidget<UImage>(GetWorld(), "LobbyPlayer");;
		LobbyPlayer[PlayerCount]->AddToViewPort(15);
		LobbyPlayer[PlayerCount]->SetSprite("bazzi_idle.png", 1);
		LobbyPlayer[PlayerCount]->SetScale({ 150, 150 });
		LobbyPlayer[PlayerCount]->AddPosition(FVector(static_cast<float>(-750 + PlayerCount * 105), -20.0f, 100.0f));
		++PlayerCount;
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