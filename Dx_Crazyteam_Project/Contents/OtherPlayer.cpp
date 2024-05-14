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
	Renderer->CreateAnimation("Idle_Left", "bazzi_left.png", 0.1f, false, 0, 0);
	Renderer->CreateAnimation("Idle_Right", "bazzi_right.png", 0.1f, false, 0, 0);
	Renderer->CreateAnimation("Idle_Up", "bazzi_up.png", 0.1f, false, 0, 0);
	Renderer->CreateAnimation("Idle_Down", "bazzi_down.png", 0.1f, false, 0, 0);

	Renderer->CreateAnimation("Move_Left", "bazzi_left.png", 0.1f, true, 0, 5);
	Renderer->CreateAnimation("Move_Right", "bazzi_right.png", 0.1f, true, 0, 5);
	Renderer->CreateAnimation("Move_Up", "bazzi_up.png", 0.1f, true, 0, 7);
	Renderer->CreateAnimation("Move_Down", "bazzi_down.png", 0.1f, true, 0, 7);


	// CreateState
	State.CreateState("Idle");
	State.CreateState("Move");
	//State.CreateState("Attack");
	//State.CreateState("Die");

	// StartFunction
	State.SetStartFunction("Idle", std::bind(&AOtherPlayer::IdleStart, this));
	State.SetStartFunction("Move", std::bind(&AOtherPlayer::MoveStart, this));

	// UpdateFunction
	State.SetUpdateFunction("Idle", std::bind(&AOtherPlayer::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction("Move", std::bind(&AOtherPlayer::Move, this, std::placeholders::_1));



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

			SetActorLocation(ActorUpdatePacket->Pos);

			std::string SpriteNames = ActorUpdatePacket->SpriteName;

			if (SpriteNames != "")
			{
				Renderer->ChangeAnimation(SpriteNames);
				//State.ChangeState(SpriteNames);
			}

			int a = 0;
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
