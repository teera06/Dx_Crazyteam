#include "PreCompile.h"
#include "MainGameMode.h"

#include <EngineCore/TextWidget.h>
#include <EnginePlatform/TextimeInput.h>

#include "MapUI.h"
#include "Player.h"
#include "OtherPlayer.h"

#include "Village.h"
#include "Camp.h"
#include "Player_Name.h"

#include "ItemBubble.h"
#include "ItemRoller.h"
#include "ItemNiddle.h"
#include "ItemOwl.h"
#include <EngineBase/NetObject.h>
#include "WaterCourse.h"

#include "ServerGameMode.h"
#include "Game_Core.h"
#include "Packets.h"
#include "OtherUI.h"
#include "ServerTestPlayer.h"
#include "ContentsValue.h"
#include "SendPacketManager.h"


AMainGameMode::AMainGameMode()
{
}

AMainGameMode::~AMainGameMode()
{
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->DepthOn();
	//깊이버퍼 실행시 DepthOn

	GameModeActorInit();

	//ACAGameMode::OtherPlayers.clear();
#ifdef _DEBUG
	InputOn();
#endif
}

void AMainGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	int PlayerNum = static_cast<int>(UContentsValue::PlayerIDs.size());
	
	UNetObject::AllNetObject;

	if (false == IsSpawnBlocks
		&& AServerGameMode::NetType == ENetType::Server
		&& PlayerNum == UContentsValue::LobbyPlayerNum
		)
	{
		EMapType MapType = GetWorld()->GetMapType();

		switch (MapType)
		{
		case EMapType::Camp:
			CreateCampBlocks();
			ACAGameMode::BattleStart = true;
			break;
		case EMapType::Village:
			CreateVillageBlocks();
			ACAGameMode::BattleStart = true;
			break;
		default:
			MsgBoxAssert("지정된 MapType이 아닙니다.");
			return;
		}
		IsSpawnBlocks = true;
	}
	else if (false == IsSpawnBlocks
		&& AServerGameMode::NetType == ENetType::Client
		&& PlayerNum == UContentsValue::LobbyPlayerNum)
	{
		ACAGameMode::BattleStart = true;

		IsSpawnBlocks = true;
	}


	//UTextimeInput::IMEInput();
	
	//std::string Text = UTextimeInput::GetReadText();
	//if (Text.size() > 0)
	//{
	//	ShowText->SetText(Text);
	//}
	//else
	//{
	//	ShowText->SetText(" ");
	//}
}

void AMainGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	// Packet 처리 등록을 보장하기 위한 변수
	UEngineDispatcher::IsPacketInit = false;
	UEngineSound::SoundPlay("GameStart.wav");
	switch (GetWorld()->GetMapType())
	{
	case EMapType::Village:
	{
		std::shared_ptr<AVillage> Village = GetWorld()->SpawnActor<AVillage>("Village");
		SetCurMap(Village);
		Village->SetCurGameMode(this);
		MainBGM = UEngineSound::SoundPlay("VillageBGM.mp3");
		MainBGM.Loop();
		break;

	}
	case EMapType::Camp:
	{
		std::shared_ptr<ACamp> Camp = GetWorld()->SpawnActor<ACamp>("Camp");
		SetCurMap(Camp);
		Camp->SetCurGameMode(this);
		MainBGM = UEngineSound::SoundPlay("CampBGM.mp3");
		MainBGM.Loop();
		break;
	}
	default:
		break;
	}
	
	if (AServerGameMode::NetType == ENetType::Server)
	{
			{
				//UGame_Core::Net = std::make_shared<UEngineServer>();
				//UGame_Core::Net->ServerOpen(30000, 512);

				MainPlayer = GetWorld()->SpawnActor<APlayer>("Player1", 0);
				MainPlayer->SetCurGameMode(this);
				SetMainPlayer(MainPlayer);

				switch (GetWorld()->GetMapType())
				{
				case EMapType::Village:
				{
					FVector InitPos = GetCurMap()->PointToPos(ConstValue::VillageStartPOINT[UGame_Core::Net->GetSessionToken()]);
					MainPlayer->SetActorLocation(InitPos);
					break;
				}
				case EMapType::Camp:
				{
					FVector InitPos = GetCurMap()->PointToPos(ConstValue::CampStartPOINT[UGame_Core::Net->GetSessionToken()]);
					MainPlayer->SetActorLocation(InitPos);
					break;
				}
				default:
					break;
				}

				// 여기에서 메인 플레이어한테 번호를 하나 줄겁니다.
				MainPlayer->SetObjectToken(UNetObject::GetNewObjectToken());


				// 타임 유아이
				MapUI = GetWorld()->SpawnActor<AMapUI>("MapUI");
				MapUI->SetCurGameMode(this);
				MapUI->SetObjectToken(UNetObject::GetNewObjectToken());
				SetUI(MapUI);

				//물폭탄
				MainPlayer->WaterBomb_Token = UGame_Core::Net->GetSessionToken() * 1000 + 2;
				ServerPacketInit(UGame_Core::Net->Dispatcher);

				//세션토큰을 PlayerIDs에 넣어서 관리
				UContentsValue::PlayerIDs.push_back(UGame_Core::Net->GetSessionToken());
			};

			MapUI->MapTimeLogic = [=](AMapUI* _Lobby)
				{										
		/*			std::shared_ptr<UUIUpdatePacket> TimeCreate= std::make_shared<UUIUpdatePacket>();
					TimeCreate->SerVerSend = true;
					TimeCreate->Second_Tens = MapUI->GetCreateTime();
					UGame_Core::Net->Send(TimeCreate);*/
				};


	}
	else if (AServerGameMode::NetType == ENetType::Client)
	{
			{
				//UGame_Core::Net = std::make_shared<UEngineClient>();
				//UGame_Core::Net->Connect(IP, PORT);

				//UGame_Core::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
					//{

				MainPlayer = GetWorld()->SpawnActor<APlayer>("Player1", 0);
				MainPlayer->SetCurGameMode(this);
				SetMainPlayer(MainPlayer);

				switch (GetWorld()->GetMapType())
				{
				case EMapType::Village:
				{
					FVector InitPos = GetCurMap()->PointToPos(ConstValue::VillageStartPOINT[UGame_Core::Net->GetSessionToken()]);
					MainPlayer->SetActorLocation(InitPos);
					break;
				}
				case EMapType::Camp:
				{
					FVector InitPos = GetCurMap()->PointToPos(ConstValue::CampStartPOINT[UGame_Core::Net->GetSessionToken()]);
					MainPlayer->SetActorLocation(InitPos);
					break;
				}
				default:
					break;
				}

				MainPlayer->SetObjectToken(UGame_Core::Net->GetSessionToken() * 1000);

				//타임 유아이

				MapUI = GetWorld()->SpawnActor<AMapUI>("MapUI");
				MapUI->SetCurGameMode(this);
				MapUI->SetObjectToken(UGame_Core::Net->GetSessionToken() * 1000 + 1);
				SetUI(MapUI);
	
				//물폭탄
				MainPlayer->WaterBomb_Token = UGame_Core::Net->GetSessionToken() * 1000 + 2;
					//});
				// 어떤 패키싱 왔을때 어떻게 처리할건지를 정하는 걸 해야한다
				ClientPacketInit(UGame_Core::Net->Dispatcher);
			};

			MapUI->MapTimeLogic = [=](AMapUI* _Lobby)
			{
				std::shared_ptr<UUIUpdatePacket> TimeCreate = std::make_shared<UUIUpdatePacket>();
				TimeCreate->ClientCreate = true;
				int a = UGame_Core::Net->GetSessionToken();
				TimeCreate->SetSessionToken(UGame_Core::Net->GetSessionToken());
				TimeCreate->SetObjectToken(MapUI->GetObjectToken());
				UGame_Core::Net->Send(TimeCreate);	
			};
	}
}

void AMainGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	MainBGM.Off();

	InfoRelease();
}


