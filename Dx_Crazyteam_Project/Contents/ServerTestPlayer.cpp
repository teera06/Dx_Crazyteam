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

	//OffIsSendPacket();
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

	//	std::shared_ptr<AMapObject> WaterBomb = GetGameMode()->GetCurMap()->SpawnWaterBomb(BombPoint.y, BombPoint.x);
	//	WaterBomb->SetObjectToken((UGame_Core::Net->GetSessionToken() + 1) * 1000 + WaterBomb_Token++);
	//	USendPacketManager::SendMapObjectSpawnPacket(WaterBomb, { BombPoint.y, BombPoint.x }, EMapObject::WaterBomb);
	//}

	Super::Tick(_DeltaTime);

	//if (false == IsNetInit())
	//{
	//	// 네트워크 통신준비가 아직 안된 오브젝트다.
	//	if (nullptr != UGame_Core::Net)
	//	{
	//		InitNet(UGame_Core::Net);
	//	}
	//}

	//CurTime -= _DeltaTime;

	//if (0.0f >= CurTime && true == IsNetInit())
	//{
	//	std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

	//	Packet->Pos = GetActorLocation();
	//	Packet->AnimationInfo = Renderer->GetCurInfo().SpriteNum;
	//	Packet->SpriteName = Renderer->GetCurInfo().Texture->GetName();
	//	Packet->ObjectType = static_cast<int>(EObjectType::Player);
	//	Send(Packet);
	//	CurTime += FrameTime;
	//}
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

			// 빌리지
			std::shared_ptr<AMapObject> vilBlock1 = GetGameMode()->GetCurMap()->AddMapObject(0, 1, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(vilBlock1, { 0,1 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> vilBlock2 = GetGameMode()->GetCurMap()->AddMapObject(0, 2, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(vilBlock2, { 0,2 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> vilBlock3 = GetGameMode()->GetCurMap()->AddMapObject(0, 3, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(vilBlock3, { 0,3 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> vilBlock4 = GetGameMode()->GetCurMap()->AddMapObject(0, 4, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(vilBlock4, { 0,4 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> TownBush1 = GetGameMode()->GetCurMap()->AddMapObject(0, 5, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush1, { 0,5 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageMoveBlock1 = GetGameMode()->GetCurMap()->AddMapObject(0, 8, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock1, { 0,8 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> TownBush2 = GetGameMode()->GetCurMap()->AddMapObject(0, 9, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush2, { 0,9 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageYellowHouse1 = GetGameMode()->GetCurMap()->AddMapObject(0, 10, EMapObject::VillageYellowHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse1, { 0,10 }, EMapObject::VillageYellowHouse);

			std::shared_ptr<AMapObject> VillageBlock5 = GetGameMode()->GetCurMap()->AddMapObject(0, 11, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock5, { 0,11 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageYellowHouse2 = GetGameMode()->GetCurMap()->AddMapObject(0, 12, EMapObject::VillageYellowHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse2, { 0,12 }, EMapObject::VillageYellowHouse);

			std::shared_ptr<AMapObject> VillageYellowHouse3 = GetGameMode()->GetCurMap()->AddMapObject(0, 14, EMapObject::VillageYellowHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse3, { 0,14 }, EMapObject::VillageYellowHouse);

			std::shared_ptr<AMapObject> VillageRedHouse1 = GetGameMode()->GetCurMap()->AddMapObject(1, 1, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse1, { 1,1 }, EMapObject::VillageRedHouse);


			//AddMapObject(1, 1, EMapObject::VillageRedHouse);
			/*AddMapObject(1, 2, EMapObject::VillageMoveBlock);
			AddMapObject(1, 3, EMapObject::VillageRedHouse);
			AddMapObject(1, 4, EMapObject::VillageMoveBlock);
			AddMapObject(1, 5, EMapObject::VillageTree);
			AddMapObject(1, 6, EMapObject::VillageMoveBlock);
			AddMapObject(1, 9, EMapObject::VillageTree);
			AddMapObject(1, 10, EMapObject::VillageBlock1);
			AddMapObject(1, 11, EMapObject::VillageBlock2);

			AddMapObject(2, 2, EMapObject::VillageBlock2);
			AddMapObject(2, 3, EMapObject::VillageBlock1);
			AddMapObject(2, 4, EMapObject::VillageBlock2);
			AddMapObject(2, 5, EMapObject::TownBush);
			AddMapObject(2, 7, EMapObject::VillageMoveBlock);
			AddMapObject(2, 8, EMapObject::VillageMoveBlock);
			AddMapObject(2, 9, EMapObject::TownBush);
			AddMapObject(2, 10, EMapObject::VillageYellowHouse);
			AddMapObject(2, 11, EMapObject::VillageMoveBlock);
			AddMapObject(2, 12, EMapObject::VillageYellowHouse);
			AddMapObject(2, 13, EMapObject::VillageMoveBlock);
			AddMapObject(2, 14, EMapObject::VillageYellowHouse);

			AddMapObject(3, 0, EMapObject::VillageMoveBlock);
			AddMapObject(3, 1, EMapObject::VillageRedHouse);
			AddMapObject(3, 2, EMapObject::VillageMoveBlock);
			AddMapObject(3, 3, EMapObject::VillageRedHouse);
			AddMapObject(3, 4, EMapObject::VillageMoveBlock);
			AddMapObject(3, 5, EMapObject::VillageTree);
			AddMapObject(3, 6, EMapObject::VillageMoveBlock);
			AddMapObject(3, 9, EMapObject::VillageTree);
			AddMapObject(3, 10, EMapObject::VillageBlock2);
			AddMapObject(3, 11, EMapObject::VillageBlock1);
			AddMapObject(3, 12, EMapObject::VillageBlock2);
			AddMapObject(3, 13, EMapObject::VillageBlock1);
			AddMapObject(3, 14, EMapObject::VillageBlock2);

			AddMapObject(4, 0, EMapObject::VillageBlock1);
			AddMapObject(4, 1, EMapObject::VillageBlock2);
			AddMapObject(4, 2, EMapObject::VillageBlock1);
			AddMapObject(4, 3, EMapObject::VillageBlock2);
			AddMapObject(4, 4, EMapObject::VillageBlock1);
			AddMapObject(4, 5, EMapObject::TownBush);
			AddMapObject(4, 8, EMapObject::VillageMoveBlock);
			AddMapObject(4, 9, EMapObject::TownBush);
			AddMapObject(4, 10, EMapObject::VillageYellowHouse);
			AddMapObject(4, 11, EMapObject::VillageMoveBlock);
			AddMapObject(4, 12, EMapObject::VillageYellowHouse);
			AddMapObject(4, 13, EMapObject::VillageMoveBlock);
			AddMapObject(4, 14, EMapObject::VillageYellowHouse);

			AddMapObject(5, 0, EMapObject::VillageBlock2);
			AddMapObject(5, 1, EMapObject::VillageRedHouse);
			AddMapObject(5, 2, EMapObject::VillageBlock2);
			AddMapObject(5, 3, EMapObject::VillageRedHouse);
			AddMapObject(5, 4, EMapObject::VillageBlock2);
			AddMapObject(5, 5, EMapObject::VillageTree);
			AddMapObject(5, 6, EMapObject::VillageMoveBlock);
			AddMapObject(5, 7, EMapObject::VillageMoveBlock);
			AddMapObject(5, 10, EMapObject::VillageBlock1);
			AddMapObject(5, 11, EMapObject::VillageBlock2);
			AddMapObject(5, 12, EMapObject::VillageBlock1);
			AddMapObject(5, 13, EMapObject::VillageBlock2);
			AddMapObject(5, 14, EMapObject::VillageBlock1);

			AddMapObject(6, 0, EMapObject::VillageTree);
			AddMapObject(6, 1, EMapObject::TownBush);
			AddMapObject(6, 2, EMapObject::VillageTree);
			AddMapObject(6, 3, EMapObject::TownBush);
			AddMapObject(6, 4, EMapObject::VillageTree);
			AddMapObject(6, 5, EMapObject::TownBush);
			AddMapObject(6, 8, EMapObject::VillageMoveBlock);
			AddMapObject(6, 9, EMapObject::TownBush);
			AddMapObject(6, 10, EMapObject::VillageTree);
			AddMapObject(6, 11, EMapObject::TownBush);
			AddMapObject(6, 12, EMapObject::VillageTree);
			AddMapObject(6, 13, EMapObject::TownBush);
			AddMapObject(6, 14, EMapObject::VillageTree);

			AddMapObject(7, 0, EMapObject::VillageBlock1);
			AddMapObject(7, 1, EMapObject::VillageBlock2);
			AddMapObject(7, 2, EMapObject::VillageBlock1);
			AddMapObject(7, 3, EMapObject::VillageBlock2);
			AddMapObject(7, 4, EMapObject::VillageBlock1);
			AddMapObject(7, 6, EMapObject::VillageMoveBlock);
			AddMapObject(7, 9, EMapObject::VillageTree);
			AddMapObject(7, 10, EMapObject::VillageBlock1);
			AddMapObject(7, 11, EMapObject::VillageRedHouse);
			AddMapObject(7, 12, EMapObject::VillageBlock1);
			AddMapObject(7, 13, EMapObject::VillageRedHouse);
			AddMapObject(7, 14, EMapObject::VillageBlock1);

			AddMapObject(8, 0, EMapObject::VillageBlueHouse);
			AddMapObject(8, 1, EMapObject::VillageMoveBlock);
			AddMapObject(8, 2, EMapObject::VillageBlueHouse);
			AddMapObject(8, 3, EMapObject::VillageMoveBlock);
			AddMapObject(8, 4, EMapObject::VillageBlueHouse);
			AddMapObject(8, 5, EMapObject::TownBush);
			AddMapObject(8, 7, EMapObject::VillageMoveBlock);
			AddMapObject(8, 8, EMapObject::VillageMoveBlock);
			AddMapObject(8, 9, EMapObject::TownBush);
			AddMapObject(8, 10, EMapObject::VillageBlock2);
			AddMapObject(8, 11, EMapObject::VillageBlock1);
			AddMapObject(8, 12, EMapObject::VillageBlock2);
			AddMapObject(8, 13, EMapObject::VillageBlock1);
			AddMapObject(8, 14, EMapObject::VillageBlock2);

			AddMapObject(9, 0, EMapObject::VillageBlock2);
			AddMapObject(9, 1, EMapObject::VillageBlock1);
			AddMapObject(9, 2, EMapObject::VillageBlock2);
			AddMapObject(9, 3, EMapObject::VillageBlock1);
			AddMapObject(9, 4, EMapObject::VillageBlock2);
			AddMapObject(9, 5, EMapObject::VillageTree);
			AddMapObject(9, 6, EMapObject::VillageMoveBlock);
			AddMapObject(9, 9, EMapObject::VillageTree);
			AddMapObject(9, 10, EMapObject::VillageMoveBlock);
			AddMapObject(9, 11, EMapObject::VillageRedHouse);
			AddMapObject(9, 12, EMapObject::VillageMoveBlock);
			AddMapObject(9, 13, EMapObject::VillageRedHouse);
			AddMapObject(9, 14, EMapObject::VillageMoveBlock);

			AddMapObject(10, 0, EMapObject::VillageBlueHouse);
			AddMapObject(10, 2, EMapObject::VillageBlueHouse);
			AddMapObject(10, 3, EMapObject::VillageMoveBlock);
			AddMapObject(10, 4, EMapObject::VillageBlueHouse);
			AddMapObject(10, 5, EMapObject::TownBush);
			AddMapObject(10, 8, EMapObject::VillageMoveBlock);
			AddMapObject(10, 9, EMapObject::TownBush);
			AddMapObject(10, 10, EMapObject::VillageBlock1);
			AddMapObject(10, 11, EMapObject::VillageBlock2);
			AddMapObject(10, 12, EMapObject::VillageBlock1);
			AddMapObject(10, 13, EMapObject::VillageBlock2);

			AddMapObject(11, 2, EMapObject::VillageBlock1);
			AddMapObject(11, 3, EMapObject::VillageBlock2);
			AddMapObject(11, 4, EMapObject::VillageBlock1);
			AddMapObject(11, 5, EMapObject::VillageTree);
			AddMapObject(11, 6, EMapObject::VillageMoveBlock);
			AddMapObject(11, 7, EMapObject::VillageMoveBlock);
			AddMapObject(11, 9, EMapObject::VillageTree);
			AddMapObject(11, 10, EMapObject::VillageMoveBlock);
			AddMapObject(11, 11, EMapObject::VillageRedHouse);
			AddMapObject(11, 12, EMapObject::VillageMoveBlock);
			AddMapObject(11, 13, EMapObject::VillageRedHouse);

			AddMapObject(12, 0, EMapObject::VillageBlueHouse);
			AddMapObject(12, 2, EMapObject::VillageBlueHouse);
			AddMapObject(12, 3, EMapObject::VillageBlock1);
			AddMapObject(12, 4, EMapObject::VillageBlueHouse);
			AddMapObject(12, 5, EMapObject::TownBush);
			AddMapObject(12, 8, EMapObject::VillageMoveBlock);
			AddMapObject(12, 9, EMapObject::TownBush);
			AddMapObject(12, 10, EMapObject::VillageBlock2);
			AddMapObject(12, 11, EMapObject::VillageBlock1);
			AddMapObject(12, 12, EMapObject::VillageBlock2);*/
		
		
		
		
		
		}

	}
}