#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Game_Core.h"
#include "Packets.h"
#include "Player_Shadow.h"
#include "Player_Name.h"
#include "BaseMap.h"
#include "CAGameMode.h"
#include <EngineBase/EngineRandom.h>
#include "OtherPlayer.h"
#include "stringHelper.h"
#include <EngineCore/TextWidget.h>
#include <EngineCore/Image.h>

int APlayer::WaterBomb_Token = 0;
int APlayer::WaterCourse_Token = 0;
bool APlayer::SetWater_Token = false;

APlayer::APlayer()
{
	SoloArrowRenderer = CreateDefaultSubObject<USpriteRenderer>("SoloArrowRenderer");
	SoloArrowRenderer->SetupAttachment(Root);
}

APlayer::~APlayer()
{
}



void APlayer::BeginPlay()
{

	Super::BeginPlay();


	Renderer->SetOrder(ERenderOrder::Player);
	Renderer->SetAutoSize(0.05f, true);
	SetActorScale3D(FVector(20, 20, 1));


	SoloArrowRenderer->SetSprite("MyPlayer_Arrow.png");
	SoloArrowRenderer->SetOrder(ERenderOrder::UI);
	SoloArrowRenderer->SetAutoSize(0.05f, true);
	SoloArrowRenderer->SetPosition(FVector(0, 4, 0));

	Shadow = GetWorld()->SpawnActor<APlayer_Shadow>("Player_Shadow");
	Shadow->SetActorLocation(GetActorLocation() + FVector(0, 2, 1));

	Info = std::make_shared<PlayerInfo>();

	//PlayerNameUI = CreateWidget<UTextWidget>(GetWorld(), "PlayerName");
	//PlayerNameUI->SetFont("맑은 고딕");
	//PlayerNameUI->SetText(stringHelper::GetPlayerName());
	//PlayerNameUI->SetPosition(GetActorLocation() - ConstValue::CameraPos + FVector(0, 70));
	//PlayerNameUI->SetScale(10.0f);
	//PlayerNameUI->SetColor(Color8Bit::Black);
	//PlayerNameUI->SetOrder(1);
	//PlayerNameUI->AddToViewPort(11);
	PlayerListUI = CreateWidget<UImage>(GetWorld(), "PlayerUIList");
	PlayerListUI->AddToViewPort(15);
	PlayerListUI->SetSprite("Play_Portrait_Bazzi_Normal_R.png");
	PlayerListUI->SetAutoSize(1.0f, true);
	PlayerListUI->SetPosition({ 0, 0 });

	PlayerListUI->CreateAnimation("Bazzi_R_Nor", "Play_Portrait_Bazzi_Normal_R.png", 0.2f, true, 0, 1);
	PlayerListUI->CreateAnimation("Bazzi_B_Nor", "Play_Portrait_Bazzi_Normal_B.png", 0.2f, true, 0, 1);
	PlayerListUI->CreateAnimation("Bazzi_R_Cry", "Play_Portrait_Bazzi_Lose_R.png", 0.1f, true, 0, 3);
	PlayerListUI->CreateAnimation("Bazzi_B_Cry", "Play_Portrait_Bazzi_Lose_B.png", 0.1f, true, 0, 3);

	PlayerListUI->CreateAnimation("Dao_R_Nor", "Play_Portrait_Dao_Normal_R.png", 0.2f, true, 0, 1);
	PlayerListUI->CreateAnimation("Dao_B_Nor", "Play_Portrait_Dao_Normal_B.png", 0.2f, true, 0, 1);
	PlayerListUI->CreateAnimation("Dao_R_Cry", "Play_Portrait_Dao_Lose_R.png", 0.1f, true, 0, 3);
	PlayerListUI->CreateAnimation("Dao_B_Cry", "Play_Portrait_Dao_Lose_B.png", 0.1f, true, 0, 3);

	PlayerListUI->CreateAnimation("Marid_R_Nor", "Play_Portrait_Marid_Normal_R.png", 0.2f, true, 0, 1);
	PlayerListUI->CreateAnimation("Marid_B_Nor", "Play_Portrait_Marid_Normal_B.png", 0.2f, true, 0, 1);
	PlayerListUI->CreateAnimation("Marid_R_Cry", "Play_Portrait_Marid_Lose_R.png", 0.1f, true, 0, 3);
	PlayerListUI->CreateAnimation("Marid_B_Cry", "Play_Portrait_Marid_Lose_B.png", 0.1f, true, 0, 3);

	PlayerListUI->ChangeAnimation("Bazzi_R_Nor");
	PlayerListUI->SetActive(true);

	MainPlayerSetting();
	StateInit();
}

