#include "PreCompile.h"
#include "ServerGameMode.h"
#include <EngineBase/EngineProtocol.h>

#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>

#include "ServerTestPlayer.h"
#include "Game_Core.h"
#include "Packets.h"
#include "OtherPlayer.h"
#include "Village.h"
#include "ItemBubble.h"

#include "TitleMenu.h"
#include "PlayLobby.h"

#include "TestLobbyMode.h"


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


	Village = GetWorld()->SpawnActor<AVillage>("Village");
	SetCurMap(Village);

	MainPlayer = GetWorld()->SpawnActor<AServerTestPlayer>("Player");
	MainPlayer->SetCurGameMode(this);
	SetMainPlayer(MainPlayer);
}

void AServerGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UNetObject::AllNetObject;
}

void AServerGameMode::LevelStart(ULevel* _PrevLevel)
{
	if (nullptr == NetWindow)
	{
		NetWindow = UEngineEditorGUI::CreateEditorWindow<UEngineNetWindow>("NetWindow");

		NetWindow->SetServerOpenFunction([&]()
			{
				UGame_Core::Net = std::make_shared<UEngineServer>();
				UGame_Core::Net->ServerOpen(30000, 512);

				MainPlayer->SetObjectToken(UNetObject::GetNewObjectToken());
				

				ServerPacketInit(UGame_Core::Net->Dispatcher);
			});

		NetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
			{
				UGame_Core::Net = std::make_shared<UEngineClient>();
				UGame_Core::Net->Connect(IP, PORT);

				UGame_Core::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
					{
						MainPlayer->SetObjectToken(_Token->GetObjectToken());
					});

				// 어떤 패키싱 왔을때 어떻게 처리할건지를 정하는 걸 해야한다.
				ClientPacketInit(UGame_Core::Net->Dispatcher);
			});
	}
	NetWindow->On();
}

void AServerGameMode::ServerPacketInit(UEngineDispatcher& Dis)
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
}

void AServerGameMode::ClientPacketInit(UEngineDispatcher& Dis)
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
}

std::shared_ptr<APlayLobby> AServerGameMode::GetPlayLobby()
{
	return PlayLobby;
}

void AServerGameMode::LevelEnd(ULevel* _NextLevel)
{
	NetWindow->Off();
}

void AServerGameMode::CollectWindowAppear()
{
	NetWindow->On();
}