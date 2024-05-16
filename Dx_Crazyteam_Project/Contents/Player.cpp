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

int APlayer::WaterBomb_Token = 1000;


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
	Info = std::make_shared<PlayerInfo>();
	SetActorScale3D(FVector(20, 20, 1));

	Shadow = GetWorld()->SpawnActor<APlayer_Shadow>("Player_Shadow");

	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	PlayerSendPacket(_DeltaTime);

	Info->CurIndex = GetGameMode()->GetCurMap()->PosToPoint(GetActorLocation());
	Shadow->SetActorLocation(GetActorLocation() + FVector(0, 2, 0));

	if (true == IsDown(VK_SPACE))
	{
		if (Info->WBCount > 0)
		{
			if (nullptr == GetGameMode()->GetCurMap()->GetMapObject(Info->CurIndex.y, Info->CurIndex.x))
			{
				--Info->WBCount;
				std::shared_ptr<AWaterBomb> Bomb = dynamic_pointer_cast<AWaterBomb>(GetGameMode()->GetCurMap()->SpawnWaterBomb(GetActorLocation()));
				Bomb->SetObjectToken(WaterBomb_Token++);
			}
		}
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

	if (_StateName == "Trap" || _StateName == "Rescue")
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
		Info->WBPower = 1;
		Info->WBCount = 1;
		break;
	case ECharacterType::Dao:
		Info->MyType = ECharacterType::Dao;
		Info->WBPower = 1;
		Info->WBCount = 1;
		break;
	default:
		break;
	}
}