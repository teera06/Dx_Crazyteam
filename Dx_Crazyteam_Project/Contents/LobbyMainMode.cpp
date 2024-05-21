#include "PreCompile.h"
#include "LobbyMainMode.h"
#include "PlayLobby.h"
#include "FontActor.h"
#include "Game_Core.h"

ALobbyMainMode::ALobbyMainMode()
{
}

ALobbyMainMode::~ALobbyMainMode()
{
}

void ALobbyMainMode::BeginPlay()
{
	Super::BeginPlay();

	PlayLobby = GetWorld()->SpawnActor<APlayLobby>("Lobby");
	GetWorld()->SpawnActor<AFontActor>("FontActor");
}


void ALobbyMainMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

void ALobbyMainMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
	GEngine->DestroyLevel("LobbyMainMode");
}

void ALobbyMainMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	PlayLobby->SetMySessionToken(UGame_Core::Net->GetSessionToken());

	if (0 == UGame_Core::Net->GetSessionToken())
	{
		ServerPacketInit(UGame_Core::Net->Dispatcher);
	}
	else if (1 <= UGame_Core::Net->GetSessionToken())
	{
		ClientPacketInit(UGame_Core::Net->Dispatcher);
	}
}

void ALobbyMainMode::ServerPacketInit(UEngineDispatcher& Dis)
{
	//Dis.AddHandler<APlayLobby>([=](std::shared_ptr<APlayLobby> _Packet)
	//	{
	//		GetWorld()->PushFunction([=]()
	//			{
	//				switch (_Packet->ObjectType)
	//				{
	//				case static_cast<int>(EObjectType::Player):
	//				{
	//					AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
	//					if (nullptr == OtherPlayer)
	//					{
	//						OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
	//						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
	//					}
	//					OtherPlayer->PushProtocol(_Packet);
	//					break;
	//				}
	//				default:
	//					break;
	//				}
	//			});
	//	});
}

void ALobbyMainMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	//Dis.AddHandler<APlayLobby>([=](std::shared_ptr<APlayLobby> _Packet)
	//	{
	//		GetWorld()->PushFunction([=]()
	//			{
	//				switch (_Packet->ObjectType)
	//				{
	//				case static_cast<int>(EObjectType::Player):
	//				{
	//					AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
	//					if (nullptr == OtherPlayer)
	//					{
	//						OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
	//						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
	//					}
	//					OtherPlayer->PushProtocol(_Packet);
	//					break;
	//				}
	//				default:
	//					break;
	//				}
	//			});
	//	});
}