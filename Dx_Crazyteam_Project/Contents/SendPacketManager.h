#pragma once

// Ό³Έν :
class AMapObject;
class USendPacketManager
{
public:
	// constrcuter destructer
	USendPacketManager();
	~USendPacketManager();

	// delete Function
	USendPacketManager(const USendPacketManager& _Other) = delete;
	USendPacketManager(USendPacketManager&& _Other) noexcept = delete;
	USendPacketManager& operator=(const USendPacketManager& _Other) = delete;
	USendPacketManager& operator=(USendPacketManager&& _Other) noexcept = delete;

	static void SendMapObjectSpawnPacket(std::shared_ptr<AMapObject> _NetObject, POINT _CurPos, EMapObject _MapObjectType, EItemType _ItemType = EItemType::None);
	static void SendMapObjectReleasePacket(AMapObject* _NetObject, POINT _CurPos);
	static void SendMapObjectMovePacket(AMapObject* _NetObject, FVector _Position);
	static void SendMapObjectMoveEndPacket(std::shared_ptr<AMapObject> _NetObject, int _NY, int _NX, int _PY, int _PX);

protected:

private:

};