void AMainGameMode::ServerPacketInit(UEngineDispatcher& Dis)
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
					ACAGameMode::OtherPlayers.push_back(OtherPlayer);
					
					// 클라이언트가 접속했을 때, 생성하면 PlayerIDs에 세션 토큰 넣어서 관리
					UContentsValue::PlayerIDs.push_back(_Packet->GetSessionToken());
				}
				OtherPlayer->PushProtocol(_Packet);
			});
	});

	Dis.AddHandler<UMapObjectUpdatePacket>([=](std::shared_ptr<UMapObjectUpdatePacket> _Packet)
	{
		UGame_Core::Net->Send(_Packet);

		GetWorld()->PushFunction([=]()
			{
				// Other 오브젝트 릴리즈
				if (true == _Packet->IsDestroy)
				{
					if (false == UNetObject::IsNetObject(_Packet->GetObjectToken()))
					{
						return;
					}

					AMapObject* OtherItem = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
					if (nullptr != OtherItem)
					{
						POINT Pos = _Packet->Pos;
						GetCurMap()->DestroyMapObject(Pos.y, Pos.x);
						//UNetObject::ReleaseObjectToken(_Packet->GetObjectToken());
					}
					return;
				}

				// Other 오브젝트 이동
				if (true == _Packet->IsMove)
				{
					if (false == UNetObject::IsNetObject(_Packet->GetObjectToken()))
					{
						return;
					}

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
					if (false == UNetObject::IsNetObject(_Packet->GetObjectToken()))
					{
						return;
					}

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
				case EMapObject::WaterBomb:
				{
					AMapObject* OtherObject = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());

					if (nullptr == OtherObject)
					{
						ABaseMap* CurMap = GetCurMap().get();
						POINT PosValue = _Packet->Pos;

						OtherObject = CurMap->SpawnWaterBomb(PosValue.x, PosValue.y, _Packet->WaterPower, _Packet->CreaterToken).get();

						OtherObject->SetObjectToken(_Packet->GetObjectToken());
					}
					break;
				}
				default:
					MsgBoxAssert("Server가 아닌 곳에서 MapObject를 생성하려 했습니다.");
					return;
				}
			});
	});

	Dis.AddHandler<UUIUpdatePacket>([=](std::shared_ptr<UUIUpdatePacket> _Packet)
	{
		// 다른 사람들한테 이 오브젝트에 대해서 알리고
		//UGame_Core::Net->Send(_Packet);

		GetWorld()->PushFunction([=]()
		{
				int Test = _Packet->GetObjectToken();
				AMapUI* Time = UNetObject::GetNetObject<AMapUI>(_Packet->GetObjectToken());
				if (nullptr == Time)
				{
					int a = 0;
					//Time = this->GetWorld()->SpawnActor<AOtherUI>("UI", 0).get();
					//Time->SetObjectToken(_Packet->GetObjectToken());
				}
				else
				{
					if (_Packet->ClientCreate == true)
					{
						std::shared_ptr<UUIUpdatePacket> TimeCreate = std::make_shared<UUIUpdatePacket>();
						TimeCreate->SerVerSend = true;
						TimeCreate->Time_Second = MapUI->GetCreateTime();
						TimeCreate->SetSessionToken(UGame_Core::Net->GetSessionToken());
						TimeCreate->SetObjectToken(MapUI->GetObjectToken());

						UGame_Core::Net->Send(TimeCreate);
					}
				}//Time->PushProtocol(_Packet);					
		});
	});
}

void AMainGameMode::ClientPacketInit(UEngineDispatcher& Dis)
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
						ACAGameMode::OtherPlayers.push_back(OtherPlayer);
					}
					OtherPlayer->PushProtocol(_Packet);
				});

	});

	Dis.AddHandler<UMapObjectUpdatePacket>([=](std::shared_ptr<UMapObjectUpdatePacket> _Packet)
		{
			GetWorld()->PushFunction([=]()
				{
					// Other 오브젝트 소멸 관련
					if (true == _Packet->IsDestroy)
					{
						if (false == UNetObject::IsNetObject(_Packet->GetObjectToken()))
						{
							return;
						}

						AMapObject* OtherItem = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
						if (nullptr != OtherItem)
						{
							POINT Pos = _Packet->Pos;
							GetCurMap()->DestroyMapObject(Pos.y, Pos.x);
							//UNetObject::ReleaseObjectToken(_Packet->GetObjectToken());
						}
						return;
					}

					// Other 오브젝트 이동
					if (true == _Packet->IsMove)
					{
						if (false == UNetObject::IsNetObject(_Packet->GetObjectToken()))
						{
							return;
						}

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
						if (false == UNetObject::IsNetObject(_Packet->GetObjectToken()))
						{
							return;
						}

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
					case EMapObject::WaterBomb:
					{
						AMapObject* OtherObject = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());

						if (nullptr == OtherObject)
						{
							ABaseMap* CurMap = GetCurMap().get();
							POINT PosValue = _Packet->Pos;

							OtherObject = CurMap->SpawnWaterBomb(PosValue.x, PosValue.y, _Packet->WaterPower, _Packet->CreaterToken).get();

							OtherObject->SetObjectToken(_Packet->GetObjectToken());
						}
						break;
					}
					case EMapObject::TownBush:
					case EMapObject::DummyBlock:
					case EMapObject::NormalBlock:
					case EMapObject::CampBlock1:
					case EMapObject::CampBlock2:
					case EMapObject::CampBlock3:
					case EMapObject::CampBlock4:
					case EMapObject::CampMoveBlock1:
					case EMapObject::CampMoveBlock2:
					case EMapObject::CampHPBlock:
					case EMapObject::VillageBlock1:
					case EMapObject::VillageBlock2:
					case EMapObject::VillageMoveBlock:
					case EMapObject::VillageTree:
					case EMapObject::VillageBlueHouse:
					case EMapObject::VillageRedHouse:
					case EMapObject::VillageYellowHouse:
					{
						AMapObject* OtherObject = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());

						if (nullptr == OtherObject)
						{
							ABaseMap* CurMap = GetCurMap().get();
							POINT PosValue = _Packet->Pos;

							OtherObject = CurMap->AddMapObject(PosValue.x, PosValue.y, ObjType).get();

							EItemType ItemType = static_cast<EItemType>(_Packet->ItemType);

							if (EItemType::None != ItemType)
							{
								OtherObject->SetPossessItem(ItemType);
							}

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
							case EItemType::ItemRoller:
							case EItemType::ItemOwl:
							case EItemType::ItemTurtle:
							case EItemType::ItemNiddle:
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
					default:
						MsgBoxAssert("Type이 Default타입이거나 지정되지 않은 타입입니다.");
						return;
					}
				});
		});

	Dis.AddHandler<UUIUpdatePacket>([=](std::shared_ptr<UUIUpdatePacket> _Packet)
	{
		// 다른 사람들한테 이 오브젝트에 대해서 알리고
		GetWorld()->PushFunction([=]()
		{
				int Test = _Packet->GetObjectToken();
				AMapUI* Time = UNetObject::GetNetObject<AMapUI>(_Packet->GetObjectToken());
				if (nullptr == Time)
				{
					int a = 0;
				}
				else
				{
					if (_Packet->ClientCreate == true)
					{			
						Time->ServerGetTime(_Packet->Time_Second);	
					}
				}
				Time->PushProtocol(_Packet);
		});
	});
}

void AMainGameMode::GameModeActorInit()
{
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(80.0f, 1.0f, -1000.0f));



	//{//Text
	//	ShowText = CreateWidget<UTextWidget>(GetWorld(), "ShowText");
	//	ShowText->SetFont("맑은 고딕");
	//	ShowText->SetScale(30.0f);
	//	ShowText->SetColor(Color8Bit::Black);
	//	ShowText->SetPosition({ 0.0f ,0.0f });
	//	ShowText->SetFlag(FW1_LEFT);
	//	ShowText->AddToViewPort(11);
	//}




	////Item - Camp
	//{
	//	Camp->AddMapObject(5, 1, EMapObject::Item, EItemType::ItemBubble);
	//	Camp->AddMapObject(1, 2, EMapObject::Item, EItemType::ItemNiddle);
	//	Camp->AddMapObject(2, 1, EMapObject::Item, EItemType::ItemOwl);
	//	Camp->AddMapObject(2, 2, EMapObject::Item, EItemType::ItemShoes);
	//	Camp->AddMapObject(8, 6, EMapObject::Item, EItemType::ItemRoller);
	//	Camp->AddMapObject(6, 8, EMapObject::Item, EItemType::ItemFluid);
	//}
	////Camp 내 Object 그대로하려면 아래코드로
	//{
	//	Camp->AddObjectInit();
	//}


	////Item - Village
	//{
	//	Village->AddMapObject(0, 0, EMapObject::Item, EItemType::ItemBubble);
	//	Village->AddMapObject(1, 0, EMapObject::Item, EItemType::ItemNiddle);
	//	Village->AddMapObject(2, 0, EMapObject::Item, EItemType::ItemTurtle);
	//	Village->AddMapObject(2, 1, EMapObject::Item, EItemType::ItemOwl);
	//	Village->AddMapObject(2, 2, EMapObject::Item, EItemType::ItemShoes);
	//	Village->AddMapObject(8, 6, EMapObject::Item, EItemType::ItemRoller);
	//	Village->AddMapObject(6, 8, EMapObject::Item, EItemType::ItemFluid);
	//}
	////Camp 내 Object 그대로하려면 아래코드로
	//{
	//	Village->AddObjectInit();
	//}



}