void APlayer::MainPlayerInit()
{
	MainPlayerSetting();
	State.ChangeState("GameOn");
}

void APlayer::MainPlayerSetting()
{
	SetCharacterType(ConstValue::MainPlayerCharacterType);

	if (ConstValue::MainPlayerTeamType == ETeamType::None)
	{
		// UI에서 팀 타입 선택되지 않은 경우
		ConstValue::MainPlayerTeamType = ETeamType::ATeam;
		SetTeamType(ETeamType::ATeam);
	}
	else
	{
		// UI에서 팀 타입 선택된 경우
		SetTeamType(ConstValue::MainPlayerTeamType);
	}
}

std::string APlayer::GetUIAnimationName(std::string_view _name)
{
	std::string AniName = "";

	switch (ConstValue::MainPlayerCharacterType)
	{
	case ECharacterType::Bazzi:
		AniName = "Bazzi_";
		break;
	case ECharacterType::Dao:
		AniName = "Dao_";
		break;
	case ECharacterType::Marid:
		AniName = "Marid_";
		break;
	default:
		break;
	}

	switch (ConstValue::MainPlayerTeamType)
	{
	case ETeamType::None:
		break;
	case ETeamType::ATeam:
		AniName += "R_";
		break;
	case ETeamType::BTeam:
		AniName += "B_";
		break;
	default:
		break;
	}

	AniName += _name.data();

	return AniName;
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SettingZValue();

	if (false == UITempBool)
	{
		PlayerListUI->ChangeAnimation(GetUIAnimationName("Nor"));
		UITempBool = true;
	}

	if(SessionToken == -1000)
	{
		if (nullptr != UGame_Core::Net)
		{
			SessionToken = UGame_Core::Net->GetSessionToken();
		}
	}
	FVector Pos = FVector(280.0f, 180 - static_cast<float>((SessionToken * 43)), 100.0f);
	PlayerListUI->SetPosition(Pos);

	//static bool PlayerCanMove = false;
	//static float InitTime = 2.0f;
	//InitTime -= _DeltaTime;

	//if (false == PlayerCanMove && 0.0f >= InitTime)
	//{
	//	InitTime = 2.0f;
	//	PlayerCanMove = true;
	//}

	//if (false == PlayerCanMove)
	//{
	//	return;
	//}

	/*PlayerNameUI->SetText(stringHelper::GetPlayerName());
	PlayerNameUI->SetPosition(GetActorLocation() - ConstValue::CameraPos + FVector(0, 70));*/

	if (ConstValue::MainPlayerCharacterType != Info->MyType || ConstValue::MainPlayerTeamType != Info->Team)
	{
		// 변화가 있으면 다시 시작
		ConstValue::MainPlayerTeamType = Info->Team;
		MainPlayerInit();
	}

	State.Update(_DeltaTime);

	Info->CurIndex = GetGameMode()->GetCurMap()->PosToPoint(GetActorLocation());

	if (true == GetGameMode()->GetCurMap()->IsOnBush(GetActorLocation()))
	{
		Renderer->SetActive(false);
		Shadow->ShadowRenderOff();

		IsBushRenderOff = true;
	}
	else if (true == IsBushRenderOff)
	{
		Renderer->SetActive(true);
		Shadow->ShadowRenderOn();

		IsBushRenderOff = false;
	}

	GetGameMode()->GMToPlayerCallBack = [=](EGameResult _GameResult)
		{
			switch (_GameResult)
			{
			case EGameResult::None:
				return;
			case EGameResult::Win:
				State.ChangeState("Win");
				break;
			case EGameResult::Loss:
				State.ChangeState("Lose");
				break;
			case EGameResult::Draw:
				State.ChangeState("Lose");
				break;
			default:
				break;
			}
		};

	/* 테스트용 */
	if (true == IsDown(VK_F1))
	{
		State.ChangeState("Trap");
		return;
	}

	if (true == IsDown(VK_F3))
	{
		State.ChangeState("Win");
		return;
	}

	if (true == IsDown(VK_F4))
	{
		State.ChangeState("Lose");
		return;
	}

	if (true == IsDown('B'))
	{
		SetCharacterType(ECharacterType::Bazzi);
		State.ChangeState("Idle");
		return;
	}

	if (true == IsDown('D'))
	{
		SetCharacterType(ECharacterType::Dao);
		State.ChangeState("Idle");
		return;
	}

	if (true == IsDown('M'))
	{
		SetCharacterType(ECharacterType::Marid);
		State.ChangeState("Idle");
		return;
	}

	//if (true == IsDown(VK_TAB))
	//{
	//	switch (Info->Team)
	//	{
	//	case ETeamType::None:
	//	case ETeamType::ATeam:
	//		SetTeamType(ETeamType::BTeam);
	//		break;
	//	case ETeamType::BTeam:
	//		SetTeamType(ETeamType::ATeam);
	//		break;
	//	}
	//}

	if (true == GetIsSendPacket())
	{
		PlayerSendPacket(_DeltaTime);
	}

#ifdef _DEBUG
	DebugFunction(_DeltaTime);
#endif
}

