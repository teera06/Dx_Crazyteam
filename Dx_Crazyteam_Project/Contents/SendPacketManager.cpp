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

void USendPacketManager::SendMapObjectSpawnPacket(std::shared_ptr<AMapObject> _NetObject, POINT _CurPos, EMapObject _MapObjectType, EItemType _ItemType /*= EItemType::None*/)
{
	if (false == _NetObject->IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UGame_Core::Net)
		{
			_NetObject->InitNet(UGame_Core::Net);
		}
		//else
		//{
		//	MsgBoxAssert("네트워크에 접근하지 않고 아이템 오브젝트 생성 패킷을 보내려고 했습니다");
		//	return;
		//}
	}

	_NetObject->SetObjectToken(UNetObject::GetNewObjectToken());

	std::shared_ptr<UMapObjectUpdatePacket> Packet = std::make_shared<UMapObjectUpdatePacket>();
	Packet->SetObjectToken(_NetObject->GetObjectToken());
	Packet->IsDestroy = false;
	Packet->Pos = _CurPos;
	Packet->ObjectType = static_cast<int>(_MapObjectType);
	Packet->ItemType = static_cast<int>(_ItemType);
	_NetObject->Send(Packet);
}

void USendPacketManager::SendMapObjectReleasePacket(AMapObject* _NetObject, POINT _CurPos)
{
	if (false == _NetObject->IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UGame_Core::Net)
		{
			_NetObject->InitNet(UGame_Core::Net);
		}
		//else
		//{
		//	MsgBoxAssert("네트워크에 접근하지 않고 오브젝트 릴리즈 패킷을 보내려고 했습니다");
		//	return;
		//}
	}

	std::shared_ptr<UMapObjectUpdatePacket> Packet = std::make_shared<UMapObjectUpdatePacket>();
	Packet->SetObjectToken(_NetObject->GetObjectToken());
	Packet->IsDestroy = true;
	Packet->Pos = _CurPos;
	_NetObject->Send(Packet);
}