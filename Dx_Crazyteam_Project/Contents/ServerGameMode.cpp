#include "PreCompile.h"
#include "ServerGameMode.h"
#include <EngineBase/EngineProtocol.h>

#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>


#include "ServerTestOtherPlayer.h"
#include "ServerTestPlayer.h"
#include "Game_Core.h"
#include "Packets.h"
#include "TestPackets.h"
#include "OtherPlayer.h"
#include "Village.h"
#include "Camp.h"
#include "ItemBubble.h"
#include "MapObject.h"
#include "BaseMap.h"

#include "TitleMenu.h"
#include "PlayLobby.h"

#include "TestLobbyMode.h"
#include "stringHelper.h"
#include <EnginePlatform/TextimeInput.h>


std::shared_ptr<UEngineNetWindow> AServerGameMode::NetWindow = nullptr;
bool AServerGameMode::IsServerOpen = false;
ENetType AServerGameMode::NetType = ENetType::None;


AServerGameMode::AServerGameMode() 
{
}

AServerGameMode::~AServerGameMode() 
{
	if (nullptr != UGame_Core::Net)
	{
		UGame_Core::Net->End();
		UGame_Core::Net = nullptr;
	}
}

void AServerGameMode::BeginPlay() 
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	//std::shared_ptr<APlayer> Player1 = GetWorld()->SpawnActor<AServerTestPlayer>("Player1", 0);
	//Player1->SetCurGameMode(this);
	//SetMainPlayer(Player1);

}

void AServerGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//UNetObject::AllNetObject;
}

void AServerGameMode::LevelStart(ULevel* _PrevLevel)
{

	//if (nullptr == NetWindow)
	//{
	//	NetWindow = UEngineEditorGUI::CreateEditorWindow<UEngineNetWindow>("NetWindow");

	//	NetWindow->SetServerOpenFunction([&]()
	//		{
	//			UGame_Core::Net = std::make_shared<UEngineServer>();
	//			UGame_Core::Net->ServerOpen(30000, 512);

	//			//GetPlayer()->SetObjectToken(UNetObject::GetNewObjectToken());
	//			

	//			//ServerPacketInit(UGame_Core::Net->Dispatcher);
	//		});

	//	NetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
	//		{
	//			UGame_Core::Net = std::make_shared<UEngineClient>();
	//			UGame_Core::Net->Connect(IP, PORT);

	//			//UGame_Core::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
	//			//	{
	//			//		GetPlayer()->SetObjectToken(_Token->GetObjectToken());
	//			//	});

	//			// 어떤 패키싱 왔을때 어떻게 처리할건지를 정하는 걸 해야한다.
	//			//ClientPacketInit(UGame_Core::Net->Dispatcher);
	//		});
	//}
	//NetWindow->Off();
}

void AServerGameMode::ServerPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			// 다른 사람들한테 이 오브젝트에 대해서 알리고
		    UGame_Core::Net->Send(_Packet);

			GetWorld()->PushFunction([=]()
				{
					switch (_Packet->ObjectType)
					{	
					case static_cast<int>(EObjectType::Player):
					{
						AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
						if (nullptr == OtherPlayer)
						{
							OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
							OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
						}
						OtherPlayer->PushProtocol(_Packet);
						break;
					}
					default:
						break;
					}
				});
		});

	Dis.AddHandler<UMapObjectUpdatePacket>([=](std::shared_ptr<UMapObjectUpdatePacket> _Packet)
		{
			UGame_Core::Net->Send(_Packet);
					
			// Other 오브젝트 릴리즈
			if (true == _Packet->IsDestroy)
			{
				AMapObject* OtherItem = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
				if (nullptr != OtherItem)
				{
					POINT Pos = _Packet->Pos;
					GetCurMap()->DestroyMapObject(Pos.y, Pos.x);
				}
				return;
			}

			// Other 오브젝트 이동
			if (true == _Packet->IsMove)
			{
				AMapObject* OtherBlock = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
				if (nullptr != OtherBlock)
				{
					OtherBlock->SetActorLocation(_Packet->MovePos);
				}
				return;
			}

			// Other 오브젝트 이동 종료
			if (true == _Packet->IsMoveEnd)
			{
				AMapObject* OtherBlock = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
				if (nullptr != OtherBlock)
				{
					GetCurMap()->MoveMapObject(OtherBlock->shared_from_this(), _Packet->MoveEndPos.y, _Packet->MoveEndPos.x, _Packet->MoveBeginPos.y, _Packet->MoveBeginPos.x);
				}
				return;
			}

			// 물풍선 관련 오브젝트 생성 관련
			EMapObject ObjType = static_cast<EMapObject>(_Packet->ObjectType);

			switch (ObjType)
			{
			case EMapObject::Water:
			case EMapObject::WaterBomb:
			{
				AMapObject* OtherObject = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());

				if (nullptr == OtherObject)
				{
					ABaseMap* CurMap = GetCurMap().get();
					POINT PosValue = _Packet->Pos;

					OtherObject = CurMap->AddMapObject(PosValue.x, PosValue.y, ObjType).get();

					OtherObject->SetObjectToken(_Packet->GetObjectToken());
				}
				break;
			}
			default:
				MsgBoxAssert("Server가 아닌 곳에서 MapObject를 생성하려 했습니다.");
				return;
			}

		});
}

void AServerGameMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			GetWorld()->PushFunction([=]()
				{
					switch (_Packet->ObjectType)
					{
					case static_cast<int>(EObjectType::Player):
					{
						AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
						if (nullptr == OtherPlayer)
						{
							OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
							OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
						}
						OtherPlayer->PushProtocol(_Packet);
						break;
					}
					default:
						break;
					}
				});
		});

	Dis.AddHandler<UMapObjectUpdatePacket>([=](std::shared_ptr<UMapObjectUpdatePacket> _Packet)
		{
			// Other 오브젝트 소멸 관련
			if (true == _Packet->IsDestroy)
			{
				AMapObject* OtherItem = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
				if (nullptr != OtherItem)
				{
					POINT Pos = _Packet->Pos;
					GetCurMap()->DestroyMapObject(Pos.y, Pos.x);
				}
				return;
			}

			// Other 오브젝트 이동
			if (true == _Packet->IsMove)
			{
				AMapObject* OtherBlock = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
				if (nullptr != OtherBlock)
				{
					OtherBlock->SetActorLocation(_Packet->MovePos);
				}
				return;
			}

			// Other 오브젝트 이동 종료
			if (true == _Packet->IsMoveEnd)
			{
				AMapObject* OtherBlock = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
				if (nullptr != OtherBlock)
				{
					GetCurMap()->MoveMapObject(OtherBlock->shared_from_this(), _Packet->MoveEndPos.y, _Packet->MoveEndPos.x, _Packet->MoveBeginPos.y, _Packet->MoveBeginPos.x);
				}
				return;
			}

			// Other 오브젝트 생성 관련
			EMapObject ObjType = static_cast<EMapObject>(_Packet->ObjectType);

			switch (ObjType)
			{
			case EMapObject::DummyBlock:
			case EMapObject::NormalBlock:
			case EMapObject::CampBlock1:
			case EMapObject::CampBlock2:
			case EMapObject::CampBlock3:
			case EMapObject::CampBlock4:
			case EMapObject::CampMoveBlock1:
			case EMapObject::CampMoveBlock2:
			case EMapObject::CampHPBlock:
			case EMapObject::WaterBomb:
			case EMapObject::Water:
			case EMapObject::TownBush:
			{
				AMapObject* OtherObject = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());

				if (nullptr == OtherObject)
				{
					ABaseMap* CurMap = GetCurMap().get();
					POINT PosValue = _Packet->Pos;

					OtherObject = CurMap->AddMapObject(PosValue.x, PosValue.y, ObjType).get();

					OtherObject->SetObjectToken(_Packet->GetObjectToken());
				}
				break;
			}
			case EMapObject::Item:
			{
				EItemType ItemType = static_cast<EItemType>(_Packet->ItemType);

				if (EItemType::None == ItemType)
				{
					MsgBoxAssert("아이템 타입을 지정하지 않았습니다. 지정해주세요.");
					return;
				}

				// UActorUpdatePacket으로 아이템 정보가 날라왔을 때 자신에게도 Item이 보이는 기능 구현
				AMapObject* OtherItem = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());

				if (nullptr == OtherItem)
				{
					ABaseMap* CurMap = GetCurMap().get();
					POINT PosValue = _Packet->Pos;

					switch (ItemType)
					{
					case EItemType::ItemBubble:
					case EItemType::ItemFluid:
					case EItemType::ItemNiddle:
					case EItemType::ItemOwl:
					case EItemType::ItemRoller:
					case EItemType::ItemShoes:
						OtherItem = CurMap->AddMapObject(PosValue.x, PosValue.y, EMapObject::Item, ItemType).get();
						break;
					default:
						MsgBoxAssert("지정되지 않은 타입입니다. 아이템 타입을 확인하세요.");
						return;
					}

					OtherItem->SetObjectToken(_Packet->GetObjectToken());
				}
				break;
			}
			case EMapObject::Default:
			default:
				MsgBoxAssert("Type이 Default타입이거나 지정되지 않은 타입입니다.");
				return;
			}
			
		});
}

void AServerGameMode::ServerOpen()
{
	if (nullptr == NetWindow)
	{
		NetWindow = UEngineEditorGUI::CreateEditorWindow<UEngineNetWindow>("NetWindow");

		NetWindow->SetServerOpenFunction([&]()
			{
				UGame_Core::Net = std::make_shared<UEngineServer>();
				UGame_Core::Net->ServerOpen(30000, 512);
				SetIsServerOpen(true);
				AServerGameMode::NetType = ENetType::Server;
				stringHelper::SetPlayerName(UTextimeInput::GetReadText());
				UTextimeInput::Off();

				//GetPlayer()->SetObjectToken(UNetObject::GetNewObjectToken());


				//ServerPacketInit(UGame_Core::Net->Dispatcher);
			});

		NetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
			{
				UGame_Core::Net = std::make_shared<UEngineClient>();
				UGame_Core::Net->Connect(IP, PORT);
				
				AServerGameMode::NetType = ENetType::Client;

				SetIsServerOpen(true);
				stringHelper::SetPlayerName(UTextimeInput::GetReadText());
				UTextimeInput::Off();

				//UGame_Core::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
				//	{
				//		GetPlayer()->SetObjectToken(_Token->GetObjectToken());
				//	});

				// 어떤 패키싱 왔을때 어떻게 처리할건지를 정하는 걸 해야한다.
				//ClientPacketInit(UGame_Core::Net->Dispatcher);
			});
	}
	NetWindow->On();
}

//std::shared_ptr<APlayLobby> AServerGameMode::GetPlayLobby()
//{
//	return PlayLobby;
//}

void AServerGameMode::LevelEnd(ULevel* _NextLevel)
{
	NetWindow->Off();
}

void AServerGameMode::CollectWindowAppear()
{
	NetWindow->On();
}