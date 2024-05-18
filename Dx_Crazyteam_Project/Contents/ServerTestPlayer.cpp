﻿#include "PreCompile.h"
#include <EngineBase/EngineProtocol.h>

#include "ServerTestPlayer.h"
#include "ItemBubble.h"
#include "Game_Core.h"
#include "MapObject.h"
#include "Packets.h"
#include "CAGameMode.h"
#include "BaseMap.h"



AServerTestPlayer::AServerTestPlayer()
	:APlayer()
{
}

AServerTestPlayer::~AServerTestPlayer()
{
}

void AServerTestPlayer::BeginPlay()
{
	Super::BeginPlay();

	OffIsSendPacket();
}

void AServerTestPlayer::Tick(float _DeltaTime)
{
	if (true == IsDown('P'))
	{
		SpawnItem();
	}

	Super::Tick(_DeltaTime);

	if (false == IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UGame_Core::Net)
		{
			InitNet(UGame_Core::Net);
		}
	}

	CurTime -= _DeltaTime;

	if (0.0f >= CurTime && true == IsNetInit())
	{
		std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

		Packet->Pos = GetActorLocation();
		Packet->AnimationInfo = Renderer->GetCurAnimationFrame();
		Packet->SpriteName = Renderer->GetCurInfo().Texture->GetName();
		Packet->ObjectType = static_cast<int>(EObjectType::Player);
		Send(Packet);
		CurTime += FrameTime;
	}
}

void AServerTestPlayer::SpawnItem()
{
	std::shared_ptr<AMapObject> BubbleItem = GetGameMode()->GetCurMap()->AddMapObject(6, 1, EMapObject::Item, EItemType::ItemBubble);

	SendPacket(BubbleItem);
}

void AServerTestPlayer::SendPacket(std::shared_ptr<AMapObject> _NetObject)
{
	_NetObject->SetObjectToken(UNetObject::GetNewObjectToken());

	std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();
	Packet->SetObjectToken(_NetObject->GetObjectToken());
	Packet->Pos = _NetObject->GetActorLocation();
	Packet->IsDestroy = false;
	Packet->ObjectType = static_cast<int>(EObjectType::Item);
	UGame_Core::Net->Send(Packet);
}