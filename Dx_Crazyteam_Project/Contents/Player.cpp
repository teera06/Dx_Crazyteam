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

	if (false == IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UGame_Core::Net)
		{
			InitNet(UGame_Core::Net);
		}
	}

	static float FrameTime = 1.0f / 60.0f;
	static float CurTime = FrameTime;

	CurTime -= _DeltaTime;

	if (0.0f >= CurTime && true == IsNetInit())
	{
		std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

		Packet->Pos = GetActorLocation();
		Packet->AnimationInfo = Renderer->GetCurAnimationFrame();
		Packet->SpriteName = GetAnimationName(State.GetCurStateName());
		Send(Packet);
		CurTime += FrameTime;
	}
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