std::string APlayer::GetAnimationName(std::string_view _StateName)
{
	std::string _AniName = _StateName.data();

	switch (Info->RideType)
	{
	case EPlayerRideType::None:
		break;
	case EPlayerRideType::Owl:
		_AniName = std::string("Owl_") + _AniName;
		break;
	case EPlayerRideType::Turtle:
		_AniName = std::string("Turtle_") + _AniName;
		break;
	default:
		break;
	}

	switch (Info->MyType)
	{
	case ECharacterType::Bazzi:
		_AniName = std::string("Bazzi_") + _AniName;
		break;
	case ECharacterType::Dao:
		_AniName = std::string("Dao_") + _AniName;
		break;
	case ECharacterType::Marid:
		_AniName = std::string("Marid_") + _AniName;
		break;
	default:
		break;
	}

	switch (Info->Team)
	{
	case ETeamType::ATeam:
		_AniName = std::string("Red_") + _AniName;
		break;
	case ETeamType::BTeam:
		_AniName = std::string("Blue_") + _AniName;
		break;
	default:
		break;
	}

	if (_StateName == "GameOn1" || _StateName == "GameOn2" || _StateName == "Trap" || _StateName == "Rescue" || _StateName == "Die" || _StateName == "Win")
	{
		return _AniName;
	}

	if (Dir.iX() == FVector::Up.iX() && Dir.iY() == FVector::Up.iY())
	{
		return _AniName + "_Up";
	}
	else if (Dir.iX() == FVector::Down.iX() && Dir.iY() == FVector::Down.iY())
	{
		return _AniName + "_Down";
	}
	else if (Dir.iX() == FVector::Right.iX() && Dir.iY() == FVector::Right.iY())
	{
		return _AniName + "_Right";
	}
	else if (Dir.iX() == FVector::Left.iX() && Dir.iY() == FVector::Left.iY())
	{
		return _AniName + "_Left";
	}
	else 
	{
		return "AnimationNameError";
	}
}

