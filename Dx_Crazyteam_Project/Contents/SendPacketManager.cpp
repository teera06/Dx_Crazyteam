#include "PreCompile.h"

#include "SendPacketManager.h"
#include "MapObject.h"
#include "TestPackets.h"
#include "Game_Core.h"


USendPacketManager::USendPacketManager()
{
}

USendPacketManager::~USendPacketManager()
{
}

void USendPacketManager::SendItemSpawnPacket(std::shared_ptr<AMapObject> _NetObject)
{
	if (false == _NetObject->IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UGame_Core::Net)
		{
			_NetObject->InitNet(UGame_Core::Net);
		}
	}

	_NetObject->SetObjectToken(UNetObject::GetNewObjectToken());

	std::shared_ptr<UMapObjectUpdatePacket> Packet = std::make_shared<UMapObjectUpdatePacket>();
	Packet->SetObjectToken(_NetObject->GetObjectToken());
	Packet->IsDestroy = false;
	_NetObject->Send(Packet);
}

void USendPacketManager::SendItemReleasePacket(int _ObjectToken, POINT _CurPos)
{
	std::shared_ptr<UMapObjectUpdatePacket> Packet = std::make_shared<UMapObjectUpdatePacket>();
	Packet->SetObjectToken(_ObjectToken);
	Packet->IsDestroy = true;
	Packet->Pos = _CurPos;
	UGame_Core::Net->Send(Packet);
}