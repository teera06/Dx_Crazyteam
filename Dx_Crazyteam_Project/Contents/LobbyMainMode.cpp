#include "PreCompile.h"
#include "LobbyMainMode.h"
#include "PlayLobby.h"
#include "FontActor.h"
#include "Game_Core.h"
#include "OtherLobbyPlayer.h"
#include "Packets.h"
#include <EngineCore/Image.h>
#include "ServerGameMode.h"


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

	// 나 로비 들어왔어 샌드

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


	if (AServerGameMode::NetType == ENetType::Server)
	{
		//PlayLobby->NewPlayer();

		std::shared_ptr<ULobbyPlayerUpdatePacket> NewPlayer = std::make_shared<ULobbyPlayerUpdatePacket>();
		NewPlayer->SpriteNames.push_back("Room_Charcater_Bazzi.png");
		NewPlayer->SpriteNames.push_back("Room_Charcater_Bazzi.png");
		NewPlayer->SpriteNames.push_back("Room_Charcater_Bazzi.png");
		NewPlayer->SpriteNames.push_back("Room_Charcater_Bazzi.png");
		NewPlayer->SpriteNames.push_back("Room_Charcater_Bazzi.png");
		NewPlayer->SpriteNames.push_back("Room_Charcater_Bazzi.png");
		NewPlayer->SpriteNames.push_back("Room_Charcater_Bazzi.png");
		NewPlayer->SpriteNames.push_back("Room_Charcater_Bazzi.png");

		PlayLobby->SettingUIPlayerName(NewPlayer->SpriteNames);

		PlayLobby->ChracterChangeLogic = [=](APlayLobby* Lobby)
			{
				
			};
	}
	else if (AServerGameMode::NetType == ENetType::Client)
	{
		// 이미 네트워크 연결이 되어있기 때문에
		// 클라이언트는 그냥 서버한테 쏠거야.
		std::shared_ptr<ULobbyPlayerUpdatePacket> NewPlayer = std::make_shared<ULobbyPlayerUpdatePacket>();
		NewPlayer->NewPlayer = true;
		UGame_Core::Net->Send(NewPlayer);
	}
	else
	{
		MsgBoxAssert("말도 안되는 상황임");
	}
}

void ALobbyMainMode::ServerPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<ULobbyPlayerUpdatePacket>([=](std::shared_ptr<ULobbyPlayerUpdatePacket> _Packet)
		{
			GetWorld()->PushFunction([=]
				{
					if (true == _Packet->NewPlayer)
					{
						PlayLobby->NewPlayer();

						if (8 != PlayLobby->LobbyPlayer.size())
						{
							MsgBoxAssert("UI가 이상함");
						}

						std::vector<UImage*>& PlayerUIImages = PlayLobby->LobbyPlayer;

						std::shared_ptr<ULobbyPlayerUpdatePacket> NewPlayer = std::make_shared<ULobbyPlayerUpdatePacket>();

						for (size_t i = 0; i < PlayerUIImages.size(); i++)
						{
							if (nullptr == PlayerUIImages[i])
							{
								NewPlayer->SpriteNames.push_back("None");
								continue;
							}

							UImage* LobbyPlayerImage = PlayerUIImages[i];
							NewPlayer->SpriteNames.push_back(LobbyPlayerImage->CurInfo.Texture->GetName());
						}

						UGame_Core::Net->Send(NewPlayer);
					}
				});


			// PlayLobby->SetMySessionToken(_Packet->GetSessionToken());
			//AOtherLobbyPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherLobbyPlayer>(_Packet->GetObjectToken());
			//if (nullptr == OtherPlayer)
			//{
			//	OtherPlayer = this->GetWorld()->SpawnActor<AOtherLobbyPlayer>("OtherLobbyPlayer", 0).get();
			//	OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
			//	OtherPlayer->MySessionToken = _Packet->GetObjectToken() - 110000;
			//}
			// OtherPlayer->PushProtocol(_Packet);
			
		});
}

void ALobbyMainMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<ULobbyPlayerUpdatePacket>([=](std::shared_ptr<ULobbyPlayerUpdatePacket> _Packet)
		{
			GetWorld()->PushFunction([=]
				{
					PlayLobby->SettingUIPlayerName(_Packet->SpriteNames);
				});

			//UNetObject* OtherPlayer = UNetObject::GetNetObject<UNetObject>(_Packet->GetObjectToken());
			//if (nullptr == OtherPlayer)
			//{
			//	if (PlayLobby->LobbyPlayer[_Packet->Token] == nullptr)
			//	{
			//		UImage* Sprite = CreateWidget<UImage>(GetWorld(), "LobbyPlayer");
			//		PlayLobby->LobbyPlayer[_Packet->Token] = Sprite;
			//		Sprite->SetActive(false);
			//		OtherPlayer = this->GetWorld()->SpawnActor<AOtherLobbyPlayer>("OtherLobbyPlayer", 0).get();
			//	}
			//}
			//OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
			//OtherPlayer->PushProtocol(_Packet);
		});
}