#include "PreCompile.h"

#include "NetInterface.h"
#include "Game_Core.h"
#include "Packets.h"

UNetInterface::UNetInterface()
{
}

UNetInterface::~UNetInterface()
{
}

void UNetInterface::PlayerSendPacket(float _DeltaTime, float4 _Pos, std::string_view _AnimationName, int _Frame)
{
	if (false == IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UGame_Core::Net)
		{
			InitNet(UGame_Core::Net);
		}
	}

	CurTime -= _DeltaTime;

	if (0.0f >= CurTime && true == IsNetInit())
	{
		std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

		Packet->Pos = _Pos;
		Packet->AnimationInfo = _Frame;
		Packet->SpriteName = _AnimationName;
		Send(Packet);
		CurTime += FrameTime;
	}
}