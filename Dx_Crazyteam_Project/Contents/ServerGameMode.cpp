#include "PreCompile.h"
#include "ServerGameMode.h"

#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>

#include "Player.h"
#include "Game_Core.h"
#include "Packets.h"
#include "OtherPlayer.h"
#include "Village.h"

#include "TitleMenu.h"
#include "PlayLobby.h"

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


	//Village = GetWorld()->SpawnActor<AVillage>("Village");
	//SetCurMap(Village);

	//MainPlayer = GetWorld()->SpawnActor<APlayer>("Player");
	//MainPlayer->SetCurGameMode(this);
	//SetMainPlayer(MainPlayer);

	PlayLobby = GetWorld()->SpawnActor<APlayLobby>("PlayLobby");
	TitleMenu = GetWorld()->SpawnActor<ATitleMenu>("TitleMenu");
	//TitleMenu->SetFunction(std::bind(&AServerGameMode::CollectWindowAppear, this));
}

void AServerGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AServerGameMode::LevelStart(ULevel* _DeltaTime)
{
	if (nullptr == NetWindow)
	{
		NetWindow = UEngineEditorGUI::CreateEditorWindow<UEngineNetWindow>("NetWindow");

		NetWindow->SetServerOpenFunction([&]()
			{
				UGame_Core::Net = std::make_shared<UEngineServer>();
				UGame_Core::Net->ServerOpen(30000, 512);

				//ServerPacketInit(UGame_Core::Net->Dispatcher);
			});

		NetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
			{
				UGame_Core::Net = std::make_shared<UEngineClient>();
				UGame_Core::Net->Connect(IP, PORT);

				//ClientPacketInit(UGame_Core::Net->Dispatcher);
			});
	}
	NetWindow->Off();
}

//void AServerGameMode::ServerPacketInit(UEngineDispatcher& Dis)
//{
//	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
//		{
//			// 다른 사람들한테 이 오브젝트에 대해서 알리고
//		    UGame_Core::Net->Send(_Packet);
//
//			GetWorld()->PushFunction([=]()
//				{
//					AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
//					if (nullptr == OtherPlayer)
//					{
//						OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
//						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
//					}
//					OtherPlayer->PushProtocol(_Packet);
//				});
//
//
//		});
//}
//
//void AServerGameMode::ClientPacketInit(UEngineDispatcher& Dis)
//{
//	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
//		{
//			GetWorld()->PushFunction([=]()
//				{
//					AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
//					if (nullptr == OtherPlayer)
//					{
//						OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
//						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
//					}
//					OtherPlayer->PushProtocol(_Packet);
//				});
//		});
//}

std::shared_ptr<APlayLobby> AServerGameMode::GetPlayLobby()
{
	return PlayLobby;
}

void AServerGameMode::LevelEnd(ULevel* _DeltaTime)
{
	NetWindow->Off();
}

void AServerGameMode::CollectWindowAppear()
{
	NetWindow->On();
}