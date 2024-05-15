#include "PreCompile.h"
#include <EngineBase/NetObject.h>

#include "TestLobbyMode.h"
#include "Game_Core.h"
#include "TestLobbyPlayer.h"

ATestLobbyMode::ATestLobbyMode()
{
}

ATestLobbyMode::~ATestLobbyMode()
{
}

void ATestLobbyMode::BeginPlay()
{
	Super::BeginPlay();

	CreateObject();
}

void ATestLobbyMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATestLobbyMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	int DistinctToken = UGame_Core::Net->GetSessionToken();

	if (0 == DistinctToken)
	{
		ServerPacketInit(UGame_Core::Net->Dispatcher);
	}
	else if (1 <= DistinctToken)
	{
		ClientPacketInit(UGame_Core::Net->Dispatcher);
	}
}

void ATestLobbyMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ATestLobbyMode::ServerPacketInit(UEngineDispatcher& Dis)
{
	//Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
	//	{
	//		// 다른 사람들한테 이 오브젝트에 대해서 알리고
	//	    UGame_Core::Net->Send(_Packet);

	//		GetWorld()->PushFunction([=]()
	//			{
	//				AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
	//				if (nullptr == OtherPlayer)
	//				{
	//					OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
	//					OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
	//				}
	//				OtherPlayer->PushProtocol(_Packet);
	//			});
	//	});
}

void ATestLobbyMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	/*Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
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
		});*/
}

void ATestLobbyMode::CreateObject()
{
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	MainLobbyPlayer = GetWorld()->SpawnActor<ATestLobbyPlayer>("MainLobbyPlayer");
}