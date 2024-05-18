#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Game_Core.h"
#include "Packets.h"
#include "Player_Shadow.h"
#include "BaseMap.h"
#include "CAGameMode.h"
#include "WaterBomb.h"
#include <EngineBase/EngineRandom.h>

int APlayer::WaterBomb_Token = 0;


APlayer::APlayer()
{
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

	Shadow = GetWorld()->SpawnActor<APlayer_Shadow>("Player_Shadow");
	Shadow->SetActorLocation(GetActorLocation() + FVector(0, 2, 1));

	Info = std::make_shared<PlayerInfo>();

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

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (ConstValue::MainPlayerCharacterType != Info->MyType || ConstValue::MainPlayerTeamType != Info->Team)
	{
		// 변화가 있으면 다시 시작
		MainPlayerInit();
	}

	State.Update(_DeltaTime);

	Info->CurIndex = GetGameMode()->GetCurMap()->PosToPoint(GetActorLocation());
	
	//Shadow->SetActorLocation(GetActorLocation() + FVector(0, 2, 0));


	if (true == GetGameMode()->GetCurMap()->IsOnBush(GetActorLocation()))
	{
		Renderer->SetActive(false);
		Shadow->ShadowRenderOff();
	}
	else 
	{
		Renderer->SetActive(true);
		Shadow->ShadowRenderOn();
	}

	/* 테스트용 */
	if (true == IsDown(VK_F1))
	{
		State.ChangeState("Trap");
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

	if (true == GetIsSendPacket())
	{
		PlayerSendPacket(_DeltaTime);
	}


	if (true == IsDown(VK_SPACE))
	{
		std::shared_ptr<AWaterBomb> Bomb = dynamic_pointer_cast<AWaterBomb>(GetGameMode()->GetCurMap()->SpawnWaterBomb(GetActorLocation()));
		Bomb->SetObjectToken(WaterBomb_Token++);
		Bomb->SetToken(WaterBomb_Token++);
		std::shared_ptr<UWaterBombUpdatePacket> Packet = std::make_shared<UWaterBombUpdatePacket>();
		Packet->Pos = GetActorLocation();
		Packet->ObjectType = static_cast<int>(EObjectType::WaterBomb);
		Packet->Bomb = true;
		Send(Packet);
	}
}

std::string APlayer::GetAnimationName(std::string_view _StateName)
{
	std::string _AniName = _StateName.data();

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

	if (_StateName == "GameOn1" || _StateName == "GameOn2" || _StateName == "Trap" || _StateName == "Rescue" || _StateName == "Die")
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
		ConstValue::MainPlayerCharacterType = _Type;
	}

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

void APlayer::SettingZValue()
{
	FVector Pos = GetActorLocation();
	POINT Idx = GetGameMode()->GetCurMap()->PosToPoint(Pos);
	Pos.Z = -static_cast<float>(Idx.y) - 0.1f;
	
	SetActorLocation(Pos);

	Pos.Z += 0.1f;
	Shadow->SetActorLocation(Pos);
}