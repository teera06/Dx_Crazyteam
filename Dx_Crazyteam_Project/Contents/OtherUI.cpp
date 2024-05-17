#include "PreCompile.h"
#include "OtherUI.h"
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Game_Core.h"
#include "Packets.h"
#include "EngineBase/EngineTime.h"

AOtherUI::AOtherUI()
{
	UEngineTime Time;
	MapTime_MilliSecond = Time.GetCurTime().MilliSecond;
	MapTime_Second = Time.GetCurTime().Second;
}

AOtherUI::~AOtherUI()
{
}

void AOtherUI::BeginPlay()
{
	AMapUI::BeginPlay();

	Sub_MilliSecond = MapTime_MilliSecond - MapTime_MilliSecond;
	Sub_Second = MapTime_Second - MapTime_Second;
	OtherCreate = true;
}

void AOtherUI::Tick(float _DeltaTime)
{
	/*std::shared_ptr<UEngineProtocol> Protocol = nullptr;

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


			break;
		}
		default:
			break;
		}
	} while (nullptr != Protocol);*/


	AMapUI::Tick(_DeltaTime);
}

