#include "PreCompile.h"
#include "OtherBomb.h"
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Game_Core.h"
#include "Packets.h"


AOtherBomb::AOtherBomb()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("RendererRoot");
	SetRoot(Root);
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetAutoSize(0.05f, true);
	Renderer->SetupAttachment(Root);
	Renderer->SetOrder(5);
	SetActorScale3D(FVector(20, 20, 1));
}

AOtherBomb::~AOtherBomb()
{
}

void AOtherBomb::BeginPlay()
{
	AActor::BeginPlay();
}

void AOtherBomb::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

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
		case WaterBombUpdatePacket:
		{
			std::shared_ptr<UWaterBombUpdatePacket> UpdatePacket = std::dynamic_pointer_cast<UWaterBombUpdatePacket>(Protocol);

			SetActorLocation(UpdatePacket->Pos);

			std::string SpriteNames = UpdatePacket->SpriteName;

			int AnimationInFO = UpdatePacket->AnimationInfo;

			bool IsDie = UpdatePacket->IsDestroy;

			if (SpriteNames != "" && IsDie ==false)
			{
				Renderer->SetSprite(SpriteNames, AnimationInFO);
			}
			if (IsDie == true)
			{
				Renderer->SetActive(false);
			}
			break;
		}
		default:
			break;
		}
	} while (nullptr != Protocol);
}

