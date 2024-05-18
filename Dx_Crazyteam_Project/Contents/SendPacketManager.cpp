#include "PreCompile.h"

#include "SendPacketManager.h"
#include "MapObject.h"
#include "Packets.h"
#include "Game_Core.h"

USendPacketManager::USendPacketManager()
{
}

USendPacketManager::~USendPacketManager()
{
}

void USendPacketManager::SendItemSpawnPacket(std::shared_ptr<AMapObject> _NetObject)
{
	_NetObject->SetObjectToken(UNetObject::GetNewObjectToken());

	std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();
	Packet->SetObjectToken(_NetObject->GetObjectToken());
	Packet->Pos = _NetObject->GetActorLocation();
	Packet->IsDestroy = false;
	Packet->ObjectType = static_cast<int>(EObjectType::Item);
	UGame_Core::Net->Send(Packet);
}

void USendPacketManager::SendItemReleasePacket(int _ObjectToken, POINT _CurPos)
{
	std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();
	Packet->SetObjectToken(_ObjectToken);
	Packet->IsDestroy = true;
	Packet->ObjectType = static_cast<int>(EObjectType::Item);
	Packet->Pos = float4(_CurPos.x, _CurPos.y);
	UGame_Core::Net->Send(Packet);
}