#pragma once

// 설명 :
class AMapObject;
class UNetObject;
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
	static void SendLPlayerPacket(UNetObject* _NetObject, std::string_view _SpriteName, int _SpriteIndex, int _Token =0);

protected:

private:
	// Test 토큰
	static int MapObjectToken;
	static int MapObjectOffsetToken;
};