void APlayer::SetCharacterType(ECharacterType _Type)
{
	if (_Type == ECharacterType::None || _Type == ECharacterType::Random)
	{
		int RandomCharacter = UEngineRandom::MainRandom.RandomInt(static_cast<int>(ECharacterType::Bazzi), static_cast<int>(ECharacterType::Marid));
		_Type = static_cast<ECharacterType>(RandomCharacter);
	}

	ConstValue::MainPlayerCharacterType = _Type;

	switch (_Type)
	{
	case ECharacterType::Bazzi:
		Info->MyType = ECharacterType::Bazzi;
		Info->Speed = ConstValue::BazziDefaultSpeed;
		Info->WBCount = ConstValue::BazziDefaultWBCount;
		Info->WBPower = ConstValue::BazziDefaultWBPower;
		Info->MaxSpeed = ConstValue::BazziMaxSpeed;
		Info->MaxWBCount = ConstValue::BazziMaxWBCount;
		Info->MaxWBPower = ConstValue::BazziMaxWBPower;
		break;
	case ECharacterType::Dao:
		Info->MyType = ECharacterType::Dao;
		Info->Speed = ConstValue::DaoDefaultSpeed;
		Info->WBCount = ConstValue::DaoDefaultWBCount;
		Info->WBPower = ConstValue::DaoDefaultWBPower;
		Info->MaxSpeed = ConstValue::DaoMaxSpeed;
		Info->MaxWBCount = ConstValue::DaoMaxWBCount;
		Info->MaxWBPower = ConstValue::DaoMaxWBPower;
		break;
	case ECharacterType::Marid:
		Info->MyType = ECharacterType::Marid;
		Info->Speed = ConstValue::MaridDefaultSpeed;
		Info->WBCount = ConstValue::MaridDefaultWBCount;
		Info->WBPower = ConstValue::MaridDefaultWBPower;
		Info->MaxSpeed = ConstValue::MaridMaxSpeed;
		Info->MaxWBCount = ConstValue::MaridMaxWBCount;
		Info->MaxWBPower = ConstValue::MaridMaxWBPower;
		break;
	default:
		break;
	}
}

void APlayer::SetRideType(EPlayerRideType _Ride)
{
	Info->RideType = _Ride;

	switch (_Ride)
	{
	case EPlayerRideType::None:
	{
		if (BeforeSpeedData >= 1)
		{
			Info->Speed = BeforeSpeedData;
		}
		State.ChangeState("RideOff");
		return;
	}
	case EPlayerRideType::Owl:
		BeforeSpeedData = Info->Speed;
		Info->Speed = 5;
		// 애니메이션 변경도 해야함
		break;
	case EPlayerRideType::Turtle:
		BeforeSpeedData = Info->Speed;
		Info->Speed = 1;
		// 애니메이션 변경도 해야함
		break;
	default:
		break;
	}

	// 처음 몇초간 무적
	RideGodModeTime = 2.f;
	State.ChangeState("RideIdle");
}

void APlayer::SettingZValue()
{
	FVector Pos = GetActorLocation();
	POINT Idx = GetGameMode()->GetCurMap()->PosToPoint(Pos);
	Pos.Z = -static_cast<float>(Idx.y) - 0.1f;
	
	SetActorLocation(Pos);

	Pos.Z += 0.1f;
	Shadow->SetActorLocation(Pos);
}

AOtherPlayer* APlayer::IsOtherPlayer()
{
	for (int i = 0; i < GetGameMode()->GetOtherPlayers().size(); i++)
	{
		POINT MyPos = GetGameMode()->GetCurMap()->PosToPoint(GetActorLocation());

		if (GetObjectToken() == GetGameMode()->GetOtherPlayers()[i]->GetObjectToken()) continue;

		POINT OtherPlayerPos = GetGameMode()->GetCurMap()->PosToPoint(GetGameMode()->GetOtherPlayers()[i]->GetActorLocation());

		if (MyPos.y == OtherPlayerPos.y &&
			MyPos.x == OtherPlayerPos.x)
		{
			return GetGameMode()->GetOtherPlayers()[i];
		}
	}

	return nullptr;
}
