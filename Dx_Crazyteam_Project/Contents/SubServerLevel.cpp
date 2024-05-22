#include "PreCompile.h"
#include "SubServerLevel.h"

#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>
#include <EnginePlatform/EngineInput.h>

#include "ServerPlayer.h"
#include "Game_Core.h"
#include "Packets.h"
#include "Player.h"
#include "OtherPlayer.h"
#include "Village.h"
#include "Camp.h"
#include "WaterBomb.h"
#include "OtherUI.h"
#include "CAGameMode.h"
#include "BaseMap.h"
#include "MapUI.h"
#include <EngineBase/NetObject.h>

ASubServerLevel::ASubServerLevel()
{
	if (nullptr != UGame_Core::Net)
	{
		UGame_Core::Net->End();
		UGame_Core::Net = nullptr;
	}
}

ASubServerLevel::~ASubServerLevel()
{
}

void ASubServerLevel::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(80.0f, 1.0f, -1000.0f));

	//Village = GetWorld()->SpawnActor<AVillage>("Village");
	//SetCurMap(Village);

	std::shared_ptr<ACamp> Camp = GetWorld()->SpawnActor<ACamp>("Camp");
	SetCurMap(Camp);
	Camp->SetCurGameMode(this);


	MainPlayer = GetWorld()->SpawnActor<APlayer>("Player");
	MainPlayer->SetCurGameMode(this);
	SetMainPlayer(MainPlayer);

	MapUI = GetWorld()->SpawnActor<AMapUI>("MapUI");
	MapUI->SetCurGameMode(this);
	SetUI(MapUI);
	FVector Pos = MapUI->GetActorLocation();
	Pos.Z = 100.f;
	MapUI->SetActorLocation(Pos);
}

void ASubServerLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UNetObject::AllNetObject;
}

void ASubServerLevel::LevelStart(ULevel* _DeltaTime)
{
	if (nullptr == subNetWindow)
	{
		subNetWindow = UEngineEditorGUI::CreateEditorWindow<UEngineNetWindow>("subNetWindow");

		subNetWindow->SetServerOpenFunction([&]()
		{
			UGame_Core::Net = std::make_shared<UEngineServer>();
			UGame_Core::Net->ServerOpen(30000, 512);

			// 여기에서 메인 플레이어한테 번호를 하나 줄겁니다.

			MainPlayer->SetObjectToken(UNetObject::GetNewObjectToken());

			// 타임 유아이
			MapUI->SetObjectToken(UNetObject::GetNewObjectToken() + 1);

			ServerPacketInit(UGame_Core::Net->Dispatcher);
		});

		subNetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
		{
			UGame_Core::Net = std::make_shared<UEngineClient>();
			UGame_Core::Net->Connect(IP, PORT);

			UGame_Core::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
			{
				MainPlayer->SetObjectToken(_Token->GetSessionToken() * 1000);

				//타임 유아이
				MapUI->SetObjectToken(_Token->GetSessionToken() * 1000+1);
				if (nullptr != MapUI)
				{
					MapUI->ClientCreate();
				}
				//물폭탄
				MainPlayer->WaterBomb_Token = _Token->GetSessionToken() * 1000 + 2;
				//물폭탄물줄기
				MainPlayer->WaterCourse_Token = _Token->GetSessionToken() * 10000;
			});
			// 어떤 패키싱 왔을때 어떻게 처리할건지를 정하는 걸 해야한다.
			ClientPacketInit(UGame_Core::Net->Dispatcher);
		});
	}
	subNetWindow->On();
}

void ASubServerLevel::ServerPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
	{
		// 다른 사람들한테 이 오브젝트에 대해서 알리고
		UGame_Core::Net->Send(_Packet);		

		GetWorld()->PushFunction([=]()
		{
			AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
			if (nullptr == OtherPlayer)
			{
				OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
				OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
			}
			OtherPlayer->PushProtocol(_Packet);
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

	Dis.AddHandler<UUIUpdatePacket>([=](std::shared_ptr<UUIUpdatePacket> _Packet)
		{
			// 다른 사람들한테 이 오브젝트에 대해서 알리고
			UGame_Core::Net->Send(_Packet);

			GetWorld()->PushFunction([=]()
				{
					AOtherUI* Time = UNetObject::GetNetObject<AOtherUI>(_Packet->GetObjectToken());
					if (nullptr == Time)
					{
						Time = this->GetWorld()->SpawnActor<AOtherUI>("UI", 0).get();
						Time->SetObjectToken(_Packet->GetObjectToken());
					}
					Time->PushProtocol(_Packet);
				});
		});
}

void ASubServerLevel::ClientPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
	{
		GetWorld()->PushFunction([=]()
		{
			AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
			if (nullptr == OtherPlayer)
			{
				OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
				OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
			}
			OtherPlayer->PushProtocol(_Packet);
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

	Dis.AddHandler<UUIUpdatePacket>([=](std::shared_ptr<UUIUpdatePacket> _Packet)
		{
			// 다른 사람들한테 이 오브젝트에 대해서 알리고
			GetWorld()->PushFunction([=]()
				{
					int Test = _Packet->GetObjectToken();

					AOtherUI* Time = UNetObject::GetNetObject<AOtherUI>(_Packet->GetObjectToken());
					if (nullptr == Time)
					{
						Time = this->GetWorld()->SpawnActor<AOtherUI>("UI", 0).get();
						Time->SetObjectToken(_Packet->GetObjectToken());
					}
					Time->PushProtocol(_Packet);

				});
		});	
}

void ASubServerLevel::LevelEnd(ULevel* _DeltaTime)
{
	subNetWindow->Off();
}
