#include "PreCompile.h"
#include <EngineBase/EngineProtocol.h>

#include "ServerTestPlayer.h"
#include "ItemBubble.h"
#include "Game_Core.h"
#include "Packets.h"

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
	std::shared_ptr<AItemBubble> BubbleItem = GetWorld()->SpawnActor<AItemBubble>("BubbleItem");
	BubbleItem->SetObjectToken(UNetObject::GetNewObjectToken());
	BubbleItem->SetActorLocation(GetActorLocation() + float4(50.0f, 50.0f, 0.0f));

	std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();
	Packet->SetObjectToken(BubbleItem->GetObjectToken());
	Packet->Pos = BubbleItem->GetActorLocation();
	Packet->IsDestroy = false;
	Send(Packet);
}