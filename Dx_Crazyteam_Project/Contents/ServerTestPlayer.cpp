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

	//// WaterBomb 생성 테스트
	//if (true == IsDown('O'))
	//{
	//	POINT BombPoint = GetGameMode()->GetCurMap()->PosToPoint(GetActorLocation());

	//	std::shared_ptr<AMapObject> WoterBomb = GetGameMode()->GetCurMap()->SpawnWaterBomb(BombPoint.y, BombPoint.x);
	//	USendPacketManager::SendMapObjectSpawnPacket(WoterBomb, { BombPoint.y, BombPoint.x }, EMapObject::WaterBomb);
	//}

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
		//{
		//	// Item
		//	std::shared_ptr<AMapObject> NiddleItem = GetGameMode()->GetCurMap()->AddMapObject(8, 1, EMapObject::Item, EItemType::ItemNiddle);
		//	USendPacketManager::SendMapObjectSpawnPacket(NiddleItem, { 8,1 }, EMapObject::Item, EItemType::ItemNiddle);

		//	std::shared_ptr<AMapObject> ShoesItem = GetGameMode()->GetCurMap()->AddMapObject(7, 1, EMapObject::Item, EItemType::ItemShoes);
		//	USendPacketManager::SendMapObjectSpawnPacket(ShoesItem, { 7,1 }, EMapObject::Item, EItemType::ItemShoes);

		//	std::shared_ptr<AMapObject> BubbleItem = GetGameMode()->GetCurMap()->AddMapObject(6, 1, EMapObject::Item, EItemType::ItemBubble);
		//	USendPacketManager::SendMapObjectSpawnPacket(BubbleItem, { 6,1 }, EMapObject::Item, EItemType::ItemBubble);

		//	std::shared_ptr<AMapObject> FluidItem = GetGameMode()->GetCurMap()->AddMapObject(5, 1, EMapObject::Item, EItemType::ItemFluid);
		//	USendPacketManager::SendMapObjectSpawnPacket(FluidItem, { 5,1 }, EMapObject::Item, EItemType::ItemFluid);

		//	std::shared_ptr<AMapObject> RollerItem = GetGameMode()->GetCurMap()->AddMapObject(4, 1, EMapObject::Item, EItemType::ItemRoller);
		//	USendPacketManager::SendMapObjectSpawnPacket(RollerItem, { 4,1 }, EMapObject::Item, EItemType::ItemRoller);

		//	std::shared_ptr<AMapObject> OwlItem = GetGameMode()->GetCurMap()->AddMapObject(3, 1, EMapObject::Item, EItemType::ItemOwl);
		//	USendPacketManager::SendMapObjectSpawnPacket(OwlItem, { 3,1 }, EMapObject::Item, EItemType::ItemOwl);
		//}
		
		
		{
			// Block
			std::shared_ptr<AMapObject> CampBlock1 = GetGameMode()->GetCurMap()->AddMapObject(3, 3, EMapObject::CampBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(CampBlock1, { 3,3 }, EMapObject::CampBlock1);

			std::shared_ptr<AMapObject> CampMoveBlock1 = GetGameMode()->GetCurMap()->AddMapObject(3, 6, EMapObject::CampMoveBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock1, { 3,6 }, EMapObject::CampMoveBlock1);

			std::shared_ptr<AMapObject> CampHPBlock1 = GetGameMode()->GetCurMap()->AddMapObject(3, 9, EMapObject::CampHPBlock);
			USendPacketManager::SendMapObjectSpawnPacket(CampHPBlock1, { 3,9 }, EMapObject::CampHPBlock);

			std::shared_ptr<AMapObject> TownBush = GetGameMode()->GetCurMap()->AddMapObject(9, 1, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush, { 9,1 }, EMapObject::TownBush);
		}

	}
}