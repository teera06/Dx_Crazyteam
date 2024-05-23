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

}

void AServerGameMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	
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
	if (IsServerOpen != false)
	{
		NetWindow->Off();
	}

	
}

void AServerGameMode::CollectWindowAppear()
{
	NetWindow->On();
}

