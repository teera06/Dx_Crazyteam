#include "PreCompile.h"
#include "PlayLobby.h"

#include "EngineCore/Image.h"
#include "EngineBase/EngineDebug.h"

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

	//플레이어 Room
	Room1 = CreateWidget<UImage>(GetWorld(), "Room1");
	Room1->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room1->AddToViewPort(12);
	Room1->SetSprite("Room_0.png");
	Room1->SetAutoSize(1.0f, true);
	Room1->SetPosition(FVector(-218.f, 157.f));
	Room1->SetActive(true);

	Room2 = CreateWidget<UImage>(GetWorld(), "Room2");
	Room2->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room2->AddToViewPort(12);
	Room2->SetSprite("Room_0.png");
	Room2->SetAutoSize(1.0f, true);
	Room2->SetPosition(FVector(-112.f, 157.f));
	Room2->SetActive(true);

	Room3 = CreateWidget<UImage>(GetWorld(), "Room3");
	Room3->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room3->AddToViewPort(12);
	Room3->SetSprite("Room_0.png");
	Room3->SetAutoSize(1.0f, true);
	Room3->SetPosition(FVector(-6.f, 157.f));
	Room3->SetActive(true);

	Room4 = CreateWidget<UImage>(GetWorld(), "Room4");
	Room4->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room4->AddToViewPort(12);
	Room4->SetSprite("Room_0.png");
	Room4->SetAutoSize(1.0f, true);
	Room4->SetPosition(FVector(-324.f, 11.f));
	Room4->SetActive(true);

	Room5 = CreateWidget<UImage>(GetWorld(), "Room5");
	Room5->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room5->AddToViewPort(12);
	Room5->SetSprite("Room_0.png");
	Room5->SetAutoSize(1.0f, true);
	Room5->SetPosition(FVector(-218.f, 11.f));
	Room5->SetActive(true);

	Room6 = CreateWidget<UImage>(GetWorld(), "Room6");
	Room6->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room6->AddToViewPort(12);
	Room6->SetSprite("Room_0.png");
	Room6->SetAutoSize(1.0f, true);
	Room6->SetPosition(FVector(-112.f, 11.f));
	Room6->SetActive(true);

	Room7 = CreateWidget<UImage>(GetWorld(), "Room7");
	Room7->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room7->AddToViewPort(12);
	Room7->SetSprite("Room_0.png");
	Room7->SetAutoSize(1.0f, true);
	Room7->SetPosition(FVector(-6.f, 11.f));
	Room7->SetActive(true);


	//시작 버튼
	GameStart = CreateWidget<UImage>(GetWorld(), "GameStart");
	GameStart->CreateAnimation("UnHover", "StartBt_1.png", 0.1f, false, 0, 0);
	GameStart->CreateAnimation("Hover", "StartBT", 0.1f, true, 6, 7);
	GameStart->CreateAnimation("Down", "StartBt_3.png", 0.1f, false, 0, 0);
	GameStart->AddToViewPort(10);
	GameStart->SetSprite("StartBt_1.png");
	GameStart->SetScale({ 190,52 });
	GameStart->SetPosition({ 209,-223 });
	GameStart->SetActive(true);
	GameStart->ChangeAnimation("UnHover");

	//맵선택 버튼

	SelectMap = CreateWidget<UImage>(GetWorld(), "SelectMap");
	SelectMap->CreateAnimation("UnHover", "SelectMap_0.png", 0.1f, false, 0, 0);
	SelectMap->CreateAnimation("Hover", "SelectMap", 0.1f, true, 1, 2);
	SelectMap->CreateAnimation("Down", "SelectMap_3.png", 0.1f, false, 0, 0);
	SelectMap->AddToViewPort(12);
	SelectMap->SetSprite("SelectMap_0.png");
	SelectMap->SetAutoSize(1.0f, true);
	SelectMap->SetPosition({ 306.0f,-152.0f });
	SelectMap->SetActive(true);
	SelectMap->ChangeAnimation("UnHover");

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
	checkUI->SetActive(true);

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
		SelectMap->SetUnHover([=] {
			SelectMap->ChangeAnimation("UnHover");
			SwitchON = false;
			});
		SelectMap->SetHover([=] {
			if (SelectMap->IsCurAnimationEnd() == true)
			{
				SelectMap->ChangeAnimation("Hover");
			}
			});
		SelectMap->SetDown([=] {
			SelectMap->ChangeAnimation("Down");
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


	// Room Hover
	{
		Room1->SetUnHover([=] {
			if (true == RoomO1 && false == RoomSwitch && "UP" != Room1->GetUiAniName())
			{
				Room1->ChangeAnimation("UnHover");
				RoomO1 = true;
			}
			else if (true == RoomX1 && "UP" == Room1->GetUiAniName())
			{
				Room1->ChangeAnimation("UP");
				RoomO1 = false;
				RoomX1 = true;
			}
			});

		Room1->SetHover([=] {
			{
				if (true == RoomO1 && false == RoomSwitch && "UP" != Room1->GetUiAniName())
				{
					Room1->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO1)
				{
					Room1->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO1)
				{
					IsSelectSharacter = false;
					Room1->ChangeAnimation("UP");
					RoomX1 = true;
					RoomSwitch = true;
					RoomO1 = false;
				}
				else if (false == RoomSwitch && true == RoomX1 && false == RoomO1 && "UP" == Room1->GetUiAniName())
				{
					Room1->ChangeAnimation("XHover");
					RoomX1 = true;
				}
				else if (true == RoomX1 && false == RoomO1 && IsDown(VK_LBUTTON))
				{
					Room1->ChangeAnimation("XDown");
					RoomX1 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX1 && false == RoomO1 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room1->ChangeAnimation("XUp");
					RoomX1 = false;
					RoomO1 = true;
				}
			}
			});

	}
	{
		Room2->SetUnHover([=] {
			if (true == RoomO2 && false == RoomSwitch && "UP" != Room1->GetUiAniName())
			{
				Room2->ChangeAnimation("UnHover");
				RoomO2 = true;
			}
			else if (true == RoomX2 && "UP" == Room2->GetUiAniName())
			{
				Room2->ChangeAnimation("UP");
				RoomO2 = false;
				RoomX2 = true;
			}
			});

		Room2->SetHover([=] {
			{
				if (true == RoomO2 && false == RoomSwitch && "UP" != Room2->GetUiAniName())
				{
					Room2->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO2)
				{
					Room2->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO2)
				{
					IsSelectSharacter = false;
					Room2->ChangeAnimation("UP");
					RoomX2 = true;
					RoomSwitch = true;
					RoomO2 = false;
				}
				else if (false == RoomSwitch && true == RoomX2 && false == RoomO2 && "UP" == Room2->GetUiAniName())
				{
					Room2->ChangeAnimation("XHover");
					RoomX2 = true;
				}
				else if (true == RoomX2 && false == RoomO2 && IsDown(VK_LBUTTON))
				{
					Room2->ChangeAnimation("XDown");
					RoomX2 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX2 && false == RoomO2 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room2->ChangeAnimation("XUp");
					RoomX2 = false;
					RoomO2 = true;
				}
			}
			});
	}

	{
		Room3->SetHover([=] {
			{
				if (true == RoomO3 && false == RoomSwitch && "UP" != Room3->GetUiAniName())
				{
					Room3->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO3)
				{
					Room3->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO3)
				{
					IsSelectSharacter = false;
					Room3->ChangeAnimation("UP");
					RoomX3 = true;
					RoomSwitch = true;
					RoomO3 = false;
				}
				else if (false == RoomSwitch && true == RoomX3 && false == RoomO3 && "UP" == Room3->GetUiAniName())
				{
					Room3->ChangeAnimation("XHover");
					RoomX3 = true;
				}
				else if (true == RoomX3 && false == RoomO3 && IsDown(VK_LBUTTON))
				{
					Room3->ChangeAnimation("XDown");
					RoomX3 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX3 && false == RoomO3 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room3->ChangeAnimation("XUp");
					RoomX3= false;
					RoomO3 = true;
				}
			}
			});
	}
	{
		Room4->SetHover([=] {
			{
				if (true == RoomO4 && false == RoomSwitch && "UP" != Room4->GetUiAniName())
				{
					Room4->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO4)
				{
					Room4->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO4)
				{
					IsSelectSharacter = false;
					Room4->ChangeAnimation("UP");
					RoomX4 = true;
					RoomSwitch = true;
					RoomO4 = false;
				}
				else if (false == RoomSwitch && true == RoomX4 && false == RoomO4 && "UP" == Room4->GetUiAniName())
				{
					Room4->ChangeAnimation("XHover");
					RoomX4 = true;
				}
				else if (true == RoomX4 && false == RoomO4 && IsDown(VK_LBUTTON))
				{
					Room4->ChangeAnimation("XDown");
					RoomX4 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX4 && false == RoomO4 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room4->ChangeAnimation("XUp");
					RoomX4 = false;
					RoomO4 = true;
				}
			}
			});
	}

	{
		Room5->SetHover([=] {
			{
				if (true == RoomO5 && false == RoomSwitch && "UP" != Room5->GetUiAniName())
				{
					Room5->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO5)
				{
					Room5->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO5)
				{
					IsSelectSharacter = false;
					Room5->ChangeAnimation("UP");
					RoomX5 = true;
					RoomSwitch = true;
					RoomO5 = false;
				}
				else if (false == RoomSwitch && true == RoomX5 && false == RoomO5 && "UP" == Room5->GetUiAniName())
				{
					Room5->ChangeAnimation("XHover");
					RoomX5 = true;
				}
				else if (true == RoomX5 && false == RoomO5 && IsDown(VK_LBUTTON))
				{
					Room5->ChangeAnimation("XDown");
					RoomX5 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX5 && false == RoomO5 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room5->ChangeAnimation("XUp");
					RoomX5 = false;
					RoomO5 = true;
				}
			}
			});
	}

	{
		Room6->SetHover([=] {
			{
				if (true == RoomO6 && false == RoomSwitch && "UP" != Room6->GetUiAniName())
				{
					Room6->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO6)
				{
					Room6->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO6)
				{
					IsSelectSharacter = false;
					Room6->ChangeAnimation("UP");
					RoomX6 = true;
					RoomSwitch = true;
					RoomO6 = false;
				}
				else if (false == RoomSwitch && true == RoomX6 && false == RoomO6 && "UP" == Room6->GetUiAniName())
				{
					Room6->ChangeAnimation("XHover");
					RoomX6 = true;
				}
				else if (true == RoomX6 && false == RoomO6 && IsDown(VK_LBUTTON))
				{
					Room6->ChangeAnimation("XDown");
					RoomX6 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX6 && false == RoomO6 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room6->ChangeAnimation("XUp");
					RoomX6 = false;
					RoomO6 = true;
				}
			}
			});
	}

	{
		Room7->SetHover([=] {
			{
				if (true == RoomO7 && false == RoomSwitch && "UP" != Room7->GetUiAniName())
				{
					Room7->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO7)
				{
					Room7->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO7)
				{
					IsSelectSharacter = false;
					Room7->ChangeAnimation("UP");
					RoomX7 = true;
					RoomSwitch = true;
					RoomO7 = false;
				}
				else if (false == RoomSwitch && true == RoomX7 && false == RoomO7 && "UP" == Room7->GetUiAniName())
				{
					Room7->ChangeAnimation("XHover");
					RoomX7 = true;
				}
				else if (true == RoomX7 && false == RoomO7 && IsDown(VK_LBUTTON))
				{
					Room7->ChangeAnimation("XDown");
					RoomX7 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX7 && false == RoomO7 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room7->ChangeAnimation("XUp");
					RoomX7 = false;
					RoomO7 = true;
				}
			}
			});
	}












	if (IsDown('P') && 3 >= PlayerCount)
	{
		LobbyPlayer[PlayerCount] = CreateWidget<UImage>(GetWorld(), "LobbyPlayer");;
		LobbyPlayer[PlayerCount]->AddToViewPort(15);
		LobbyPlayer[PlayerCount]->SetSprite("bazzi_idle.png", 1);
		LobbyPlayer[PlayerCount]->SetScale({ 150, 150 });
		LobbyPlayer[PlayerCount]->AddPosition(FVector(static_cast<float>(-330 + PlayerCount * 105), 125.0f, 100.0f));
		++PlayerCount;
	}
	else if (IsDown('P') && 3 < PlayerCount)
	{
		if (7 < PlayerCount)
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