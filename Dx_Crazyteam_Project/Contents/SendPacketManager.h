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

	static void SendItemPacket(std::shared_ptr<AMapObject> _NetObject, bool _IsSpawn);

protected:

private:

};

