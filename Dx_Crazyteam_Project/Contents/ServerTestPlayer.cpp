#include "PreCompile.h"
#include <EngineBase/EngineProtocol.h>

#include "ServerTestPlayer.h"
#include "ItemBubble.h"
#include "Game_Core.h"
#include "MapObject.h"
#include "Packets.h"
#include "CAGameMode.h"
#include "BaseMap.h"


AServerTestPlayer::AServerTestPlayer()
{
}

AServerTestPlayer::~AServerTestPlayer()
{
}

void AServerTestPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AServerTestPlayer::Tick(float _DeltaTime)
{
	if (true == IsDown('P'))
	{
		SpawnItem();
	}

	Super::Tick(_DeltaTime);
}

void AServerTestPlayer::SpawnItem()
{
	std::shared_ptr<AMapObject> BubbleItem = GetGameMode()->GetCurMap()->AddMapObject(6, 1, EMapObject::Item, EItemType::ItemBubble);
	BubbleItem->SetObjectToken(UNetObject::GetNewObjectToken());

	std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();
	Packet->SetObjectToken(BubbleItem->GetObjectToken());
	Packet->Pos = BubbleItem->GetActorLocation();
	Packet->IsDestroy = false;
	Packet->ObjectType = static_cast<int>(EObjectType::Item);
	Send(Packet);
}