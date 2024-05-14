#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Game_Core.h"
#include "Packets.h"
#include "Player_Shadow.h"

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

	Shadow->SetActorLocation(GetActorLocation() + FVector(0, 2, 0));

}

std::string APlayer::GetAnimationName(std::string_view _StateName)
{
	std::string _AniName = _StateName.data() + std::string("_");

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

	if (Dir.iX() == FVector::Up.iX() && Dir.iY() == FVector::Up.iY())
	{
		return _AniName + "Up";
	}
	else if (Dir.iX() == FVector::Down.iX() && Dir.iY() == FVector::Down.iY())
	{
		return _AniName + "Down";
	}
	else if (Dir.iX() == FVector::Right.iX() && Dir.iY() == FVector::Right.iY())
	{
		return _AniName + "Right";
	}
	else if (Dir.iX() == FVector::Left.iX() && Dir.iY() == FVector::Left.iY())
	{
		return _AniName + "Left";
	}
	else 
	{
		return "AnimationNameError";
	}
}