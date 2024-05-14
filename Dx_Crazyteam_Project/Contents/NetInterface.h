#pragma once
#include <EngineBase/NetObject.h>

// Ό³Έν :
class UNetInterface : public UNetObject
{
public:
	// constrcuter destructer
	UNetInterface();
	~UNetInterface();

	// delete Function
	UNetInterface(const UNetInterface& _Other) = delete;
	UNetInterface(UNetInterface&& _Other) noexcept = delete;
	UNetInterface& operator=(const UNetInterface& _Other) = delete;
	UNetInterface& operator=(UNetInterface&& _Other) noexcept = delete;

protected:
	void PlayerSendPacket(float _DeltaTime, float4 _Pos, std::string_view _AnimationName, int _Frame);

private:
	float FrameTime = 1.0f / 60.0f;
	float CurTime = FrameTime;
};

