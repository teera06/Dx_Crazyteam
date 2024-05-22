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

	if (EMapObject::Water == _MapObjectType)
	{
		int a = 0;
	}

	if (EMapObject::WaterBomb != _MapObjectType && EMapObject::Water != _MapObjectType)
	{
		_NetObject->SetObjectToken(UNetObject::GetNewObjectToken());
	}

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

void USendPacketManager::SendMapObjectMovePacket(AMapObject* _NetObject, FVector _Position)
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
		//	MsgBoxAssert("네트워크에 접근하지 않고 오브젝트 이동 패킷을 보내려고 했습니다");
		//	return;
		//}
	}

	std::shared_ptr<UMapObjectUpdatePacket> Packet = std::make_shared<UMapObjectUpdatePacket>();
	Packet->SetObjectToken(_NetObject->GetObjectToken());
	Packet->IsMove = true;
	Packet->MovePos = _Position;
	_NetObject->Send(Packet);
}

void USendPacketManager::SendMapObjectMoveEndPacket(std::shared_ptr<AMapObject> _NetObject, int _NY, int _NX, int _PY, int _PX)
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
		//	MsgBoxAssert("네트워크에 접근하지 않고 오브젝트 이동종료 패킷을 보내려고 했습니다");
		//	return;
		//}
	}

	std::shared_ptr<UMapObjectUpdatePacket> Packet = std::make_shared<UMapObjectUpdatePacket>();
	Packet->SetObjectToken(_NetObject->GetObjectToken());
	Packet->MoveBeginPos = POINT(_PX, _PY);
	Packet->MoveEndPos = POINT(_NX, _NY);
	Packet->IsMoveEnd = true;
	_NetObject->Send(Packet);
}

void USendPacketManager::SendLPlayerPacket(UNetObject* _NetObject, std::string_view _SpriteName, int _SpriteIndex, int _Token)
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
	std::shared_ptr<ULobbyPlayerUpdatePacket> Packet = std::make_shared<ULobbyPlayerUpdatePacket>();
	Packet->SpriteName = _SpriteName;
	Packet->SpriteIndex = _SpriteIndex;	
	Packet->Token = _Token;

	int a = _NetObject->GetObjectToken();

	_NetObject->Send(Packet);
}