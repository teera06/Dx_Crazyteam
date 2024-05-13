#include "PreCompile.h"
#include "Player.h"

APlayer::APlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("RendererRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetOrder(5);

	Renderer->SetScale(FVector(5, 5));

	std::shared_ptr<PlayerInfo> Info = std::make_shared<PlayerInfo>();
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