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

	static void SendItemSpawnPacket(std::shared_ptr<AMapObject> _NetObject);
	static void SendItemReleasePacket(int _ObjectToken, POINT _CurPos);

protected:

private:

};

