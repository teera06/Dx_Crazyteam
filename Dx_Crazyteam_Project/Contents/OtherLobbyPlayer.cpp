﻿#include "PreCompile.h"
#include <EngineCore/Image.h>
#include "OtherLobbyPlayer.h"
#include "Game_Core.h"
#include "Packets.h"

AOtherLobbyPlayer::AOtherLobbyPlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("RendererRoot");
	SetRoot(Root);
}

AOtherLobbyPlayer::~AOtherLobbyPlayer()
{
}

void AOtherLobbyPlayer::SetRenderer(std::string_view _SpriteName, int _Index)
{
	ImageRenderer->SetSprite(_SpriteName, _Index);
}

void AOtherLobbyPlayer::SetPosition(int _SessionToken)
{
	ImageRenderer->AddPosition(FVector(static_cast<float>(-330 + _SessionToken * 105), 125.0f, 100.0f));
}

void AOtherLobbyPlayer::BeginPlay()
{
	ImageRenderer = CreateWidget<UImage>(GetWorld(), "Room1");
	ImageRenderer->SetScale({ 150, 150 });
	ImageRenderer->SetPosition(FVector(0.f, 0.f));
	ImageRenderer->SetActive(true);
	ImageRenderer->AddToViewPort(15);
	Super::BeginPlay();
}

void AOtherLobbyPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (nullptr == UGame_Core::Net)
	{
		MsgBoxAssert("네트워크 연결이 안된상태에서 아더플레어를 만들었습니다.");
	}

	std::shared_ptr<UEngineProtocol> Protocol = nullptr;

	do
	{
		Protocol = PopProtocol();
		if (nullptr == Protocol)
		{
			break;
		}

		EContentPacket PacketType = Protocol->GetPacketType<EContentPacket>();
			
		std::shared_ptr<ULobbyPlayerUpdatePacket> UpdatePacket = std::dynamic_pointer_cast<ULobbyPlayerUpdatePacket>(Protocol);

		std::string SpriteNames = UpdatePacket->SpriteName;
		int Index = UpdatePacket->SpriteIndex;
		SetRenderer(SpriteNames, Index);
		SetPosition(UpdatePacket->GetSessionToken());		


	} while (nullptr != Protocol);
}
