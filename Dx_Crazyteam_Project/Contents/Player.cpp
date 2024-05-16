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

	Info = std::make_shared<PlayerInfo>();
	SetCharacterType(ECharacterType::Bazzi);

	Renderer->SetOrder(ERenderOrder::Player);
	Renderer->SetAutoSize(0.05f, true);
	SetActorScale3D(FVector(20, 20, 1));

	Shadow = GetWorld()->SpawnActor<APlayer_Shadow>("Player_Shadow");

	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	Info->CurIndex = GetGameMode()->GetCurMap()->PosToPoint(GetActorLocation());
	Shadow->SetActorLocation(GetActorLocation() + FVector(0, 2, 0));



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

	PlayerSendPacket(_DeltaTime);

	//if (false == IsNetInit())
	//{
	//	// 네트워크 통신준비가 아직 안된 오브젝트다.
	//	if (nullptr != UGame_Core::Net)
	//	{
	//		InitNet(UGame_Core::Net);
	//	}
	//}

	//CurTime -= _DeltaTime;

	//if (0.0f >= CurTime && true == IsNetInit())
	//{
	//	std::shared_ptr<UWaterBombUpdatePacket> Packet = std::make_shared<UWaterBombUpdatePacket>();

	//	Packet->Pos = GetActorLocation();
	//	Packet->AnimationInfo = Renderer->GetCurAnimationFrame();
	//	Packet->SpriteName = Renderer->GetCurInfo().Texture->GetName();
	//	Send(Packet);
	//	CurTime += FrameTime;
	//}


	if (true == IsDown(VK_SPACE))
	{
		std::shared_ptr<AWaterBomb> Bomb = dynamic_pointer_cast<AWaterBomb>(GetGameMode()->GetCurMap()->SpawnWaterBomb(GetActorLocation()));
		Bomb->SetObjectToken(WaterBomb_Token++);

		std::shared_ptr<UWaterBombUpdatePacket> Packet = std::make_shared<UWaterBombUpdatePacket>();
		Packet->Pos = GetActorLocation();
		Packet->AnimationInfo = Renderer->GetCurAnimationFrame();
		Packet->SpriteName = Renderer->GetCurInfo().Texture->GetName();
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
	default:
		break;
	}

	if (_StateName == "Trap" || _StateName == "Rescue" || _StateName == "Die")
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
	default:
		break;
	}
}

