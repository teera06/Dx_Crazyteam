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

void USendPacketManager::SendItemPacket(std::shared_ptr<AMapObject> _NetObject, bool _IsSpawn)
{
	_NetObject->SetObjectToken(UNetObject::GetNewObjectToken());

	std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();
	Packet->SetObjectToken(_NetObject->GetObjectToken());
	Packet->Pos = _NetObject->GetActorLocation();
	Packet->IsDestroy = false;
	Packet->ObjectType = static_cast<int>(EObjectType::Item);
	UGame_Core::Net->Send(Packet);
}