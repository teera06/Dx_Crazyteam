#include "PreCompile.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "NetInterface.h"
#include "Game_Core.h"
#include "Packets.h"

UNetInterface::UNetInterface()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("RendererRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
}

UNetInterface::~UNetInterface()
{
}

void UNetInterface::BeginPlay()
{
	Super::BeginPlay();
}

void UNetInterface::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void UNetInterface::BaseNetInit(float _DeltaTime)
{
	if (false == IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UGame_Core::Net)
		{
			InitNet(UGame_Core::Net);
		}
	}

	CurTime -= _DeltaTime;
}

void UNetInterface::PlayerSendPacket(float _DeltaTime)
{
	BaseNetInit(_DeltaTime);

	if (0.0f >= CurTime && true == IsNetInit())
	{
		std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

		Packet->Pos = GetActorLocation();
		Packet->AnimationInfo = Renderer->GetCurInfo().SpriteNum;
		Packet->SpriteName = Renderer->GetCurInfo().Texture->GetName();
		Packet->ObjectType = static_cast<int>(EObjectType::Player);
		Packet->SpriteAlpha = Renderer->GetAlpha();
		Send(Packet);
		CurTime += FrameTime;
	}
}

void UNetInterface::PlayerShadowPacket(float _DeltaTime)
{
	BaseNetInit(_DeltaTime);

	if (0.0f >= CurTime && true == IsNetInit())
	{
		std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

		Packet->Pos = GetActorLocation();
		Packet->SpriteName = Renderer->GetCurInfo().Texture->GetName();
		Send(Packet);
		CurTime += FrameTime;
	}
}

