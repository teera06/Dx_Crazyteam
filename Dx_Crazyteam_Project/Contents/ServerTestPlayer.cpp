#include "PreCompile.h"
#include <EngineBase/EngineProtocol.h>

#include "ServerTestPlayer.h"
#include "ItemBubble.h"
#include "Game_Core.h"
#include "MapObject.h"
#include "Packets.h"
#include "CAGameMode.h"
#include "BaseMap.h"
#include "SendPacketManager.h"



AServerTestPlayer::AServerTestPlayer()
	:APlayer()
{
}

AServerTestPlayer::~AServerTestPlayer()
{
}

void AServerTestPlayer::BeginPlay()
{
	Super::BeginPlay();

	OffIsSendPacket();
}

void AServerTestPlayer::Tick(float _DeltaTime)
{
	if (true == IsDown('P'))
	{
		SpawnItem();
	}

	Super::Tick(_DeltaTime);

	if (false == IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UGame_Core::Net)
		{
			InitNet(UGame_Core::Net);
		}
	}

	CurTime -= _DeltaTime;

	if (0.0f >= CurTime && true == IsNetInit())
	{
		std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

		Packet->Pos = GetActorLocation();
		Packet->AnimationInfo = Renderer->GetCurAnimationFrame();
		Packet->SpriteName = Renderer->GetCurInfo().Texture->GetName();
		Packet->ObjectType = static_cast<int>(EObjectType::Player);
		Send(Packet);
		CurTime += FrameTime;
	}
}

void AServerTestPlayer::SpawnItem()
{
	std::shared_ptr<UEngineServer> Server = dynamic_pointer_cast<UEngineServer>(UGame_Core::Net);

	if (nullptr != Server)
	{
		std::shared_ptr<AMapObject> NiddleItem = GetGameMode()->GetCurMap()->AddMapObject(8, 1, EMapObject::Item, EItemType::ItemNiddle);
		USendPacketManager::SendItemSpawnPacket(NiddleItem);

		std::shared_ptr<AMapObject> ShoesItem = GetGameMode()->GetCurMap()->AddMapObject(7, 1, EMapObject::Item, EItemType::ItemShoes);
		USendPacketManager::SendItemSpawnPacket(ShoesItem);

		std::shared_ptr<AMapObject> BubbleItem = GetGameMode()->GetCurMap()->AddMapObject(6, 1, EMapObject::Item, EItemType::ItemBubble);
		USendPacketManager::SendItemSpawnPacket(BubbleItem);

		std::shared_ptr<AMapObject> FluidItem = GetGameMode()->GetCurMap()->AddMapObject(5, 1, EMapObject::Item, EItemType::ItemFluid);
		USendPacketManager::SendItemSpawnPacket(FluidItem);

		std::shared_ptr<AMapObject> RollerItem = GetGameMode()->GetCurMap()->AddMapObject(4, 1, EMapObject::Item, EItemType::ItemRoller);
		USendPacketManager::SendItemSpawnPacket(RollerItem);

		std::shared_ptr<AMapObject> OwlItem = GetGameMode()->GetCurMap()->AddMapObject(3, 1, EMapObject::Item, EItemType::ItemOwl);
		USendPacketManager::SendItemSpawnPacket(OwlItem);
	}
}