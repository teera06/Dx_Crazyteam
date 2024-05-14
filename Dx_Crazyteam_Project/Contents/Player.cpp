#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Game_Core.h"
#include "Packets.h"

APlayer::APlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("RendererRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetOrder(5);
	Renderer->SetAutoSize(0.05f, true);
	Info = std::make_shared<PlayerInfo>();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(20, 20, 1));
	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
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