void AMainGameMode::InfoRelease()
{
	IsSpawnBlocks = false;
}

void AMainGameMode::CreateVillageBlocks()
{
	// 빌리지
	std::shared_ptr<AMapObject> vilBlock1 = GetCurMap()->AddMapObject(0, 1, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(vilBlock1, { 0,1 }, EMapObject::VillageBlock2, vilBlock1->GetPossessItem());

	std::shared_ptr<AMapObject> vilBlock2 = GetCurMap()->AddMapObject(0, 2, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(vilBlock2, { 0,2 }, EMapObject::VillageBlock1, vilBlock2->GetPossessItem());

	std::shared_ptr<AMapObject> vilBlock3 = GetCurMap()->AddMapObject(0, 3, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(vilBlock3, { 0,3 }, EMapObject::VillageBlock2, vilBlock3->GetPossessItem());

	std::shared_ptr<AMapObject> vilBlock4 = GetCurMap()->AddMapObject(0, 4, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(vilBlock4, { 0,4 }, EMapObject::VillageBlock1, vilBlock4->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush1 = GetCurMap()->AddMapObject(0, 5, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush1, { 0,5 }, EMapObject::TownBush, TownBush1->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock = GetCurMap()->AddMapObject(0, 8, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock, { 0,8 }, EMapObject::VillageMoveBlock, VillageMoveBlock->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush2 = GetCurMap()->AddMapObject(0, 9, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush2, { 0,9 }, EMapObject::TownBush, TownBush2->GetPossessItem());

	std::shared_ptr<AMapObject> VillageYellowHouse1 = GetCurMap()->AddMapObject(0, 10, EMapObject::VillageYellowHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse1, { 0,10 }, EMapObject::VillageYellowHouse, VillageYellowHouse1->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock5 = GetCurMap()->AddMapObject(0, 11, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock5, { 0,11 }, EMapObject::VillageBlock1, VillageBlock5->GetPossessItem());

	std::shared_ptr<AMapObject> VillageYellowHouse2 = GetCurMap()->AddMapObject(0, 12, EMapObject::VillageYellowHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse2, { 0,12 }, EMapObject::VillageYellowHouse, VillageYellowHouse2->GetPossessItem());

	std::shared_ptr<AMapObject> VillageYellowHouse3 = GetCurMap()->AddMapObject(0, 14, EMapObject::VillageYellowHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse3, { 0,14 }, EMapObject::VillageYellowHouse, VillageYellowHouse3->GetPossessItem());

	std::shared_ptr<AMapObject> VillageRedHouse = GetCurMap()->AddMapObject(1, 1, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse, { 1,1 }, EMapObject::VillageRedHouse, VillageRedHouse->GetPossessItem());

	std::shared_ptr<AMapObject> VillageRedHouse1 = GetCurMap()->AddMapObject(1, 1, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse1, { 1,1 }, EMapObject::VillageRedHouse, VillageRedHouse1->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock1 = GetCurMap()->AddMapObject(1, 2, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock1, { 1,2 }, EMapObject::VillageMoveBlock, VillageMoveBlock1->GetPossessItem());

	std::shared_ptr<AMapObject> VillageRedHouse3 = GetCurMap()->AddMapObject(1, 3, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse3, { 1,3 }, EMapObject::VillageRedHouse, VillageRedHouse3->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock2 = GetCurMap()->AddMapObject(1, 4, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock2, { 1,4 }, EMapObject::VillageMoveBlock, VillageMoveBlock2->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree1 = GetCurMap()->AddMapObject(1, 5, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree1, { 1,5 }, EMapObject::VillageTree, VillageTree1->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock3 = GetCurMap()->AddMapObject(1, 6, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock3, { 1,6 }, EMapObject::VillageMoveBlock, VillageMoveBlock3->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree2 = GetCurMap()->AddMapObject(1, 9, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree2, { 1,9 }, EMapObject::VillageTree, VillageTree2->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock6 = GetCurMap()->AddMapObject(1, 10, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock6, { 1,10 }, EMapObject::VillageBlock1, VillageBlock6->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock7 = GetCurMap()->AddMapObject(1, 11, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock7, { 1,11 }, EMapObject::VillageBlock2, VillageBlock7->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock8 = GetCurMap()->AddMapObject(2, 2, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock8, { 2,2 }, EMapObject::VillageBlock2, VillageBlock8->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock9 = GetCurMap()->AddMapObject(2, 3, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock9, { 2,3 }, EMapObject::VillageBlock1, VillageBlock9->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock10 = GetCurMap()->AddMapObject(2, 4, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock10, { 2,4 }, EMapObject::VillageBlock2, VillageBlock10->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush3 = GetCurMap()->AddMapObject(2, 5, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush3, { 2,5 }, EMapObject::TownBush, TownBush3->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock4 = GetCurMap()->AddMapObject(2, 7, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock4, { 2,7 }, EMapObject::VillageMoveBlock, VillageMoveBlock4->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock5 = GetCurMap()->AddMapObject(2, 8, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock5, { 2,8 }, EMapObject::VillageMoveBlock, VillageMoveBlock5->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush4 = GetCurMap()->AddMapObject(2, 9, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush4, { 2,9 }, EMapObject::TownBush, TownBush4->GetPossessItem());

	std::shared_ptr<AMapObject> VillageYellowHouse4 = GetCurMap()->AddMapObject(2, 10, EMapObject::VillageYellowHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse4, { 2,10 }, EMapObject::VillageYellowHouse, VillageYellowHouse4->GetPossessItem());


	std::shared_ptr<AMapObject> VillageMoveBlock6 = GetCurMap()->AddMapObject(2, 11, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock6, { 2,11 }, EMapObject::VillageMoveBlock, VillageMoveBlock6->GetPossessItem());


	std::shared_ptr<AMapObject> VillageYellowHouse5 = GetCurMap()->AddMapObject(2, 12, EMapObject::VillageYellowHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse5, { 2,12 }, EMapObject::VillageYellowHouse, VillageYellowHouse5->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock7 = GetCurMap()->AddMapObject(2, 13, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock7, { 2,13 }, EMapObject::VillageMoveBlock, VillageMoveBlock7->GetPossessItem());

	std::shared_ptr<AMapObject> VillageYellowHouse6 = GetCurMap()->AddMapObject(2, 14, EMapObject::VillageYellowHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse6, { 2,14 }, EMapObject::VillageYellowHouse, VillageYellowHouse6->GetPossessItem());

	//

	std::shared_ptr<AMapObject> VillageMoveBlock8 = GetCurMap()->AddMapObject(3, 0, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock8, { 3,0 }, EMapObject::VillageMoveBlock, VillageMoveBlock8->GetPossessItem());

	std::shared_ptr<AMapObject> VillageRedHouse4 = GetCurMap()->AddMapObject(3, 1, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse4, { 3,1 }, EMapObject::VillageRedHouse, VillageRedHouse4->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock9 = GetCurMap()->AddMapObject(3, 2, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock9, { 3,2 }, EMapObject::VillageMoveBlock, VillageMoveBlock9->GetPossessItem());


	std::shared_ptr<AMapObject> VillageRedHouse5 = GetCurMap()->AddMapObject(3, 3, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse5, { 3,3 }, EMapObject::VillageRedHouse, VillageRedHouse5->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock10 = GetCurMap()->AddMapObject(3, 4, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock10, { 3,4 }, EMapObject::VillageMoveBlock, VillageMoveBlock10->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree3 = GetCurMap()->AddMapObject(3, 5, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree3, { 3,5 }, EMapObject::VillageTree, VillageTree3->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock11 = GetCurMap()->AddMapObject(3, 6, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock11, { 3,6 }, EMapObject::VillageMoveBlock, VillageMoveBlock11->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree4 = GetCurMap()->AddMapObject(3, 9, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree4, { 3,9 }, EMapObject::VillageTree, VillageTree4->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock11 = GetCurMap()->AddMapObject(3, 10, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock11, { 3,10 }, EMapObject::VillageBlock2, VillageBlock11->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock12 = GetCurMap()->AddMapObject(3, 11, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock12, { 3,11 }, EMapObject::VillageBlock1, VillageBlock12->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock13 = GetCurMap()->AddMapObject(3, 12, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock13, { 3,12 }, EMapObject::VillageBlock2, VillageBlock13->GetPossessItem());


	std::shared_ptr<AMapObject> VillageBlock14 = GetCurMap()->AddMapObject(3, 13, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock14, { 3,13 }, EMapObject::VillageBlock1, VillageBlock14->GetPossessItem());

	std::shared_ptr<AMapObject>  VillageBlock15 = GetCurMap()->AddMapObject(3, 14, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock15, { 3,14 }, EMapObject::VillageBlock2, VillageBlock15->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock16 = GetCurMap()->AddMapObject(4, 0, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock16, { 4,0 }, EMapObject::VillageBlock1, VillageBlock16->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock17 = GetCurMap()->AddMapObject(4, 1, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock17, { 4,1 }, EMapObject::VillageBlock2, VillageBlock17->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock18 = GetCurMap()->AddMapObject(4, 2, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock18, { 4,2 }, EMapObject::VillageBlock1, VillageBlock18->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock19 = GetCurMap()->AddMapObject(4, 3, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock19, { 4,3 }, EMapObject::VillageBlock2, VillageBlock19->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock20 = GetCurMap()->AddMapObject(4, 4, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock20, { 4,4 }, EMapObject::VillageBlock1, VillageBlock20->GetPossessItem());


	std::shared_ptr<AMapObject> TownBush5 = GetCurMap()->AddMapObject(4, 5, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush5, { 4,5 }, EMapObject::TownBush, TownBush5->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock12 = GetCurMap()->AddMapObject(4, 8, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock12, { 4,8 }, EMapObject::VillageMoveBlock, VillageMoveBlock12->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush6 = GetCurMap()->AddMapObject(4, 9, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush6, { 4,9 }, EMapObject::TownBush, TownBush6->GetPossessItem());

	std::shared_ptr<AMapObject> VillageYellowHouse7 = GetCurMap()->AddMapObject(4, 10, EMapObject::VillageYellowHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse7, { 4,10 }, EMapObject::VillageYellowHouse, VillageYellowHouse7->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock13 = GetCurMap()->AddMapObject(4, 11, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock13, { 4,11 }, EMapObject::VillageMoveBlock, VillageMoveBlock13->GetPossessItem());

	std::shared_ptr<AMapObject> VillageYellowHouse8 = GetCurMap()->AddMapObject(4, 12, EMapObject::VillageYellowHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse8, { 4,12 }, EMapObject::VillageYellowHouse, VillageYellowHouse8->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock14 = GetCurMap()->AddMapObject(4, 13, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock14, { 4,13 }, EMapObject::VillageMoveBlock, VillageMoveBlock14->GetPossessItem());

	std::shared_ptr<AMapObject> VillageYellowHouse9 = GetCurMap()->AddMapObject(4, 14, EMapObject::VillageYellowHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageYellowHouse9, { 4,14 }, EMapObject::VillageYellowHouse, VillageYellowHouse9->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock21 = GetCurMap()->AddMapObject(5, 0, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock21, { 5,0 }, EMapObject::VillageBlock2, VillageBlock21->GetPossessItem());

	std::shared_ptr<AMapObject> VillageRedHouse6 = GetCurMap()->AddMapObject(5, 1, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse6, { 5,1 }, EMapObject::VillageRedHouse, VillageRedHouse6->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock22 = GetCurMap()->AddMapObject(5, 2, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock22, { 5,2 }, EMapObject::VillageBlock2, VillageBlock22->GetPossessItem());

	std::shared_ptr<AMapObject> VillageRedHouse7 = GetCurMap()->AddMapObject(5, 3, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse7, { 5,3 }, EMapObject::VillageRedHouse, VillageRedHouse7->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock23 = GetCurMap()->AddMapObject(5, 4, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock23, { 5,4 }, EMapObject::VillageBlock2, VillageBlock23->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree5 = GetCurMap()->AddMapObject(5, 5, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree5, { 5,5 }, EMapObject::VillageTree, VillageTree5->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock15 = GetCurMap()->AddMapObject(5, 6, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock15, { 5,6 }, EMapObject::VillageMoveBlock, VillageMoveBlock15->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock16 = GetCurMap()->AddMapObject(5, 7, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock16, { 5,7 }, EMapObject::VillageMoveBlock, VillageMoveBlock16->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock24 = GetCurMap()->AddMapObject(5, 10, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock24, { 5,10 }, EMapObject::VillageBlock1, VillageBlock24->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock25 = GetCurMap()->AddMapObject(5, 11, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock25, { 5,11 }, EMapObject::VillageBlock2, VillageBlock25->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock26 = GetCurMap()->AddMapObject(5, 12, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock26, { 5,12 }, EMapObject::VillageBlock1, VillageBlock26->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock27 = GetCurMap()->AddMapObject(5, 13, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock27, { 5,13 }, EMapObject::VillageBlock2, VillageBlock27->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock28 = GetCurMap()->AddMapObject(5, 14, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock28, { 5,14 }, EMapObject::VillageBlock1, VillageBlock28->GetPossessItem());


	std::shared_ptr<AMapObject> VillageTree6 = GetCurMap()->AddMapObject(6, 0, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree6, { 6,0 }, EMapObject::VillageTree, VillageTree6->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush7 = GetCurMap()->AddMapObject(6, 1, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush7, { 6,1 }, EMapObject::TownBush, TownBush7->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree7 = GetCurMap()->AddMapObject(6, 2, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree7, { 6,2 }, EMapObject::VillageTree, VillageTree7->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush8 = GetCurMap()->AddMapObject(6, 3, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush8, { 6,3 }, EMapObject::TownBush, TownBush8->GetPossessItem());


	std::shared_ptr<AMapObject> VillageTree8 = GetCurMap()->AddMapObject(6, 4, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree8, { 6,4 }, EMapObject::VillageTree, VillageTree8->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush9 = GetCurMap()->AddMapObject(6, 5, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush9, { 6,5 }, EMapObject::TownBush, TownBush9->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock17 = GetCurMap()->AddMapObject(6, 8, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock17, { 6,8 }, EMapObject::VillageMoveBlock, VillageMoveBlock17->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush10 = GetCurMap()->AddMapObject(6, 9, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush10, { 6,9 }, EMapObject::TownBush, TownBush10->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree9 = GetCurMap()->AddMapObject(6, 10, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree9, { 6,10 }, EMapObject::VillageTree, VillageTree9->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush11 = GetCurMap()->AddMapObject(6, 11, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush11, { 6,11 }, EMapObject::TownBush, TownBush11->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree10 = GetCurMap()->AddMapObject(6, 12, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree10, { 6,12 }, EMapObject::VillageTree, VillageTree10->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush12 = GetCurMap()->AddMapObject(6, 13, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush12, { 6,13 }, EMapObject::TownBush, TownBush12->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree11 = GetCurMap()->AddMapObject(6, 14, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree11, { 6,14 }, EMapObject::VillageTree, VillageTree11->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock29 = GetCurMap()->AddMapObject(7, 0, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock29, { 7,0 }, EMapObject::VillageBlock1, VillageBlock29->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock30 = GetCurMap()->AddMapObject(7, 1, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock30, { 7,1 }, EMapObject::VillageBlock2, VillageBlock30->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock31 = GetCurMap()->AddMapObject(7, 2, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock31, { 7,2 }, EMapObject::VillageBlock1, VillageBlock31->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock32 = GetCurMap()->AddMapObject(7, 3, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock32, { 7,3 }, EMapObject::VillageBlock2, VillageBlock32->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock33 = GetCurMap()->AddMapObject(7, 4, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock33, { 7,4 }, EMapObject::VillageBlock1, VillageBlock33->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock18 = GetCurMap()->AddMapObject(7, 6, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock18, { 7,6 }, EMapObject::VillageMoveBlock, VillageMoveBlock18->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree12 = GetCurMap()->AddMapObject(7, 9, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree12, { 7,9 }, EMapObject::VillageTree, VillageTree12->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock34 = GetCurMap()->AddMapObject(7, 10, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock34, { 7,10 }, EMapObject::VillageBlock1, VillageBlock34->GetPossessItem());

	std::shared_ptr<AMapObject> VillageRedHouse8 = GetCurMap()->AddMapObject(7, 11, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse8, { 7,11 }, EMapObject::VillageRedHouse, VillageRedHouse8->GetPossessItem());


	std::shared_ptr<AMapObject> VillageBlock35 = GetCurMap()->AddMapObject(7, 12, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock35, { 7,12 }, EMapObject::VillageBlock1, VillageBlock35->GetPossessItem());

	std::shared_ptr<AMapObject> VillageRedHouse9 = GetCurMap()->AddMapObject(7, 13, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse9, { 7,13 }, EMapObject::VillageRedHouse, VillageRedHouse9->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock36 = GetCurMap()->AddMapObject(7, 14, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock36, { 7,14 }, EMapObject::VillageBlock1, VillageBlock36->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlueHouse1 = GetCurMap()->AddMapObject(8, 0, EMapObject::VillageBlueHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse1, { 8,0 }, EMapObject::VillageBlueHouse, VillageBlueHouse1->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock19 = GetCurMap()->AddMapObject(8, 1, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock19, { 8,1 }, EMapObject::VillageMoveBlock, VillageMoveBlock19->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlueHouse2 = GetCurMap()->AddMapObject(8, 2, EMapObject::VillageBlueHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse2, { 8,2 }, EMapObject::VillageBlueHouse, VillageBlueHouse2->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock20 = GetCurMap()->AddMapObject(8, 3, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock20, { 8,3 }, EMapObject::VillageMoveBlock, VillageMoveBlock20->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlueHouse3 = GetCurMap()->AddMapObject(8, 4, EMapObject::VillageBlueHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse3, { 8,4 }, EMapObject::VillageBlueHouse, VillageBlueHouse3->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush13 = GetCurMap()->AddMapObject(8, 5, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush13, { 8,5 }, EMapObject::TownBush, TownBush13->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock21 = GetCurMap()->AddMapObject(8, 7, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock21, { 8,7 }, EMapObject::VillageMoveBlock, VillageMoveBlock21->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock22 = GetCurMap()->AddMapObject(8, 8, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock22, { 8,8 }, EMapObject::VillageMoveBlock, VillageMoveBlock22->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush14 = GetCurMap()->AddMapObject(8, 9, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush14, { 8,9 }, EMapObject::TownBush, TownBush14->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock37 = GetCurMap()->AddMapObject(8, 10, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock37, { 8,10 }, EMapObject::VillageBlock2, VillageBlock37->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock38 = GetCurMap()->AddMapObject(8, 11, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock38, { 8,11 }, EMapObject::VillageBlock1, VillageBlock38->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock39 = GetCurMap()->AddMapObject(8, 12, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock39, { 8,12 }, EMapObject::VillageBlock2, VillageBlock39->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock40 = GetCurMap()->AddMapObject(8, 13, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock40, { 8,13 }, EMapObject::VillageBlock1, VillageBlock40->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock41 = GetCurMap()->AddMapObject(8, 14, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock41, { 8,14 }, EMapObject::VillageBlock2, VillageBlock41->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock42 = GetCurMap()->AddMapObject(9, 0, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock42, { 9,0 }, EMapObject::VillageBlock2, VillageBlock42->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock43 = GetCurMap()->AddMapObject(9, 1, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock43, { 9,1 }, EMapObject::VillageBlock1, VillageBlock43->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock44 = GetCurMap()->AddMapObject(9, 2, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock44, { 9,2 }, EMapObject::VillageBlock2, VillageBlock44->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock45 = GetCurMap()->AddMapObject(9, 3, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock45, { 9,3 }, EMapObject::VillageBlock1, VillageBlock45->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock46 = GetCurMap()->AddMapObject(9, 4, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock46, { 9,4 }, EMapObject::VillageBlock2, VillageBlock46->GetPossessItem());


	std::shared_ptr<AMapObject> VillageTree13 = GetCurMap()->AddMapObject(9, 5, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree13, { 9,5 }, EMapObject::VillageTree, VillageTree13->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock23 = GetCurMap()->AddMapObject(9, 6, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock23, { 9,6 }, EMapObject::VillageMoveBlock, VillageMoveBlock23->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree14 = GetCurMap()->AddMapObject(9, 9, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree14, { 9,9 }, EMapObject::VillageTree, VillageTree14->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock24 = GetCurMap()->AddMapObject(9, 10, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock24, { 9,10 }, EMapObject::VillageMoveBlock, VillageMoveBlock24->GetPossessItem());

	std::shared_ptr<AMapObject> VillageRedHouse10 = GetCurMap()->AddMapObject(9, 11, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse10, { 9,11 }, EMapObject::VillageRedHouse, VillageRedHouse10->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock25 = GetCurMap()->AddMapObject(9, 12, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock25, { 9,12 }, EMapObject::VillageMoveBlock, VillageMoveBlock25->GetPossessItem());

	std::shared_ptr<AMapObject> VillageRedHouse11 = GetCurMap()->AddMapObject(9, 13, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse11, { 9,13 }, EMapObject::VillageRedHouse, VillageRedHouse11->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock26 = GetCurMap()->AddMapObject(9, 14, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock26, { 9,14 }, EMapObject::VillageMoveBlock, VillageMoveBlock26->GetPossessItem());


	std::shared_ptr<AMapObject> VillageBlueHouse4 = GetCurMap()->AddMapObject(10, 0, EMapObject::VillageBlueHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse4, { 10,0 }, EMapObject::VillageBlueHouse, VillageBlueHouse4->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlueHouse5 = GetCurMap()->AddMapObject(10, 2, EMapObject::VillageBlueHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse5, { 10,2 }, EMapObject::VillageBlueHouse, VillageBlueHouse5->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock27 = GetCurMap()->AddMapObject(10, 3, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock27, { 10,3 }, EMapObject::VillageMoveBlock, VillageMoveBlock27->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlueHouse6 = GetCurMap()->AddMapObject(10, 4, EMapObject::VillageBlueHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse6, { 10,4 }, EMapObject::VillageBlueHouse, VillageBlueHouse6->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush15 = GetCurMap()->AddMapObject(10, 5, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush15, { 10,5 }, EMapObject::TownBush, TownBush15->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock28 = GetCurMap()->AddMapObject(10, 8, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock28, { 10,8 }, EMapObject::VillageMoveBlock, VillageMoveBlock28->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush16 = GetCurMap()->AddMapObject(10, 9, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush16, { 10,9 }, EMapObject::TownBush, TownBush16->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock48 = GetCurMap()->AddMapObject(10, 10, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock48, { 10,10 }, EMapObject::VillageBlock1, VillageBlock48->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock49 = GetCurMap()->AddMapObject(10, 11, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock49, { 10,11 }, EMapObject::VillageBlock2, VillageBlock49->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock50 = GetCurMap()->AddMapObject(10, 12, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock50, { 10,12 }, EMapObject::VillageBlock1, VillageBlock50->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock51 = GetCurMap()->AddMapObject(10, 13, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock51, { 10,13 }, EMapObject::VillageBlock2, VillageBlock51->GetPossessItem());


	std::shared_ptr<AMapObject> VillageBlock52 = GetCurMap()->AddMapObject(11, 2, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock52, { 11,2 }, EMapObject::VillageBlock1, VillageBlock52->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock53 = GetCurMap()->AddMapObject(11, 3, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock53, { 11,3 }, EMapObject::VillageBlock2, VillageBlock53->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock54 = GetCurMap()->AddMapObject(11, 4, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock54, { 11,4 }, EMapObject::VillageBlock1, VillageBlock54->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree15 = GetCurMap()->AddMapObject(11, 5, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree15, { 11,5 }, EMapObject::VillageTree, VillageTree15->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock29 = GetCurMap()->AddMapObject(11, 6, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock29, { 11,6 }, EMapObject::VillageMoveBlock, VillageMoveBlock29->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock30 = GetCurMap()->AddMapObject(11, 7, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock30, { 11,7 }, EMapObject::VillageMoveBlock, VillageMoveBlock30->GetPossessItem());

	std::shared_ptr<AMapObject> VillageTree16 = GetCurMap()->AddMapObject(11, 9, EMapObject::VillageTree);
	USendPacketManager::SendMapObjectSpawnPacket(VillageTree16, { 11,9 }, EMapObject::VillageTree, VillageTree16->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock31 = GetCurMap()->AddMapObject(11, 10, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock31, { 11,10 }, EMapObject::VillageMoveBlock, VillageMoveBlock31->GetPossessItem());

	std::shared_ptr<AMapObject> VillageRedHouse12 = GetCurMap()->AddMapObject(11, 11, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse12, { 11,11 }, EMapObject::VillageRedHouse, VillageRedHouse12->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock32 = GetCurMap()->AddMapObject(11, 12, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock32, { 11,12 }, EMapObject::VillageMoveBlock, VillageMoveBlock32->GetPossessItem());


	std::shared_ptr<AMapObject> VillageRedHouse13 = GetCurMap()->AddMapObject(11, 13, EMapObject::VillageRedHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageRedHouse13, { 11,13 }, EMapObject::VillageRedHouse, VillageRedHouse13->GetPossessItem());


	std::shared_ptr<AMapObject> VillageBlueHouse7 = GetCurMap()->AddMapObject(12, 0, EMapObject::VillageBlueHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse7, { 12,0 }, EMapObject::VillageBlueHouse, VillageBlueHouse7->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlueHouse8 = GetCurMap()->AddMapObject(12, 2, EMapObject::VillageBlueHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse8, { 12,2 }, EMapObject::VillageBlueHouse, VillageBlueHouse8->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock55 = GetCurMap()->AddMapObject(12, 3, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock55, { 12,3 }, EMapObject::VillageBlock1, VillageBlock55->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlueHouse9 = GetCurMap()->AddMapObject(12, 4, EMapObject::VillageBlueHouse);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlueHouse9, { 12,4 }, EMapObject::VillageBlueHouse, VillageBlueHouse9->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush17 = GetCurMap()->AddMapObject(12, 5, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush17, { 12,5 }, EMapObject::TownBush, TownBush17->GetPossessItem());

	std::shared_ptr<AMapObject> VillageMoveBlock33 = GetCurMap()->AddMapObject(12, 8, EMapObject::VillageMoveBlock);
	USendPacketManager::SendMapObjectSpawnPacket(VillageMoveBlock33, { 12,8 }, EMapObject::VillageMoveBlock, VillageMoveBlock33->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush18 = GetCurMap()->AddMapObject(12, 9, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush18, { 12,9 }, EMapObject::TownBush, TownBush18->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock56 = GetCurMap()->AddMapObject(12, 10, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock56, { 12,10 }, EMapObject::VillageBlock2, VillageBlock56->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock57 = GetCurMap()->AddMapObject(12, 11, EMapObject::VillageBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock57, { 12,11 }, EMapObject::VillageBlock1, VillageBlock57->GetPossessItem());

	std::shared_ptr<AMapObject> VillageBlock58 = GetCurMap()->AddMapObject(12, 12, EMapObject::VillageBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(VillageBlock58, { 12,12 }, EMapObject::VillageBlock2, VillageBlock58->GetPossessItem());
}

void AMainGameMode::CreateCampBlocks()
{
	std::shared_ptr<AMapObject> CampBlock1 = GetCurMap()->AddMapObject(0, 0, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock1, { 0,0 }, EMapObject::CampBlock2, CampBlock1->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock2 = GetCurMap()->AddMapObject(0, 2, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock2, { 0,2 }, EMapObject::CampBlock1, CampBlock2->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock3 = GetCurMap()->AddMapObject(0, 4, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock3, { 0,4 }, EMapObject::CampBlock1, CampBlock3->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush1 = GetCurMap()->AddMapObject(0, 6, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush1, { 0,6 }, EMapObject::TownBush, TownBush1->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush2 = GetCurMap()->AddMapObject(0, 8, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush2, { 0,8 }, EMapObject::TownBush, TownBush2->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock4 = GetCurMap()->AddMapObject(0, 10, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock4, { 0,10 }, EMapObject::CampBlock2, CampBlock4->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock5 = GetCurMap()->AddMapObject(0, 12, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock5, { 0,12 }, EMapObject::CampBlock2, CampBlock5->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock6 = GetCurMap()->AddMapObject(0, 14, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock6, { 0,14 }, EMapObject::CampBlock1, CampBlock6->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock1 = GetCurMap()->AddMapObject(1, 0, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock1, { 1,0 }, EMapObject::CampMoveBlock1, CampMoveBlock1->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock7 = GetCurMap()->AddMapObject(1, 4, EMapObject::CampBlock3);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock7, { 1,4 }, EMapObject::CampBlock3, CampBlock7->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock8 = GetCurMap()->AddMapObject(1, 5, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock8, { 1,5 }, EMapObject::CampBlock1, CampBlock8->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush3 = GetCurMap()->AddMapObject(1, 6, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush3, { 1,6 }, EMapObject::TownBush, TownBush3->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush4 = GetCurMap()->AddMapObject(1, 8, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush4, { 1,8 }, EMapObject::TownBush, TownBush4->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock9 = GetCurMap()->AddMapObject(1, 9, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock9, { 1,9 }, EMapObject::CampBlock2, CampBlock9->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock10 = GetCurMap()->AddMapObject(1, 10, EMapObject::CampBlock3);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock10, { 1,10 }, EMapObject::CampBlock3, CampBlock10->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock2 = GetCurMap()->AddMapObject(1, 14, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock2, { 1,14 }, EMapObject::CampMoveBlock1, CampMoveBlock2->GetPossessItem());


	std::shared_ptr<AMapObject> CampBlock11 = GetCurMap()->AddMapObject(2, 0, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock11, { 2,0 }, EMapObject::CampBlock2, CampBlock11->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock12 = GetCurMap()->AddMapObject(2, 2, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock12, { 2,2 }, EMapObject::CampBlock1, CampBlock12->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock13 = GetCurMap()->AddMapObject(2, 3, EMapObject::CampBlock3);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock13, { 2,3 }, EMapObject::CampBlock3, CampBlock13->GetPossessItem());

	std::shared_ptr<AMapObject> CampHPBlock1 = GetCurMap()->AddMapObject(2, 5, EMapObject::CampHPBlock);
	USendPacketManager::SendMapObjectSpawnPacket(CampHPBlock1, { 2,5 }, EMapObject::CampHPBlock, CampHPBlock1->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock14 = GetCurMap()->AddMapObject(2, 6, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock14, { 2,6 }, EMapObject::CampBlock1, CampBlock14->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock15 = GetCurMap()->AddMapObject(2, 8, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock15, { 2,8 }, EMapObject::CampBlock2, CampBlock15->GetPossessItem());

	std::shared_ptr<AMapObject> CampHPBlock2 = GetCurMap()->AddMapObject(2, 9, EMapObject::CampHPBlock);
	USendPacketManager::SendMapObjectSpawnPacket(CampHPBlock2, { 2,9 }, EMapObject::CampHPBlock, CampHPBlock2->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock16 = GetCurMap()->AddMapObject(2, 11, EMapObject::CampBlock3);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock16, { 2,11 }, EMapObject::CampBlock3, CampBlock16->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock17 = GetCurMap()->AddMapObject(2, 12, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock17, { 2,12 }, EMapObject::CampBlock2, CampBlock17->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock18 = GetCurMap()->AddMapObject(2, 14, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock18, { 2,14 }, EMapObject::CampBlock1, CampBlock18->GetPossessItem());



	std::shared_ptr<AMapObject> CampBlock19 = GetCurMap()->AddMapObject(3, 0, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock19, { 3,0 }, EMapObject::CampBlock1, CampBlock19->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock20 = GetCurMap()->AddMapObject(3, 1, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock20, { 3,1 }, EMapObject::CampBlock1, CampBlock20->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock3 = GetCurMap()->AddMapObject(3, 4, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock3, { 3,4 }, EMapObject::CampMoveBlock1, CampMoveBlock3->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock21 = GetCurMap()->AddMapObject(3, 5, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock21, { 3,5 }, EMapObject::CampBlock1, CampBlock21->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock221 = GetCurMap()->AddMapObject(3, 5, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock221, { 3,5 }, EMapObject::CampBlock1, CampBlock221->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush5 = GetCurMap()->AddMapObject(3, 6, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush5, { 3,6 }, EMapObject::TownBush, TownBush5->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush6 = GetCurMap()->AddMapObject(3, 8, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush6, { 3,8 }, EMapObject::TownBush, TownBush6->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock22 = GetCurMap()->AddMapObject(3, 9, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock22, { 3,9 }, EMapObject::CampBlock2, CampBlock22->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock4 = GetCurMap()->AddMapObject(3, 10, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock4, { 3,10 }, EMapObject::CampMoveBlock1, CampMoveBlock4->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock23 = GetCurMap()->AddMapObject(3, 13, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock23, { 3,13 }, EMapObject::CampBlock2, CampBlock23->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock24 = GetCurMap()->AddMapObject(3, 14, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock24, { 3,14 }, EMapObject::CampBlock2, CampBlock24->GetPossessItem());



	std::shared_ptr<AMapObject> CampMoveBlock5 = GetCurMap()->AddMapObject(4, 0, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock5, { 4,0 }, EMapObject::CampMoveBlock1, CampMoveBlock5->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush7 = GetCurMap()->AddMapObject(4, 1, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush7, { 4,1 }, EMapObject::TownBush, TownBush7->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush8 = GetCurMap()->AddMapObject(4, 2, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush8, { 4,2 }, EMapObject::TownBush, TownBush8->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock25 = GetCurMap()->AddMapObject(4, 3, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock25, { 4,3 }, EMapObject::CampBlock1, CampBlock25->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock6 = GetCurMap()->AddMapObject(4, 5, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock6, { 4,5 }, EMapObject::CampMoveBlock1, CampMoveBlock6->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock26 = GetCurMap()->AddMapObject(4, 6, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock26, { 4,6 }, EMapObject::CampBlock1, CampBlock26->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock27 = GetCurMap()->AddMapObject(4, 8, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock27, { 4,8 }, EMapObject::CampBlock2, CampBlock27->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock7 = GetCurMap()->AddMapObject(4, 9, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock7, { 4,9 }, EMapObject::CampMoveBlock1, CampMoveBlock7->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush9 = GetCurMap()->AddMapObject(4, 10, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush9, { 4,10 }, EMapObject::TownBush, TownBush9->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock28 = GetCurMap()->AddMapObject(4, 11, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock28, { 4,11 }, EMapObject::CampBlock2, CampBlock28->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush10 = GetCurMap()->AddMapObject(4, 12, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush10, { 4,12 }, EMapObject::TownBush, TownBush10->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock8 = GetCurMap()->AddMapObject(4, 14, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock8, { 4,14 }, EMapObject::CampMoveBlock1, CampMoveBlock8->GetPossessItem());



	std::shared_ptr<AMapObject> CampMoveBlock9 = GetCurMap()->AddMapObject(5, 1, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock9, { 5,1 }, EMapObject::CampMoveBlock1, CampMoveBlock9->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock29 = GetCurMap()->AddMapObject(5, 5, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock29, { 5,5 }, EMapObject::CampBlock1, CampBlock29->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock10 = GetCurMap()->AddMapObject(5, 6, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock10, { 5,6 }, EMapObject::CampMoveBlock1, CampMoveBlock10->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock11 = GetCurMap()->AddMapObject(5, 8, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock11, { 5,8 }, EMapObject::CampMoveBlock1, CampMoveBlock11->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock30 = GetCurMap()->AddMapObject(5, 9, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock30, { 5,9 }, EMapObject::CampBlock2, CampBlock30->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush11 = GetCurMap()->AddMapObject(5, 10, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush11, { 5,10 }, EMapObject::TownBush, TownBush11->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock12 = GetCurMap()->AddMapObject(5, 6, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock12, { 5,13 }, EMapObject::CampMoveBlock1, CampMoveBlock12->GetPossessItem());


	std::shared_ptr<AMapObject> CampBlock31 = GetCurMap()->AddMapObject(6, 0, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock31, { 6,0 }, EMapObject::CampBlock1, CampBlock31->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock32 = GetCurMap()->AddMapObject(6, 1, EMapObject::CampBlock3);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock32, { 6, 1 }, EMapObject::CampBlock3, CampBlock32->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush12 = GetCurMap()->AddMapObject(6, 2, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush12, { 6, 2 }, EMapObject::TownBush, TownBush12->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock33 = GetCurMap()->AddMapObject(6, 3, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock33, { 6, 3 }, EMapObject::CampBlock1, CampBlock33->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush13 = GetCurMap()->AddMapObject(6, 4, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush13, { 6, 4 }, EMapObject::TownBush, TownBush13->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock13 = GetCurMap()->AddMapObject(6, 5, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock13, { 6, 5 }, EMapObject::CampMoveBlock1, CampMoveBlock13->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock34 = GetCurMap()->AddMapObject(6, 6, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock34, { 6, 6 }, EMapObject::CampBlock1, CampBlock34->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock35 = GetCurMap()->AddMapObject(6, 8, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock35, { 6, 8 }, EMapObject::CampBlock2, CampBlock35->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock14 = GetCurMap()->AddMapObject(6, 9, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock14, { 6, 9 }, EMapObject::CampMoveBlock1, CampMoveBlock14->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush14 = GetCurMap()->AddMapObject(6, 10, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush14, { 6, 10 }, EMapObject::TownBush, TownBush14->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock36 = GetCurMap()->AddMapObject(6, 11, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock36, { 6, 11 }, EMapObject::CampBlock2, CampBlock36->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush15 = GetCurMap()->AddMapObject(6, 12, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush15, { 6, 12 }, EMapObject::TownBush, TownBush15->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock37 = GetCurMap()->AddMapObject(6, 13, EMapObject::CampBlock3);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock37, { 6, 13 }, EMapObject::CampBlock3, CampBlock37->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock38 = GetCurMap()->AddMapObject(6, 14, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock38, { 6, 14 }, EMapObject::CampBlock2, CampBlock38->GetPossessItem());




	std::shared_ptr<AMapObject> CampBlock39 = GetCurMap()->AddMapObject(7, 0, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock39, { 7, 0 }, EMapObject::CampBlock1, CampBlock39->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock15 = GetCurMap()->AddMapObject(7, 4, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock15, { 7, 4 }, EMapObject::CampMoveBlock1, CampMoveBlock15->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock40 = GetCurMap()->AddMapObject(7, 5, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock40, { 7, 5 }, EMapObject::CampBlock1, CampBlock40->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush16 = GetCurMap()->AddMapObject(7, 6, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush16, { 7, 6 }, EMapObject::TownBush, TownBush16->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush17 = GetCurMap()->AddMapObject(7, 8, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush17, { 7, 8 }, EMapObject::TownBush, TownBush17->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock41 = GetCurMap()->AddMapObject(7, 9, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock41, { 7, 9 }, EMapObject::CampBlock2, CampBlock41->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock16 = GetCurMap()->AddMapObject(7, 10, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock16, { 7, 10 }, EMapObject::CampMoveBlock1, CampMoveBlock16->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock42 = GetCurMap()->AddMapObject(7, 14, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock42, { 7, 14 }, EMapObject::CampBlock2, CampBlock42->GetPossessItem());





	std::shared_ptr<AMapObject> CampBlock43 = GetCurMap()->AddMapObject(8, 1, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock43, { 8, 1 }, EMapObject::CampBlock1, CampBlock43->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush18 = GetCurMap()->AddMapObject(8, 2, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush18, { 8, 2 }, EMapObject::TownBush, TownBush18->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush19 = GetCurMap()->AddMapObject(8, 3, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush19, { 8, 3 }, EMapObject::TownBush, TownBush19->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock44 = GetCurMap()->AddMapObject(8, 5, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock44, { 8, 5 }, EMapObject::CampBlock1, CampBlock44->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush20 = GetCurMap()->AddMapObject(8, 6, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush20, { 8, 6 }, EMapObject::TownBush, TownBush20->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush21 = GetCurMap()->AddMapObject(8, 8, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush21, { 8, 8 }, EMapObject::TownBush, TownBush21->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock45 = GetCurMap()->AddMapObject(8, 9, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock45, { 8, 9 }, EMapObject::CampBlock2, CampBlock45->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush22 = GetCurMap()->AddMapObject(8, 11, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush22, { 8, 11 }, EMapObject::TownBush, TownBush22->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush23 = GetCurMap()->AddMapObject(8, 12, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush23, { 8, 12 }, EMapObject::TownBush, TownBush23->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock46 = GetCurMap()->AddMapObject(8, 13, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock46, { 8, 13 }, EMapObject::CampBlock2, CampBlock46->GetPossessItem());



	std::shared_ptr<AMapObject> CampMoveBlock17 = GetCurMap()->AddMapObject(9, 0, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock17, { 9, 0 }, EMapObject::CampMoveBlock1, CampMoveBlock17->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock18 = GetCurMap()->AddMapObject(9, 1, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock18, { 9, 1 }, EMapObject::CampMoveBlock1, CampMoveBlock18->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock19 = GetCurMap()->AddMapObject(9, 2, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock19, { 9, 2 }, EMapObject::CampMoveBlock1, CampMoveBlock19->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock47 = GetCurMap()->AddMapObject(9, 3, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock47, { 9, 3 }, EMapObject::CampBlock1, CampBlock47->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock48 = GetCurMap()->AddMapObject(9, 5, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock48, { 9, 5 }, EMapObject::CampBlock1, CampBlock48->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush24 = GetCurMap()->AddMapObject(9, 6, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush24, { 9, 6 }, EMapObject::TownBush, TownBush24->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush25 = GetCurMap()->AddMapObject(9, 8, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush25, { 9, 8 }, EMapObject::TownBush, TownBush25->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock49 = GetCurMap()->AddMapObject(9, 9, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock49, { 9, 9 }, EMapObject::CampBlock2, CampBlock49->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock50 = GetCurMap()->AddMapObject(9, 11, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock50, { 9, 11 }, EMapObject::CampBlock2, CampBlock50->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock20 = GetCurMap()->AddMapObject(9, 12, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock20, { 9, 12 }, EMapObject::CampMoveBlock1, CampMoveBlock20->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock21 = GetCurMap()->AddMapObject(9, 13, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock21, { 9, 13 }, EMapObject::CampMoveBlock1, CampMoveBlock21->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock22 = GetCurMap()->AddMapObject(9, 14, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock22, { 9, 14 }, EMapObject::CampMoveBlock1, CampMoveBlock22->GetPossessItem());



	std::shared_ptr<AMapObject> CampBlock51 = GetCurMap()->AddMapObject(10, 0, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock51, { 10, 0 }, EMapObject::CampBlock1, CampBlock51->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock52 = GetCurMap()->AddMapObject(10, 1, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock52, { 10, 1 }, EMapObject::CampBlock1, CampBlock52->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock53 = GetCurMap()->AddMapObject(10, 2, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock53, { 10, 2 }, EMapObject::CampBlock1, CampBlock53->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock59 = GetCurMap()->AddMapObject(10, 3, EMapObject::CampBlock3);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock59, { 10, 3 }, EMapObject::CampBlock3, CampBlock59->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock54 = GetCurMap()->AddMapObject(10, 5, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock54, { 10, 5 }, EMapObject::CampBlock1, CampBlock54->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush26 = GetCurMap()->AddMapObject(10, 6, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush26, { 10, 6 }, EMapObject::TownBush, TownBush26->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush27 = GetCurMap()->AddMapObject(10, 8, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush27, { 10, 8 }, EMapObject::TownBush, TownBush27->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock55 = GetCurMap()->AddMapObject(10, 9, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock55, { 10, 9 }, EMapObject::CampBlock2, CampBlock55->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock60 = GetCurMap()->AddMapObject(10, 11, EMapObject::CampBlock3);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock60, { 10, 11 }, EMapObject::CampBlock3, CampBlock60->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock56 = GetCurMap()->AddMapObject(10, 12, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock56, { 10, 12 }, EMapObject::CampBlock2, CampBlock56->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock57 = GetCurMap()->AddMapObject(10, 13, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock57, { 10, 13 }, EMapObject::CampBlock2, CampBlock57->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock58 = GetCurMap()->AddMapObject(10, 14, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock58, { 10, 14 }, EMapObject::CampBlock2, CampBlock58->GetPossessItem());



	std::shared_ptr<AMapObject> CampMoveBlock23 = GetCurMap()->AddMapObject(11, 0, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock23, { 11, 0 }, EMapObject::CampMoveBlock1, CampMoveBlock23->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock61 = GetCurMap()->AddMapObject(11, 4, EMapObject::CampBlock3);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock61, { 11, 4 }, EMapObject::CampBlock3, CampBlock61->GetPossessItem());


	std::shared_ptr<AMapObject> CampHPBlock3 = GetCurMap()->AddMapObject(11, 5, EMapObject::CampHPBlock);
	USendPacketManager::SendMapObjectSpawnPacket(CampHPBlock3, { 11, 5 }, EMapObject::CampHPBlock, CampHPBlock3->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock62 = GetCurMap()->AddMapObject(11, 6, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock62, { 11, 6 }, EMapObject::CampBlock1, CampBlock62->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock63 = GetCurMap()->AddMapObject(11, 8, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock63, { 11, 8 }, EMapObject::CampBlock2, CampBlock63->GetPossessItem());

	std::shared_ptr<AMapObject> CampHPBlock4 = GetCurMap()->AddMapObject(11, 9, EMapObject::CampHPBlock);
	USendPacketManager::SendMapObjectSpawnPacket(CampHPBlock4, { 11 ,9 }, EMapObject::CampHPBlock, CampHPBlock4->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock64 = GetCurMap()->AddMapObject(11, 10, EMapObject::CampBlock3);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock64, { 11, 10 }, EMapObject::CampBlock3, CampBlock64->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock24 = GetCurMap()->AddMapObject(11, 14, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock24, { 11, 14 }, EMapObject::CampMoveBlock1, CampMoveBlock24->GetPossessItem());


	std::shared_ptr<AMapObject> CampBlock65 = GetCurMap()->AddMapObject(12, 2, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock65, { 12, 2 }, EMapObject::CampBlock1, CampBlock65->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock66 = GetCurMap()->AddMapObject(12, 3, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock66, { 12, 3 }, EMapObject::CampBlock1, CampBlock66->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock25 = GetCurMap()->AddMapObject(12, 4, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock25, { 12, 4 }, EMapObject::CampMoveBlock1, CampMoveBlock25->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock67 = GetCurMap()->AddMapObject(12, 5, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock67, { 12, 5 }, EMapObject::CampBlock1, CampBlock67->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush28 = GetCurMap()->AddMapObject(12, 6, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush28, { 12, 6 }, EMapObject::TownBush, TownBush28->GetPossessItem());

	std::shared_ptr<AMapObject> TownBush29 = GetCurMap()->AddMapObject(12, 8, EMapObject::TownBush);
	USendPacketManager::SendMapObjectSpawnPacket(TownBush29, { 12, 8 }, EMapObject::TownBush, TownBush29->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock69 = GetCurMap()->AddMapObject(12, 9, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock69, { 12, 9 }, EMapObject::CampBlock2, CampBlock69->GetPossessItem());

	std::shared_ptr<AMapObject> CampMoveBlock26 = GetCurMap()->AddMapObject(12, 10, EMapObject::CampMoveBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampMoveBlock26, { 12, 10 }, EMapObject::CampMoveBlock1, CampMoveBlock26->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock68 = GetCurMap()->AddMapObject(12, 11, EMapObject::CampBlock1);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock68, { 12, 11 }, EMapObject::CampBlock1, CampBlock68->GetPossessItem());

	std::shared_ptr<AMapObject> CampBlock70 = GetCurMap()->AddMapObject(12, 12, EMapObject::CampBlock2);
	USendPacketManager::SendMapObjectSpawnPacket(CampBlock70, { 12, 12 }, EMapObject::CampBlock2, CampBlock70->GetPossessItem());
}