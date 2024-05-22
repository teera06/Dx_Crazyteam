#include "PreCompile.h"
#include "OtherPlayer.h"
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Game_Core.h"
#include "Packets.h"

AOtherPlayer::AOtherPlayer() 
{

	Root = CreateDefaultSubObject<UDefaultSceneComponent>("RendererRoot");
	SetRoot(Root);
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetAutoSize(0.05f, true);
	Renderer->SetupAttachment(Root);
	Renderer->SetOrder(5);
	SetActorScale3D(FVector(20, 20, 1));
}

AOtherPlayer::~AOtherPlayer() 
{
}

void AOtherPlayer::BeginPlay()
{
	AActor::BeginPlay();
}

void AOtherPlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (nullptr == UGame_Core::Net)
	{
		MsgBoxAssert("네트워크 연결이 안된상태에서 아더플레어를 만들었습니다.");
	}

	std::shared_ptr<UEngineProtocol> Protocol = nullptr;

	do
	{
		Protocol = PopProtocol();
		if (nullptr == Protocol)
		{
			break;
		}

		EContentPacket PacketType = Protocol->GetPacketType<EContentPacket>();
		
		switch (PacketType)
		{
		case ActorUpdatePacket:
		{
			std::shared_ptr<UActorUpdatePacket> ActorUpdatePacket = std::dynamic_pointer_cast<UActorUpdatePacket>(Protocol);

			if (static_cast<int>(EObjectType::Player) != ActorUpdatePacket->ObjectType)
			{
				break;
			}

			SetActorLocation(ActorUpdatePacket->Pos);

			std::string SpriteNames = ActorUpdatePacket->SpriteName;

			int AnimationInFO = ActorUpdatePacket->AnimationInfo;

			if (SpriteNames != "")
			{
				Renderer->SetActive(ActorUpdatePacket->RendererIsActive);
				Renderer->SetSprite(SpriteNames, AnimationInFO);
				Renderer->SetAlpha(ActorUpdatePacket->SpriteAlpha);
				Renderer->SetPosition(ActorUpdatePacket->RendererPos);
			}

			IsOPDestroy = ActorUpdatePacket->IsDestroy;

			break;
		}
		default:
			break;
		}
	} while (nullptr != Protocol);

}

void AOtherPlayer::IdleStart()
{
}

void AOtherPlayer::Idle(float _DeltaTime)
{
}

void AOtherPlayer::MoveStart()
{
}

void AOtherPlayer::Move(float _DeltaTime)
{
}
