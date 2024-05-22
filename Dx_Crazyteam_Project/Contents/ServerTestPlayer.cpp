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

			std::shared_ptr<AMapObject> VillageMoveBlock = GetGameMode()->GetCurMap()->AddMapObject(0, 8, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock, { 0,8 }, EMapObject::VillageMoveBlock);

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

			std::shared_ptr<AMapObject> VillageRedHouse = GetGameMode()->GetCurMap()->AddMapObject(1, 1, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse, { 1,1 }, EMapObject::VillageRedHouse);

			std::shared_ptr<AMapObject> VillageRedHouse1 = GetGameMode()->GetCurMap()->AddMapObject(1, 1, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse1, { 1,1 }, EMapObject::VillageRedHouse);

			std::shared_ptr<AMapObject> VillageMoveBlock1 = GetGameMode()->GetCurMap()->AddMapObject(1, 2, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock1, { 1,2 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageRedHouse3 = GetGameMode()->GetCurMap()->AddMapObject(1, 3, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse3, { 1,3 }, EMapObject::VillageRedHouse);
			
			std::shared_ptr<AMapObject> VillageMoveBlock2 = GetGameMode()->GetCurMap()->AddMapObject(1, 4, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock2, { 1,4 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageTree1 = GetGameMode()->GetCurMap()->AddMapObject(1, 5, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree1, { 1,5 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> VillageMoveBlock3 = GetGameMode()->GetCurMap()->AddMapObject(1, 6, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock3, { 1,6 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageTree2 = GetGameMode()->GetCurMap()->AddMapObject(1, 9, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree2, { 1,9 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> VillageBlock6 = GetGameMode()->GetCurMap()->AddMapObject(1, 10, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock6, { 1,10 }, EMapObject::VillageBlock1);
			
			std::shared_ptr<AMapObject> VillageBlock7 = GetGameMode()->GetCurMap()->AddMapObject(1, 11, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock7, { 1,11 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock8 = GetGameMode()->GetCurMap()->AddMapObject(2, 2, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock8, { 2,2 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock9 = GetGameMode()->GetCurMap()->AddMapObject(2, 3, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock9, { 2,3 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock10 = GetGameMode()->GetCurMap()->AddMapObject(2, 4, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock10, { 2,4 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> TownBush3 = GetGameMode()->GetCurMap()->AddMapObject(2, 5, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush3, { 2,5 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageMoveBlock4 = GetGameMode()->GetCurMap()->AddMapObject(2, 7, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock4, { 2,7 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageMoveBlock5 = GetGameMode()->GetCurMap()->AddMapObject(2, 8, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock5, { 2,8 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> TownBush4 = GetGameMode()->GetCurMap()->AddMapObject(2, 9, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush4, { 2,9 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageYellowHouse4 = GetGameMode()->GetCurMap()->AddMapObject(2, 10, EMapObject::VillageYellowHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse4, { 2,10 }, EMapObject::VillageYellowHouse);


			std::shared_ptr<AMapObject> VillageMoveBlock6 = GetGameMode()->GetCurMap()->AddMapObject(2, 11, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock6, { 2,11 }, EMapObject::VillageMoveBlock);


			std::shared_ptr<AMapObject> VillageYellowHouse5= GetGameMode()->GetCurMap()->AddMapObject(2, 12, EMapObject::VillageYellowHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse5, { 2,12 }, EMapObject::VillageYellowHouse);

			std::shared_ptr<AMapObject> VillageMoveBlock7 = GetGameMode()->GetCurMap()->AddMapObject(2, 13, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock7, { 2,13 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageYellowHouse6 = GetGameMode()->GetCurMap()->AddMapObject(2, 14, EMapObject::VillageYellowHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse6, { 2,14 }, EMapObject::VillageYellowHouse);

			

			std::shared_ptr<AMapObject> VillageMoveBlock8 = GetGameMode()->GetCurMap()->AddMapObject(3, 0, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock8, { 3,0 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageRedHouse4 = GetGameMode()->GetCurMap()->AddMapObject(3, 1, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse4, { 3,1 }, EMapObject::VillageRedHouse);

			std::shared_ptr<AMapObject> VillageMoveBlock9 = GetGameMode()->GetCurMap()->AddMapObject(3, 2, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock9, { 3,2 }, EMapObject::VillageMoveBlock);


			std::shared_ptr<AMapObject> VillageRedHouse5 = GetGameMode()->GetCurMap()->AddMapObject(3, 3, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse5, { 3,3 }, EMapObject::VillageRedHouse);

			std::shared_ptr<AMapObject> VillageMoveBlock10 = GetGameMode()->GetCurMap()->AddMapObject(3, 4, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock10, { 3,4 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageTree3 = GetGameMode()->GetCurMap()->AddMapObject(3, 5, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree3, { 3,5 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> VillageMoveBlock11 = GetGameMode()->GetCurMap()->AddMapObject(3, 6, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock11, { 3,6 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageTree4 = GetGameMode()->GetCurMap()->AddMapObject(3, 9, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree4, { 3,9 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> VillageBlock11 = GetGameMode()->GetCurMap()->AddMapObject(3, 10, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock11, { 3,10 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock12 = GetGameMode()->GetCurMap()->AddMapObject(3, 11, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock12, { 3,11 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock13 = GetGameMode()->GetCurMap()->AddMapObject(3, 12, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock13, { 3,12 }, EMapObject::VillageBlock2);


			std::shared_ptr<AMapObject> VillageBlock14 = GetGameMode()->GetCurMap()->AddMapObject(3, 13, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock14, { 3,13 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject>  VillageBlock15 = GetGameMode()->GetCurMap()->AddMapObject(3, 14, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock15, { 3,14 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock16 = GetGameMode()->GetCurMap()->AddMapObject(4, 0, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock16, { 4,0 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock17 = GetGameMode()->GetCurMap()->AddMapObject(4, 1, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock17, { 4,1 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock18 = GetGameMode()->GetCurMap()->AddMapObject(4, 2, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock18, { 4,2 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock19 = GetGameMode()->GetCurMap()->AddMapObject(4, 3, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock19, { 4,3 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock20 = GetGameMode()->GetCurMap()->AddMapObject(4, 4, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock20, { 4,4 }, EMapObject::VillageBlock1);


			std::shared_ptr<AMapObject> TownBush5 = GetGameMode()->GetCurMap()->AddMapObject(4, 5, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush5, { 4,5 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageMoveBlock12 = GetGameMode()->GetCurMap()->AddMapObject(4, 8, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock12, { 4,8 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> TownBush6 = GetGameMode()->GetCurMap()->AddMapObject(4, 9, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush6, { 4,9 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageYellowHouse7= GetGameMode()->GetCurMap()->AddMapObject(4, 10, EMapObject::VillageYellowHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse7, { 4,10 }, EMapObject::VillageYellowHouse);

			std::shared_ptr<AMapObject> VillageMoveBlock13 = GetGameMode()->GetCurMap()->AddMapObject(4, 11, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock13, { 4,11 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageYellowHouse8 = GetGameMode()->GetCurMap()->AddMapObject(4, 12, EMapObject::VillageYellowHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse8, { 4,12 }, EMapObject::VillageYellowHouse);

			std::shared_ptr<AMapObject> VillageMoveBlock14 = GetGameMode()->GetCurMap()->AddMapObject(4, 13, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock14, { 4,13 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageYellowHouse9 = GetGameMode()->GetCurMap()->AddMapObject(4, 14, EMapObject::VillageYellowHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse9, { 4,14 }, EMapObject::VillageYellowHouse);

			std::shared_ptr<AMapObject> VillageBlock21 = GetGameMode()->GetCurMap()->AddMapObject(5, 0, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock21, { 5,0 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageRedHouse6 = GetGameMode()->GetCurMap()->AddMapObject(5, 1, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse6, { 5,1 }, EMapObject::VillageRedHouse);

			std::shared_ptr<AMapObject> VillageBlock22 = GetGameMode()->GetCurMap()->AddMapObject(5, 2, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock22, { 5,2 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageRedHouse7 = GetGameMode()->GetCurMap()->AddMapObject(5, 3, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse7, { 5,3 }, EMapObject::VillageRedHouse);

			std::shared_ptr<AMapObject> VillageBlock23 = GetGameMode()->GetCurMap()->AddMapObject(5, 4, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock23, { 5,4 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageTree5 = GetGameMode()->GetCurMap()->AddMapObject(5, 5, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree5, { 5,5 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> VillageMoveBlock15 = GetGameMode()->GetCurMap()->AddMapObject(5, 6, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock15, { 5,6 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageMoveBlock16 = GetGameMode()->GetCurMap()->AddMapObject(5, 7, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock16, { 5,7 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageBlock24 = GetGameMode()->GetCurMap()->AddMapObject(5, 10, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock24, { 5,10 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock25 = GetGameMode()->GetCurMap()->AddMapObject(5, 11, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock25, { 5,11 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock26 = GetGameMode()->GetCurMap()->AddMapObject(5, 12, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock26, { 5,12 }, EMapObject::VillageBlock1);
			
			std::shared_ptr<AMapObject> VillageBlock27 = GetGameMode()->GetCurMap()->AddMapObject(5, 13, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock27, { 5,13 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock28 = GetGameMode()->GetCurMap()->AddMapObject(5, 14, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock28, { 5,14 }, EMapObject::VillageBlock1);

			
			std::shared_ptr<AMapObject> VillageTree6 = GetGameMode()->GetCurMap()->AddMapObject(6, 0, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree6, { 6,0 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> TownBush7 = GetGameMode()->GetCurMap()->AddMapObject(6, 1, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush7, { 6,1 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageTree7 = GetGameMode()->GetCurMap()->AddMapObject(6, 2, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree7, { 6,2 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> TownBush8 = GetGameMode()->GetCurMap()->AddMapObject(6, 3, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush8, { 6,3 }, EMapObject::TownBush);


			std::shared_ptr<AMapObject> VillageTree8 = GetGameMode()->GetCurMap()->AddMapObject(6, 4, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree8, { 6,4 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> TownBush9 = GetGameMode()->GetCurMap()->AddMapObject(6, 5, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush9, { 6,5 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageMoveBlock17 = GetGameMode()->GetCurMap()->AddMapObject(6, 8, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock17, { 6,8 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> TownBush10 = GetGameMode()->GetCurMap()->AddMapObject(6, 9, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush10, { 6,9 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageTree9 = GetGameMode()->GetCurMap()->AddMapObject(6, 10, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree9, { 6,10 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> TownBush11 = GetGameMode()->GetCurMap()->AddMapObject(6, 11, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush11, { 6,11 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageTree10 = GetGameMode()->GetCurMap()->AddMapObject(6, 12, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree10, { 6,12 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> TownBush12 = GetGameMode()->GetCurMap()->AddMapObject(6, 13, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush12, { 6,13 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageTree11 = GetGameMode()->GetCurMap()->AddMapObject(6, 14, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree11, { 6,14 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> VillageBlock29 = GetGameMode()->GetCurMap()->AddMapObject(7, 0, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock29, { 7,0 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock30 = GetGameMode()->GetCurMap()->AddMapObject(7, 1, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock30, { 7,1 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock31 = GetGameMode()->GetCurMap()->AddMapObject(7, 2, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock31, { 7,2 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock32 = GetGameMode()->GetCurMap()->AddMapObject(7, 3, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock32, { 7,3 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock33 = GetGameMode()->GetCurMap()->AddMapObject(7, 4, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock33, { 7,4 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageMoveBlock18 = GetGameMode()->GetCurMap()->AddMapObject(7, 6, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock18, { 7,6 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageTree12 = GetGameMode()->GetCurMap()->AddMapObject(7, 9, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree12, { 7,9 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> VillageBlock34 = GetGameMode()->GetCurMap()->AddMapObject(7, 10, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock34, { 7,10 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageRedHouse8 = GetGameMode()->GetCurMap()->AddMapObject(7, 11, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse8, { 7,11 }, EMapObject::VillageRedHouse);


			std::shared_ptr<AMapObject> VillageBlock35 = GetGameMode()->GetCurMap()->AddMapObject(7, 12, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock35, { 7,12 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageRedHouse9 = GetGameMode()->GetCurMap()->AddMapObject(7, 13, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse9, { 7,13 }, EMapObject::VillageRedHouse);

			std::shared_ptr<AMapObject> VillageBlock36 = GetGameMode()->GetCurMap()->AddMapObject(7, 14, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock36, { 7,14 }, EMapObject::VillageBlock1);
			
			std::shared_ptr<AMapObject>VillageBlueHouse1= GetGameMode()->GetCurMap()->AddMapObject(8, 0, EMapObject::VillageBlueHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse1, { 8,0 }, EMapObject::VillageBlueHouse);

			std::shared_ptr<AMapObject> VillageMoveBlock19 = GetGameMode()->GetCurMap()->AddMapObject(8, 1, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock19, { 8,1 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageBlueHouse2 = GetGameMode()->GetCurMap()->AddMapObject(8, 2, EMapObject::VillageBlueHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse2, { 8,2 }, EMapObject::VillageBlueHouse);

			std::shared_ptr<AMapObject> VillageMoveBlock20 = GetGameMode()->GetCurMap()->AddMapObject(8, 3, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock20, { 8,3 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageBlueHouse3 = GetGameMode()->GetCurMap()->AddMapObject(8, 4, EMapObject::VillageBlueHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse3, { 8,4 }, EMapObject::VillageBlueHouse);

			std::shared_ptr<AMapObject> TownBush13 = GetGameMode()->GetCurMap()->AddMapObject(8, 5, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush13, { 8,5 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageMoveBlock21 = GetGameMode()->GetCurMap()->AddMapObject(8, 7, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock21, { 8,7 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageMoveBlock22 = GetGameMode()->GetCurMap()->AddMapObject(8, 8, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock22, { 8,8 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> TownBush14 = GetGameMode()->GetCurMap()->AddMapObject(8, 9, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush14, { 8,9 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageBlock37 = GetGameMode()->GetCurMap()->AddMapObject(8, 10, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock37, { 8,10 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock38 = GetGameMode()->GetCurMap()->AddMapObject(8, 11, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock38, { 8,11 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock39 = GetGameMode()->GetCurMap()->AddMapObject(8, 12, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock39, { 8,12 }, EMapObject::VillageBlock2);
			
			std::shared_ptr<AMapObject> VillageBlock40 = GetGameMode()->GetCurMap()->AddMapObject(8, 13, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock40, { 8,13 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock41= GetGameMode()->GetCurMap()->AddMapObject(8, 14, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock41, { 8,14 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock42 = GetGameMode()->GetCurMap()->AddMapObject(9, 0, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock42, { 9,0 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock43 = GetGameMode()->GetCurMap()->AddMapObject(9, 1, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock43, { 9,1 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock44 = GetGameMode()->GetCurMap()->AddMapObject(9, 2, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock44, { 9,2 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock45 = GetGameMode()->GetCurMap()->AddMapObject(9, 3, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock45, { 9,3 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock46 = GetGameMode()->GetCurMap()->AddMapObject(9, 4, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock46, { 9,4 }, EMapObject::VillageBlock2);


			std::shared_ptr<AMapObject> VillageTree13 = GetGameMode()->GetCurMap()->AddMapObject(9, 5, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree13, { 9,5 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> VillageMoveBlock23 = GetGameMode()->GetCurMap()->AddMapObject(9, 6, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock23, { 9,6 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageTree14 = GetGameMode()->GetCurMap()->AddMapObject(9, 9, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree14, { 9,9 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> VillageMoveBlock24 = GetGameMode()->GetCurMap()->AddMapObject(9, 10, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock24, { 9,10 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageRedHouse10 = GetGameMode()->GetCurMap()->AddMapObject(9, 11, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse10, { 9,11 }, EMapObject::VillageRedHouse);

			std::shared_ptr<AMapObject> VillageMoveBlock25 = GetGameMode()->GetCurMap()->AddMapObject(9, 12, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock25, { 9,12 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageRedHouse11 = GetGameMode()->GetCurMap()->AddMapObject(9, 13, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse11, { 9,13 }, EMapObject::VillageRedHouse);

			std::shared_ptr<AMapObject> VillageMoveBlock26 = GetGameMode()->GetCurMap()->AddMapObject(9, 14, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock26, { 9,14 }, EMapObject::VillageMoveBlock);

		
			std::shared_ptr<AMapObject> VillageBlueHouse4 = GetGameMode()->GetCurMap()->AddMapObject(10, 0, EMapObject::VillageBlueHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse4, { 10,0 }, EMapObject::VillageBlueHouse);

			std::shared_ptr<AMapObject> VillageBlueHouse5 = GetGameMode()->GetCurMap()->AddMapObject(10, 2, EMapObject::VillageBlueHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse5, { 10,2 }, EMapObject::VillageBlueHouse);

			std::shared_ptr<AMapObject> VillageMoveBlock27 = GetGameMode()->GetCurMap()->AddMapObject(10, 3, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock27, { 10,3 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageBlueHouse6 = GetGameMode()->GetCurMap()->AddMapObject(10, 4, EMapObject::VillageBlueHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse6, { 10,4 }, EMapObject::VillageBlueHouse);

			std::shared_ptr<AMapObject> TownBush15 = GetGameMode()->GetCurMap()->AddMapObject(10, 5, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush15, { 10,5 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageMoveBlock28 = GetGameMode()->GetCurMap()->AddMapObject(10, 8, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock28, { 10,8 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> TownBush16 = GetGameMode()->GetCurMap()->AddMapObject(10, 9, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush16, { 10,9 }, EMapObject::TownBush);
			
			std::shared_ptr<AMapObject> VillageBlock48 = GetGameMode()->GetCurMap()->AddMapObject(10, 10, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock48, { 10,10 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock49 = GetGameMode()->GetCurMap()->AddMapObject(10, 11, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock49, { 10,11 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock50 = GetGameMode()->GetCurMap()->AddMapObject(10, 12, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock50, { 10,12 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock51 = GetGameMode()->GetCurMap()->AddMapObject(10, 13, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock51, { 10,13 }, EMapObject::VillageBlock2);

			
			std::shared_ptr<AMapObject> VillageBlock52 = GetGameMode()->GetCurMap()->AddMapObject(11, 2, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock52, { 11,2 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock53 = GetGameMode()->GetCurMap()->AddMapObject(11, 3, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock53, { 11,3 }, EMapObject::VillageBlock2);
			
			std::shared_ptr<AMapObject> VillageBlock54 = GetGameMode()->GetCurMap()->AddMapObject(11, 4, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock54, { 11,4 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageTree15 = GetGameMode()->GetCurMap()->AddMapObject(11, 5, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree15, { 11,5 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> VillageMoveBlock29 = GetGameMode()->GetCurMap()->AddMapObject(11, 6, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock29, { 11,6 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageMoveBlock30 = GetGameMode()->GetCurMap()->AddMapObject(11, 7, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock30, { 11,7 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageTree16 = GetGameMode()->GetCurMap()->AddMapObject(11, 9, EMapObject::VillageTree);
			USendPacketManager::SendMapObjectSpawnPacket(VillageTree16, { 11,9 }, EMapObject::VillageTree);

			std::shared_ptr<AMapObject> VillageMoveBlock31 = GetGameMode()->GetCurMap()->AddMapObject(11, 10, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock31, { 11,10 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> VillageRedHouse12 = GetGameMode()->GetCurMap()->AddMapObject(11, 11, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse12, { 11,11 }, EMapObject::VillageRedHouse);
			
			std::shared_ptr<AMapObject> VillageMoveBlock32 = GetGameMode()->GetCurMap()->AddMapObject(11, 12, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock32, { 11,12 }, EMapObject::VillageMoveBlock);


			std::shared_ptr<AMapObject> VillageRedHouse13 = GetGameMode()->GetCurMap()->AddMapObject(11, 13, EMapObject::VillageRedHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse13, { 11,13 }, EMapObject::VillageRedHouse);

			
			std::shared_ptr<AMapObject> VillageBlueHouse7 = GetGameMode()->GetCurMap()->AddMapObject(12, 0, EMapObject::VillageBlueHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse7, { 12,0 }, EMapObject::VillageBlueHouse);

			std::shared_ptr<AMapObject> VillageBlueHouse8 = GetGameMode()->GetCurMap()->AddMapObject(12, 2, EMapObject::VillageBlueHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse8, { 12,2 }, EMapObject::VillageBlueHouse);

			std::shared_ptr<AMapObject> VillageBlock55 = GetGameMode()->GetCurMap()->AddMapObject(12, 3, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock55, { 12,3 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlueHouse9 = GetGameMode()->GetCurMap()->AddMapObject(12, 4, EMapObject::VillageBlueHouse);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse9, { 12,4 }, EMapObject::VillageBlueHouse);

			std::shared_ptr<AMapObject> TownBush17 = GetGameMode()->GetCurMap()->AddMapObject(12, 5, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush17, { 12,5 }, EMapObject::TownBush);

			std::shared_ptr<AMapObject> VillageMoveBlock33 = GetGameMode()->GetCurMap()->AddMapObject(12, 8, EMapObject::VillageMoveBlock);
			USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock33, { 12,8 }, EMapObject::VillageMoveBlock);

			std::shared_ptr<AMapObject> TownBush18 = GetGameMode()->GetCurMap()->AddMapObject(12, 9, EMapObject::TownBush);
			USendPacketManager::SendMapObjectSpawnPacket(TownBush18, { 12,9 }, EMapObject::TownBush);
			
			std::shared_ptr<AMapObject> VillageBlock56 = GetGameMode()->GetCurMap()->AddMapObject(12, 10, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock56, { 12,10 }, EMapObject::VillageBlock2);

			std::shared_ptr<AMapObject> VillageBlock57 = GetGameMode()->GetCurMap()->AddMapObject(12, 11, EMapObject::VillageBlock1);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock57, { 12,11 }, EMapObject::VillageBlock1);

			std::shared_ptr<AMapObject> VillageBlock58 = GetGameMode()->GetCurMap()->AddMapObject(12, 12, EMapObject::VillageBlock2);
			USendPacketManager::SendMapObjectSpawnPacket(VillageBlock58, { 12,12 }, EMapObject::VillageBlock2);
		
		
		
		
		
		}

	}
}