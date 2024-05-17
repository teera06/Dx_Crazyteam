#include "PreCompile.h"
#include "OtherBomb.h"
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Game_Core.h"
#include "Packets.h"
#include "EngineBase/EngineTime.h"

AOtherBomb::AOtherBomb()
{
	UEngineTime Time;
	OherBomb_MilliSecond = Time.GetCurTime().MilliSecond;
	OherBomb_Second = Time.GetCurTime().Second;
}

AOtherBomb::~AOtherBomb()
{
}

void AOtherBomb::BeginPlay()
{
	AWaterBomb::BeginPlay();

	Sub_MilliSecond = OherBomb_MilliSecond - Bomb_MilliSecond;
	Sub_Second = OherBomb_Second - Bomb_Second;
	OtherCreate = true;

}

void AOtherBomb::Tick(float _DeltaTime)
{
	std::shared_ptr<UEngineProtocol> Protocol = nullptr;

	do
	{
		Protocol = PopProtocol();
		if (nullptr == Protocol)
		{
			break;
		}
		EContentPacket PacketType = Protocol->GetPacketType<EContentPacket>();

		switch (PacketType)
		{
		case WaterBombUpdatePacket:
		{

			std::shared_ptr<UWaterBombUpdatePacket> UpdatePacket = std::dynamic_pointer_cast<UWaterBombUpdatePacket>(Protocol);

			if (UpdatePacket->ObjectType == static_cast<int>(EObjectType::WaterBomb))
			{
				SetActorLocation(UpdatePacket->Pos);
			}
			//else if (UpdatePacket->ObjectType == static_cast<int>(EObjectType::WaterBomb))
			//{
			//	AWaterBomb::SetActorLocation(UpdatePacket->Pos);
			//}
		
			break;
		}
		default:
			break;
		}
	} while (nullptr != Protocol);

	
	AWaterBomb::Tick(_DeltaTime);
}

