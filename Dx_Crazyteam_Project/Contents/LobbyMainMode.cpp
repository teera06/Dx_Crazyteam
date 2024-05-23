#include "PreCompile.h"
#include "LobbyMainMode.h"
#include "PlayLobby.h"
#include "FontActor.h"
#include "Game_Core.h"
#include "OtherLobbyPlayer.h"
#include "Packets.h"
#include <EngineCore/Image.h>
#include "ServerGameMode.h"
#include "ContentsValue.h"


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

	ServerNum::LobbyPlayerNum;
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
		// 서버가 들어왔기 때문에 로비 플레이어 추가
		ServerNum::LobbyPlayerNum++;

		ServerPacketInit(UGame_Core::Net->Dispatcher);
	}
	else if (1 <= UGame_Core::Net->GetSessionToken())
	{
		ClientPacketInit(UGame_Core::Net->Dispatcher);
	}


	if (AServerGameMode::NetType == ENetType::Server)
	{
		PlayLobby->NewPlayer();
		PlayLobby->ChangeUIIndex = 0;

		// 방장 0번

		PlayLobby->ChracterChangeLogic = [=](APlayLobby* _Lobby, int _Index, std::string_view _SpriteName)
			{
				//_Lobby->
				std::shared_ptr<ULobbyPlayerUpdatePacket> NewPlayer = std::make_shared<ULobbyPlayerUpdatePacket>();
				//NewPlayer->NewPlayer = true;
				std::vector<std::string> SetSpriteNames = NewPlayer->SpriteNames;
				std::vector<UImage*>& PlayerUIImages = _Lobby->LobbyPlayer;
				//PlayerUIImages[_Index]->SetSprite(_SpriteName);
				for (size_t i = 0; i < PlayerUIImages.size(); i++)
				{
					if (nullptr == PlayerUIImages[i])
					{
						NewPlayer->SpriteNames.push_back("None");
						continue;
					}
					if (i == _Index)
					{
						std::string SetName = _SpriteName.data();
						NewPlayer->SpriteNames.push_back(SetName);
					}
					else
					{
						NewPlayer->SpriteNames.push_back(_Lobby->LobbyPlayer[i]->CurInfo.Texture->GetName());
					}

				}
				UGame_Core::Net->Send(NewPlayer);
			};
		
		PlayLobby->MapChangeLogic = [=](APlayLobby* _Lobby, std::string_view _MapName)
			{
				std::shared_ptr<ULobbyPlayerUpdatePacket> NewPlayer = std::make_shared<ULobbyPlayerUpdatePacket>();		
				
				std::vector<std::string> SetSpriteNames = NewPlayer->SpriteNames;
				std::vector<UImage*>& PlayerUIImages = _Lobby->LobbyPlayer;
				for (size_t i = 0; i < PlayerUIImages.size(); i++)
				{
					if (nullptr == PlayerUIImages[i])
					{
						continue;
					}
					NewPlayer->MapName = _MapName.data();
					NewPlayer->ChangeMaP = true;
					UGame_Core::Net->Send(NewPlayer);
				}

				_Lobby->MapChange(_MapName);
			};				
	}
	else if (AServerGameMode::NetType == ENetType::Client)
	{

		PlayLobby->ChracterChangeLogic = [=](APlayLobby* _Lobby, int _Index, std::string_view _SpriteName)
			{
				//_Lobby->
				std::shared_ptr<ULobbyPlayerUpdatePacket> NewPlayer = std::make_shared<ULobbyPlayerUpdatePacket>();
				//NewPlayer->NewPlayer = true;
				std::vector<std::string> SetSpriteNames = NewPlayer->SpriteNames;


				std::vector<UImage*>& PlayerUIImages = _Lobby->LobbyPlayer;
				for (size_t i = 0; i < PlayerUIImages.size(); i++)
				{
					if (nullptr == PlayerUIImages[i])
					{
						NewPlayer->SpriteNames.push_back("None");
						continue;
					}
					if (i == _Index)
					{
						std::string SetName = _SpriteName.data();
						NewPlayer->SpriteNames.push_back(SetName);
					}
					else
					{
						NewPlayer->SpriteNames.push_back(_Lobby->LobbyPlayer[i]->CurInfo.Texture->GetName());
					}
				}
				UGame_Core::Net->Send(NewPlayer);
			};

		PlayLobby->ChangeUIIndex = UGame_Core::Net->GetSessionToken();
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

						// client가 들어왔을 때 로비Player 수 추가
						ServerNum::LobbyPlayerNum++;

						UGame_Core::Net->Send(NewPlayer);
					}
					else if(false == _Packet->NewPlayer)
					{
						std::vector<UImage*>& PlayerUIImages = PlayLobby->LobbyPlayer;

						std::string name = _Packet->SpriteNames[_Packet->GetSessionToken()];
						int a = _Packet->GetSessionToken();
						PlayerUIImages[_Packet->GetSessionToken()]->SetSprite(_Packet->SpriteNames[_Packet->GetSessionToken()]);

						std::shared_ptr<ULobbyPlayerUpdatePacket> NewPlayer = std::make_shared<ULobbyPlayerUpdatePacket>();

						for (size_t i = 0; i < PlayerUIImages.size(); i++)
						{
							if (nullptr == PlayerUIImages[i])
							{
								NewPlayer->SpriteNames.push_back("None");
								continue;
							}

							
							if (i != 0)
							{
								PlayerUIImages[i]->SetSprite(_Packet->SpriteNames[i]);
							}
	
							NewPlayer->SpriteNames.push_back(_Packet->SpriteNames[i]);
						}

						UGame_Core::Net->Send(NewPlayer);
					}					
				});			
		});
}

void ALobbyMainMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<ULobbyPlayerUpdatePacket>([=](std::shared_ptr<ULobbyPlayerUpdatePacket> _Packet)
		{
			GetWorld()->PushFunction([=]
				{
					if(_Packet->ChangeMaP ==true)
					{ 
						PlayLobby->MapChange(_Packet->MapName);
						return;
					}
					PlayLobby->SettingUIPlayerName(_Packet->SpriteNames);

				});
		});
}