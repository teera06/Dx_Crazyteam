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
#include "OtherBomb.h"
#include "CAGameMode.h"
#include "BaseMap.h"

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
	// TestThread.Start();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -400.0f));

	//Village = GetWorld()->SpawnActor<AVillage>("Village");
	//SetCurMap(Village);

	std::shared_ptr<ACamp> Camp = GetWorld()->SpawnActor<ACamp>("Camp");
	SetCurMap(Camp);
	Camp->SetCurGameMode(this);


	MainPlayer = GetWorld()->SpawnActor<APlayer>("Player");
	MainPlayer->SetCurGameMode(this);
	SetMainPlayer(MainPlayer);

	//AWaterBomb* Bomb = this->GetWorld()->SpawnActor<AWaterBomb>("Bomb", 0).get();
	//Bomb->SetCurGameMode(this);
}

void ASubServerLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UNetObject::AllNetObject;
	int a = 0;

	//if (UEngineInput::IsDown(VK_SPACE)==true)
	//{
	//	std::shared_ptr<AWaterBomb> Bomb = dynamic_pointer_cast<AWaterBomb>(this->GetCurMap()->AddMapObject(MainPlayer->GetPlayerInfo()->CurIndex.y, MainPlayer->GetPlayerInfo()->CurIndex.x,EMapObject::WaterBomb));
	//	Bomb->SetCurGameMode(this);
	//	//Bomb->SetObjectToken(UNetObject::GetNewObjectToken());

	///*	UGame_Core::Net = std::make_shared<UEngineClient>();
	//	UGame_Core::Net->Connect(IP, PORT);*/

	//	//AWaterBomb* Bomb = this->GetWorld()->SpawnActor<AWaterBomb>("Bomb", 0).get();
	//	//Bomb->SetObjectToken(UNetObject::GetNewObjectToken());
	//	//Bomb->SetObjectToken(_Packet->GetObjectToken());
	//	//Bomb->PushProtocol(_Packet);
	//	//Bomb->SetActorLocation(OtherPlayer->GetActorLocation());
	//	//ServerPacketInit(UGame_Core::Net->Dispatcher);
	//}
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

			ServerPacketInit(UGame_Core::Net->Dispatcher);
		});

		subNetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
		{
			UGame_Core::Net = std::make_shared<UEngineClient>();
			UGame_Core::Net->Connect(IP, PORT);

			UGame_Core::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
			{
				MainPlayer->SetObjectToken(_Token->GetSessionToken() * 1000);
				MainPlayer->WaterBomb_Token = _Token->GetSessionToken() * 1000 + 1;
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

	Dis.AddHandler<UWaterBombUpdatePacket>([=](std::shared_ptr<UWaterBombUpdatePacket> _Packet)
	{
		// 다른 사람들한테 이 오브젝트에 대해서 알리고
		UGame_Core::Net->Send(_Packet);

		GetWorld()->PushFunction([=]()
			{
				AOtherBomb* Bomb = UNetObject::GetNetObject<AOtherBomb>(_Packet->GetObjectToken());
				if (nullptr == Bomb)
				{
					Bomb = this->GetWorld()->SpawnActor<AOtherBomb>("Bomb", 0).get();
					//Bomb = dynamic_cast<AOtherBomb>(GetGameMode()->GetCurMap()->SpawnWaterBomb(MainPlayer->GetActorLocation()));
					Bomb->SetObjectToken(_Packet->GetObjectToken());
				}
				Bomb->PushProtocol(_Packet);
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

	Dis.AddHandler<UWaterBombUpdatePacket>([=](std::shared_ptr<UWaterBombUpdatePacket> _Packet)
	{
		// 다른 사람들한테 이 오브젝트에 대해서 알리고
		GetWorld()->PushFunction([=]()
		{
			int Test = _Packet->GetObjectToken();

			AOtherBomb* Bomb = UNetObject::GetNetObject<AOtherBomb>(_Packet->GetObjectToken());
			if (nullptr == Bomb)
			{
				Bomb = this->GetWorld()->SpawnActor<AOtherBomb>("Bomb", 0).get();
				Bomb->SetObjectToken(_Packet->GetObjectToken());
			}
			Bomb->PushProtocol(_Packet);
		});
	});
}

void ASubServerLevel::LevelEnd(ULevel* _DeltaTime)
{
	subNetWindow->Off();
}
